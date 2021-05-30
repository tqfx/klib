/*!
 @file           kstring.h
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

/* Define to prevent recursive inclusion */
#ifndef __KSTRING_H__
#define __KSTRING_H__

#ifndef __STDC_WANT_LIB_EXT1__
#define __STDC_WANT_LIB_EXT1__ 1
#endif /* __STDC_WANT_LIB_EXT1__ */

#include "klib.h"

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#undef KS_ATTR_PRINTF
#if __GNUC_PREREQ(2, 4)
#define KS_ATTR_PRINTF(fmt, arg) \
    __attribute__((__format__(__printf__, fmt, arg)))
#else
#define KS_ATTR_PRINTF(fmt, arg)
#endif /* __GNUC__ */

/*!
 @brief          c string
*/
typedef struct kstring_t
{
    size_t m; /* size of real memory     */
    size_t l; /* length of string        */
    char *s;  /* first address of string */
} kstring_t;

__BEGIN_DECLS

/*!
 @brief          print string to kstring_t
 @param[in]      ks: pointer of kstring_t
 @param[in]      fmt: format
 @param[in]      ap: va_list
 @return         Number of characters
*/
extern int kvsprintf(kstring_t *ks,
                     const char *fmt,
                     va_list ap)
    KS_ATTR_PRINTF(2, 0);

/*!
 @brief          print string to kstring_t
 @param[in]      ks: pointer of kstring_t
 @param[in]      fmt: format
 @return         Number of characters
*/
extern int ksprintf(kstring_t *ks,
                    const char *fmt,
                    ...)
    KS_ATTR_PRINTF(2, 3);

/*!
 @brief          Find the source data from the destination data
 @param[in]      dst: The pointer of destination data
 @param[in]      nd: The number of destination data
 @param[in]      src: The pointer of source data
 @param[in]      ns: The number of source data
 @return         Pointer to the data found in the destination data
*/
extern void *ks_find(void *dst,
                     size_t nd,
                     const void *src,
                     size_t ns);

/*!
 @brief          count substring from kstring_t
 @param[in]      ks: pointer of kstring_t
 @param[in]      s: substring
 @param[in]      l: length of substring
 @return         count of substring
*/
extern size_t ks_cnt_(const kstring_t *ks,
                      const char *s,
                      size_t l)
    __NONNULL((1, 2));

/*!
 @brief          count substring from kstring_t
 @param[in]      ks: pointer of kstring_t
 @param[in]      s: substring
 @return         count of substring
*/
extern size_t ks_cnt(const kstring_t *ks,
                     const char *s)
    __NONNULL_ALL;

/*!
 @brief          insert string in kstring_t
 @param[in]      ks: pointer of kstring_t
 @param[in]      s: string need to insert
 @param[in]      l: length of string
 @return         The execution state of the function
  @retval        0  success
  @retval        -1 failure
*/
extern int ks_ins_(kstring_t *ks,
                   size_t i,
                   const char *s,
                   size_t l)
    __NONNULL((1, 3));

/*!
 @brief          insert string in kstring_t
 @param[in]      ks: pointer of kstring_t
 @param[in]      s: string need to insert
 @return         The execution state of the function
  @retval        0  success
  @retval        -1 failure
*/
extern int ks_ins(kstring_t *ks,
                  size_t i,
                  const char *s)
    __NONNULL((1, 3));

/*!
 @brief          delete substring from kstring_t
 @param[in]      ks: pointer of kstring_t
 @param[in]      s: substring
 @param[in]      l: length of substring
 @return         count of substring deleted
*/
extern size_t ks_del_(kstring_t *ks,
                      const char *s,
                      size_t l)
    __NONNULL((1, 2));

/*!
 @brief          delete substring from kstring_t
 @param[in]      ks: pointer of kstring_t
 @param[in]      s: substring
 @return         count of substring deleted
*/
extern size_t ks_del(kstring_t *ks,
                     const char *s)
    __NONNULL_ALL;

/*!
 @brief          delete a substring from kstring_t
 @param[in]      ks: pointer of kstring_t
 @param[in]      s: substring
 @param[in]      l: length of substring
 @return         The execution state of the function
  @retval        0  success
  @retval        -1 failure
*/
extern int ks_del1_(kstring_t *ks,
                    const char *s,
                    size_t l)
    __NONNULL((1, 2));

/*!
 @brief          delete a substring from kstring_t
 @param[in]      ks: pointer of kstring_t
 @param[in]      s: substring
 @return         The execution state of the function
  @retval        0  success
  @retval        -1 failure
*/
extern int ks_del1(kstring_t *ks,
                   const char *s)
    __NONNULL_ALL;

/*!
 @brief          replace src to ss from kstring_t
 @param[in]      ks: pointer of kstring_t
 @param[in]      old: old substring
 @param[in]      new: new substring
 @param[in]      l: length of new substring
 @return         count of substring replaced
*/
extern size_t ks_mod_(kstring_t *ks,
                      const char *old,
                      const char *new,
                      size_t l)
    __NONNULL((1, 2, 3));

