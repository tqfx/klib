/*!
 @file           kstring.c
 @brief          basic string library
 @author         tqfx tqfx@foxmail.com
 @version        0
 @date           2021-05-30
 @copyright      Copyright (C) 2021 tqfx
 \n \n
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 \n \n
 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.
 \n \n
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.
*/

#include "kstring.h"

#include <assert.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int kvsprintf(kstring_t *ks,
              const char *fmt,
              va_list ap)
{
    assert(ks && "ks is null");
    assert(fmt && "fmt is null");

    va_list args;

    va_copy(args, ap);
    /* This line does not work with glibc 2.0. See `man snprintf' */
    int l = vsnprintf(ks->s + ks->l, ks->m - ks->l, fmt, args);
    va_end(args);

    if (ks->m - ks->l < (size_t)l + 1U)
    {
        if (ks_resize(ks, ks->l + (size_t)l + 1U))
        {
            return -1;
        }

        va_copy(args, ap);
        l = vsnprintf(ks->s + ks->l, ks->m - ks->l, fmt, args);
        va_end(args);
    }

    ks->l += (size_t)l;

    return l;
}

int ksprintf(kstring_t *ks,
             const char *fmt,
             ...)
{
    assert(ks && "ks is null");
    assert(fmt && "fmt is null");

    va_list ap;

    va_start(ap, fmt);
    int l = kvsprintf(ks, fmt, ap);
    va_end(ap);

    return l;
}

void *ks_find(void *dst,
              size_t nd,
              const void *src,
              size_t ns)
{
    assert(dst);
    assert(src);

    /* when ns is 0, return dst */
    void *ret = (void *)dst;
    /* ns is 0 */
    if (!ns)
    {
        return ret;
    }

    /* When data is not found, return null */
    ret = NULL;

    /* The end pointer of source */
    const char *src_end = (const char *)src + ns;
    /* The end pointer of destination */
    char *dst_end = (char *)dst + nd;

    /* Start the iteration */
    char *p = (char *)dst;
    while (p != dst_end)
    {
        /* When nd is less than ns */
        if ((size_t)(dst_end - p) < ns)
        {
            break;
        }

        /* The start pointer of source */
        const char *ps = (const char *)src;
        /* The start pointer of destination */
        char *pd = p;

        /* memcmp */
        while (ps != src_end)
        {
            if (*ps != *pd)
            {
                break;
            }

            ++pd;
            ++ps;
        }

        /* The data has been found */
        if (ps == src_end)
        {
            ret = (void *)p;
            break;
        }

        ++p;
    }

    return ret;
}

size_t ks_cnt_(const kstring_t *ks,
               const char *s,
               size_t l)
{
    assert(ks && "ks is null");
    assert(s && "s is null");

    size_t ret = 0U;

    /* when l is 0, it will goes into an infinite cycle */
    if (!l)
    {
        return ret;
    }

    /* The end pointer of substring */
    const char *pend = ks->s + ks->l;
    /* The start pointer */
    char *p = ks->s;
    while ((p = (char *)ks_find(p, (size_t)(pend - p), s, l)))
    {
        p += l;
        ++ret;
    }

    return ret;
}

size_t ks_cnt(const kstring_t *ks,
              const char *s)
{
    assert(ks && "ks is null");
    assert(s && "s is null");

    return ks_cnt_(ks, s, strlen(s));
}

int ks_ins_(kstring_t *ks,
            size_t i,
            const char *s,
            size_t l)
{
    assert(ks && "ks is null");
    assert(s && "s is null");

    /* Expand memory */
    if (ks_resize(ks, ks->l + l + 1U))
    {
        return -1;
    }

    /* Restrict where to insert */
    i = i > ks->l ? ks->l : i;

    /* Move data back through from back to front */
    char *pstart = ks->s + i - 1U;
    char *p = ks->s + ks->l;
    char *pend = p + l;
    while (p != pstart)
    {
        *pend-- = *p--;
    }

    (void)memcpy(ks->s + i, s, l);
    ks->l += l;

    return 0;
}

int ks_ins(kstring_t *ks, size_t i, const char *s)
{
    assert(ks && "ks is null");
    assert(s && "s is null");

    return ks_ins_(ks, i, s, strlen(s));
}

