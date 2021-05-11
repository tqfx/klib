/**
 * *****************************************************************************
 * @file         kstring.c
 * @brief        string library
 * @details      basic string library
 * @author       tqfx
 * @date         20210421
 * @version      1
 * @copyright    Copyright (C) 2021
 * @code         utf-8                                                  @endcode
 * *****************************************************************************
*/

/* Includes ------------------------------------------------------------------*/
#include "kstring.h"

/* Private includes ----------------------------------------------------------*/
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private user code ---------------------------------------------------------*/

/**
 * @defgroup     printf
 * @{
 * @brief        print string to kstring_t
*/

int kvsprintf(kstring_t * ks,
              const char *fmt,
              va_list     ap)
{
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

int ksprintf(kstring_t * ks,
             const char *fmt,
             ...)
{
    va_list ap;

    va_start(ap, fmt);
    int l = kvsprintf(ks, fmt, ap);
    va_end(ap);

    return l;
}

/** @} printf */

/**
 * @defgroup     ks_cnt
 * @{
 * @brief        count substring from kstring_t
*/

size_t ks_cnt_(const kstring_t *ks,
               const char *     s,
               size_t           l)
{
    /* when l is 0, it will goes into an infinite cycle */
    if (!l)
    {
        return 0U;
    }

    size_t count = 0U;
    char * p     = ks->s;
    while ((p = strstr(p, s)))
    {
        p += l;
        ++count;
    }
    return count;
}

size_t ks_cnt(const kstring_t *ks,
              const char *     s)
{
    return ks_cnt_(ks, s, strlen(s));
}

/** @} ks_cnt */

/**
 * @defgroup     ks_ins
 * @{
 * @brief        insert string in kstring_t
*/

int ks_ins_(kstring_t * ks,
            size_t      i,
            const char *s,
            size_t      l)
{
    if (ks_resize(ks, ks->l + l + 1U))
    {
        return -1;
    }

    i = i > ks->l ? ks->l : i;
    (void)memmove(ks->s + i + l, ks->s + i, ks->l + 1U - i);
    (void)memcpy(ks->s + i, s, l);
    ks->l += l;
    return 0;
}

int ks_ins(kstring_t *ks, size_t i, const char *s)
{
    return ks_ins_(ks, i, s, strlen(s));
}

/** @} ks_ins */

/**
 * @defgroup     ks_del
 * @{
 * @brief        delete substring from kstring_t
*/

size_t ks_del_(kstring_t * ks,
               const char *s,
               size_t      l)
{
    /* when l is 0, it will goes into an infinite cycle */
    if (!l)
    {
        return 0U;
    }

    char *ps = strstr(ks->s, s);
    if (!ps)
    {
        return 0U;
    }

    size_t count = 0U;
    size_t j     = (size_t)(ps - ks->s);
    for (size_t i = 0U; ps; j += i)
    {
        ps += l;
        char *p = strstr(ps, s);
        if (p)
        {
            i = (size_t)(p - ps);
        }
        else
        {
            i = (size_t)(ks->l + 1U + ks->s - ps);
        }
        (void)memmove(ks->s + j, ps, i);
        ps = p;
        ++count;
    }

    ks->l = j - 1U;
    (void)ks_resize_(ks, j);
    return count;
}

size_t ks_del(kstring_t * ks,
              const char *s)
{
    return ks_del_(ks, s, strlen(s));
}

int ks_del1_(kstring_t * ks,
             const char *s,
             size_t      l)
{
    /* when l is 0, not need to delete */
    if (!l)
    {
        return -1;
    }

    char *ps = strstr(ks->s, s);
    if (!ps)
    {
        return -1;
    }

    (void)memmove(ps, ps + l, ks->l + 1U - l);
    ks->l -= l;
    return ks_resize_(ks, ks->l + 1U - l);
}

int ks_del1(kstring_t * ks,
            const char *s)
{
    return ks_del1_(ks, s, strlen(s));
}

/** @} ks_del */

/**
 * @defgroup     ks_mod
 * @{
 * @brief        replace src to ss from kstring_t
*/

size_t ks_mod_(kstring_t * ks,
               const char *src,
               const char *s,
               size_t      l)
{
    const size_t n = strlen(src);
    /* when n is 0, it will goes into an infinite cycle */
    if (!n)
    {
        return 0U;
    }

    char * p     = ks->s;
    char * ps    = ks->s;
    size_t count = 0U;

    kstring_t *tmp = ks_init();
    while ((ps = strstr(ps, src)))
    {
        (void)kputsn(p, (size_t)(ps - p), tmp);
        (void)kputsn(s, l, tmp);
        ps += n;
        p = ps;
        ++count;
    }
    (void)kputs(p, tmp);

    if (count)
    {
        free(ks->s);
        (void)memcpy(ks, tmp, sizeof(kstring_t));
    }
    free(tmp);
    tmp = NULL;

    return count;
}

size_t ks_mod(kstring_t * ks,
              const char *src,
              const char *s)
{
    return ks_mod_(ks, src, s, strlen(s));
}

int ks_mod1_(kstring_t *ks, const char *src, const char *s, size_t l)
{
    const size_t n = strlen(src);
    /* when l is 0, not need to delete */
    if (!n)
    {
        return -1;
    }

    char *ps = strstr(ks->s, src);
    if (!ps)
    {
        return -1;
    }

    kstring_t *tmp = ks_init();
    (void)kputsn(ks->s, (size_t)(ps - ks->s), tmp);
    (void)kputsn(s, l, tmp);
    (void)kputs(ps + n, tmp);
    free(ks->s);
    (void)memcpy(ks, tmp, sizeof(kstring_t));
    free(tmp);
    tmp = NULL;

    return 0;
}

int ks_mod1(kstring_t * ks,
            const char *src,
            const char *s)
{
    return ks_mod1_(ks, src, s, strlen(s));
}

/** @} ks_mod */

/************************ (C) COPYRIGHT tqfx *******************END OF FILE****/