/*!
 @brief          replace src to ss from kstring_t
 @param[in]      ks: pointer of kstring_t
 @param[in]      old: old substring
 @param[in]      new: new substring
 @return         count of substring replaced
*/
extern size_t ks_mod(kstring_t *ks,
                     const char *old,
                     const char *new)
    __NONNULL_ALL;

/*!
 @brief          replace src to ss from kstring_t once
 @param[in]      ks: pointer of kstring_t
 @param[in]      old: old substring
 @param[in]      new: new substring
 @param[in]      l: length of new substring
 @return         count of substring replaced
*/
extern int ks_mod1_(kstring_t *ks,
                    const char *old,
                    const char *new,
                    size_t l)
    __NONNULL((1, 2, 3));

/*!
 @brief          replace src to ss from kstring_t once
 @param[in]      ks: pointer of kstring_t
 @param[in]      old: old substring
 @param[in]      new: new substring
 @param[in]      l: length of new substring
 @return         count of substring replaced
*/
extern int ks_mod1(kstring_t *ks,
                   const char *old,
                   const char *new)
    __NONNULL_ALL;

__END_DECLS

__RESULT_USE_CHECK
__STATIC_INLINE
/*!
 @brief          calloc kstring_t
 @return         kstring_t *
*/
kstring_t *ks_init(void)
{
    return (kstring_t *)calloc(1U, sizeof(kstring_t));
}

__STATIC_INLINE
/*!
 @brief          free kstring_t pointer
 @param[in]      ks: pointer of kstring_t
*/
void ks_free(kstring_t *ks)
{
    if (ks)
    {
        if (ks->s)
        {
            free(ks->s);
            ks->s = NULL;
        }
        free(ks);
    }
}

__NONNULL((1))
__STATIC_INLINE
/*!
 @brief          resize kstring memory
 @param[in]      ks: pointer of kstring_t
 @param[in]      m: size of new memory
 @return         The execution state of the function
  @retval        0  success
  @retval        -1 failure
*/
int ks_resize(kstring_t *ks,
              size_t m)
{
    if (ks->m < m)
    {
        ks->m = m;
        kroundup32(ks->m);
        void *s = realloc(ks->s, ks->m);
        if (s)
        {
            ks->s = (char *)s;
        }
        else
        {
            return -1;
        }
    }
    return 0;
}

__NONNULL((1))
__STATIC_INLINE
/*!
 @brief          resize kstring memory
 @param[in]      ks: pointer of kstring_t
 @param[in]      m: size of new memory
 @return         The execution state of the function
  @retval        0  success
  @retval        -1 failure
*/
int ks_resize_(kstring_t *ks,
               size_t m)
{
    ks->m = m;
    kroundup32(ks->m);
    void *s = realloc(ks->s, ks->m);
    if (s)
    {
        ks->s = (char *)s;
    }
    else
    {
        return -1;
    }
    return 0;
}

__NONNULL_ALL
__STATIC_INLINE
/*!
 @brief          get pointer of kstring_t string
 @param[in]      ks: pointer of kstring_t
 @return         pointer of kstring_t string
*/
char *ks_str(kstring_t *ks)
{
    return ks->s;
}

__NONNULL_ALL
__STATIC_INLINE
/*!
 @brief          get length of kstring_t string
 @param[in]      ks: pointer of kstring_t
 @return         length of kstring_t string
*/
size_t ks_len(kstring_t *ks)
{
    return ks->l;
}

__NONNULL_ALL
__STATIC_INLINE
/*!
 @brief          release kstring_t
 @note           Give ownership of underlying buffer away to something else
                 (making that something else responsible for freeing it),
                 leaving kstring_t empty and ready to be used again, or
                 ready to go out of scope without needing  free(str.s)  to
                 prevent a memory leak.
 @param[in]      ks: pointer of kstring_t
 @return         pointer of kstring_t string
*/
char *ks_release(kstring_t *ks)
{
    char *s = ks->s;
    ks->l = 0U;
    ks->m = 0U;
    ks->s = NULL;
    return s;
}

__NONNULL((1, 2))
__STATIC_INLINE
/*!
 @brief          put n characters to s
 @param[in]      ks: pointer of kstring_t
 @param[in]      p: pointer of data
 @param[in]      l: number of data
 @return         The execution state of the function
  @retval        0  success
  @retval        -1 failure
*/
int kputsn(kstring_t *ks,
           const char *p,
           size_t l)
{
    if (ks_resize(ks, ks->l + l + 1U))
    {
        return -1;
    }
    (void)memcpy(ks->s + ks->l, p, l);
    ks->l += l;
    ks->s[ks->l] = 0;
    return 0;
}

__NONNULL((1, 2))
__STATIC_INLINE
/*!
 @brief          put n characters to s
 @param[in]      ks: pointer of kstring_t
 @param[in]      p: pointer of data
 @param[in]      l: number of data
 @return         The execution state of the function
  @retval        0  success
  @retval        -1 failure
*/
int kputsn_(kstring_t *ks,
            const void *p,
            size_t l)
{
    if (ks_resize(ks, ks->l + l))
    {
        return -1;
    }
    (void)memcpy(ks->s + ks->l, p, l);
    ks->l += l;
    return 0;
}