size_t ks_del_(kstring_t *ks,
               const char *s,
               size_t l)
{
    assert(ks && "ks is null");
    assert(s && "s is null");

    size_t ret = 0U;

    /* when l is 0, it will goes into an infinite cycle */
    if (!l)
    {
        return ret;
    }

    /* Trying to find substring */
    char *ps = (char *)ks_find(ks->s, ks->l, s, l);
    if (!ps)
    {
        return ret;
    }

    /* The end pointer of string */
    char *pend = ks->s + ks->l;
    /* The current pointer of string */
    char *p = ps;

    while (ps != pend)
    {
        ps += l;
        /* The next pointer that is the same as the substring */
        char *pd = (char *)ks_find(ps, (size_t)(pend - ps), s, l);
        if (!pd)
        {
            /* No substring found */
            pd = pend;
        }

        /* memcpy */
        while (ps != pd)
        {
            *p++ = *ps++;
        }

        /* count */
        ++ret;
    }

    *p = 0;
    /* Recalculate the length of the string */
    ks->l = (size_t)(p - ks->s);

    return ret;
}

size_t ks_del(kstring_t *ks,
              const char *s)
{
    assert(ks && "ks is null");
    assert(s && "s is null");

    return ks_del_(ks, s, strlen(s));
}

int ks_del1_(kstring_t *ks,
             const char *s,
             size_t l)
{
    assert(ks && "ks is null");
    assert(s && "s is null");

    /* when l is 0, not need to delete */
    if (!l)
    {
        return -1;
    }

    /* Trying to find substring */
    char *ps = (char *)ks_find(ks->s, ks->l, s, l);
    if (!ps)
    {
        return -1;
    }

    /* The end pointer of string */
    char *pend = ks->s + ks->l;
    /* The start pointer that needs to be copied */
    char *p = ps + l;

    /* memcpy */
    while (p != pend)
    {
        *ps++ = *p++;
    }

    *ps = 0;

    ks->l -= l;

    return 0;
}

int ks_del1(kstring_t *ks,
            const char *s)
{
    assert(ks && "ks is null");
    assert(s && "s is null");

    return ks_del1_(ks, s, strlen(s));
}

size_t ks_mod_(kstring_t *ks,
               const char *old,
               const char *new,
               size_t l)
{
    assert(ks && "ks is null");
    assert(old && "old is null");
    assert(new && "new is null");

    size_t ret = 0U;

    const size_t n = strlen(old);
    /* when n is 0, it will goes into an infinite cycle */
    if (!n)
    {
        return ret;
    }

    /* The start pointer of string */
    char *pstart = ks->s;
    /* The end pointer of string */
    char *pend = ks->s + ks->l;
    /* The current pointer of string */
    char *ps = ks->s;

    kstring_t *tmp = ks_init();
    while ((ps = (char *)ks_find(ps, (size_t)(pend - ps), old, n)))
    {
        (void)kputsn(tmp, pstart, (size_t)(ps - pstart));
        (void)kputsn(tmp, new, l);
        /* Move pointer */
        ps += n;
        pstart = ps;
        /* count */
        ++ret;
    }
    (void)kputs(tmp, pstart);
    if (ret)
    {
        /* Move a pointer to memory */
        free(ks->s);
        (void)memcpy(ks, tmp, sizeof(kstring_t));
    }
    free(tmp);
    tmp = NULL;

    return ret;
}

size_t ks_mod(kstring_t *ks,
              const char *old,
              const char *new)
{
    assert(ks && "ks is null");
    assert(old && "old is null");
    assert(new && "new is null");

    return ks_mod_(ks, old, new, strlen(new));
}

int ks_mod1_(kstring_t *ks,
             const char *old,
             const char *new,
             size_t l)
{
    assert(ks && "ks is null");
    assert(old && "old is null");
    assert(new && "new is null");

    const size_t n = strlen(old);
    /* when l is 0, not need to delete */
    if (!n)
    {
        return -1;
    }

    char *ps = (char *)ks_find(ks->s, ks->l, old, n);
    if (!ps)
    {
        return -1;
    }

    kstring_t *tmp = ks_init();
    (void)kputsn(tmp, ks->s, (size_t)(ps - ks->s));
    (void)kputsn(tmp, new, l);
    (void)kputs(tmp, ps + n);
    /* Move a pointer to memory */
    free(ks->s);
    (void)memcpy(ks, tmp, sizeof(kstring_t));
    free(tmp);
    tmp = NULL;

    return 0;
}

int ks_mod1(kstring_t *ks,
            const char *old,
            const char *new)
{
    assert(ks && "ks is null");
    assert(old && "old is null");
    assert(new && "new is null");

    return ks_mod1_(ks, old, new, strlen(new));
}

/* END OF FILE */