__NONNULL_ALL
__STATIC_INLINE
/*!
 @brief          put string to s
 @param[in]      ks: pointer of kstring_t
 @param[in]      p: string
 @return         The execution state of the function
  @retval        0  success
  @retval        -1 failure
*/
int kputs(kstring_t *ks,
          const char *p)
{
    return kputsn(ks, p, strlen(p));
}

__NONNULL((1))
__STATIC_INLINE
/*!
 @brief          put a character to kstring_t
 @param[in]      ks: pointer of kstring_t
 @param[in]      c: character
 @return         character
*/
int kputc(kstring_t *ks,
          int c)
{
    if (ks_resize(ks, ks->l + 1U))
    {
        return EOF;
    }
    ks->s[ks->l++] = (char)c;
    ks->s[ks->l] = 0;
    return c;
}

__NONNULL((1))
__STATIC_INLINE
/*!
 @brief          put a character to kstring_t
 @param[in]      ks: pointer of kstring_t
 @param[in]      c: character
 @return         character
*/
int kputc_(kstring_t *ks,
           int c)
{
    if (ks_resize(ks, ks->l + 1U))
    {
        return EOF;
    }
    ks->s[ks->l++] = (char)c;
    return c;
}

__NONNULL((1))
__STATIC_INLINE
/*!
 @brief          put int to kstring_t
 @param[in]      ks: pointer of kstring_t
 @param[in]      c: int data
 @return         The execution state of the function
  @retval        0  success
  @retval        -1 failure
*/
int kputw(kstring_t *ks,
          int c)
{
    char buf[16U] = {0};
    unsigned int l = 0U;
    int x = c;
    if (c < 0)
    {
        x = -x;
    }
    do
    {
        buf[l++] = (char)(x % 10 + '0');
        x /= 10;
    } while (x > 0);
    if (c < 0)
    {
        buf[l++] = '-';
    }
    if (ks_resize(ks, ks->l + l + 1U))
    {
        return -1;
    }
    for (unsigned int i = l - 1U; i < l; --i)
    {
        ks->s[ks->l++] = buf[i];
    }
    ks->s[ks->l] = 0;
    return 0;
}

__NONNULL((1))
__STATIC_INLINE
/*!
 @brief          put unsigned int to kstring_t
 @param[in]      ks: pointer of kstring_t
 @param[in]      c: unsigned int data
 @return         The execution state of the function
  @retval        0  success
  @retval        -1 failure
*/
int kputuw(kstring_t *ks,
           unsigned int c)
{
    char buf[16U] = {0};
    unsigned int l = 0U;
    unsigned int x = c;
    if (c == 0U)
    {
        return kputc(ks, '0');
    }
    for (l = 0U; x; x /= 10U)
    {
        buf[l++] = (char)(x % 10U + '0');
    }
    if (ks_resize(ks, ks->l + l + 1U))
    {
        return -1;
    }
    for (unsigned int i = l - 1U; i < l; --i)
    {
        ks->s[ks->l++] = buf[i];
    }
    ks->s[ks->l] = 0;
    return 0;
}

__NONNULL((1))
__STATIC_INLINE
/*!
 @brief          put long int to kstring_t
 @param[in]      ks: pointer of kstring_t
 @param[in]      c: long int data
 @return         The execution state of the function
  @retval        0  success
  @retval        -1 failure
*/
int kputl(kstring_t *ks,
          long c)
{
    char buf[32U] = {0};
    unsigned int l = 0U;
    long int x = c;
    if (c < 0L)
    {
        x = -x;
    }
    do
    {
        buf[l++] = (char)(x % 10L + '0');
        x /= 10L;
    } while (x > 0L);
    if (c < 0L)
    {
        buf[l++] = '-';
    }
    if (ks_resize(ks, ks->l + l + 1U))
    {
        return -1;
    }
    for (unsigned int i = l - 1U; i < l; --i)
    {
        ks->s[ks->l++] = buf[i];
    }
    ks->s[ks->l] = 0;
    return 0;
}

__NONNULL((1))
__STATIC_INLINE
/*!
 @brief          put unsigned long int to kstring_t
 @param[in]      ks: pointer of kstring_t
 @param[in]      c: unsigned long int data
 @return         The execution state of the function
  @retval        0  success
  @retval        -1 failure
*/
int kputul(kstring_t *ks,
           unsigned long int c)
{
    char buf[32U] = {0};
    unsigned int l = 0U;
    unsigned long int x = c;
    if (c == 0U)
    {
        return kputc(ks, '0');
    }
    for (l = 0U; x; x /= 10U)
    {
        buf[l++] = (char)(x % 10U + '0');
    }
    if (ks_resize(ks, ks->l + l + 1U))
    {
        return -1;
    }
    for (unsigned int i = l - 1U; i < l; --i)
    {
        ks->s[ks->l++] = buf[i];
    }
    ks->s[ks->l] = 0;
    return 0;
}

/* Enddef to prevent recursive inclusion */
#endif /* __KSTRING_H__ */

/* END OF FILE */
