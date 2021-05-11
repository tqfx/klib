/**
 * *****************************************************************************
 * @file         kstring.h
 * @brief        string library
 * @details      basic string library
 * @author       tqfx
 * @date         20210421
 * @version      1
 * @copyright    Copyright (C) 2021
 * @code         utf-8                                                  @endcode
 * *****************************************************************************
*/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __KSTRING_H__
#define __KSTRING_H__

#ifndef __STDC_WANT_LIB_EXT1__
#define __STDC_WANT_LIB_EXT1__ 1
#endif /* __STDC_WANT_LIB_EXT1__ */

/* Includes ------------------------------------------------------------------*/
#include "klib.h"

/* Private includes ----------------------------------------------------------*/
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Exported macro ------------------------------------------------------------*/
#undef KS_ATTR_PRINTF

#if __GNUC_PREREQ(2, 4)
#define KS_ATTR_PRINTF(fmt, arg) \
    __attribute__((__format__(__printf__, fmt, arg)))
#else
#define KS_ATTR_PRINTF(fmt, arg)
#endif /* __GNUC__ */

/* Exported types ------------------------------------------------------------*/

/**
 * @struct       kstring_t
 * @brief        c string
*/
typedef struct Kstring
{
    size_t m; /* size of real memory     */
    size_t l; /* length of string        */
    char * s; /* first address of string */
} kstring_t;

/* Exported constants --------------------------------------------------------*/

/* Exported functions prototypes ---------------------------------------------*/

__BEGIN_DECLS

/**
 * @defgroup     printf
 * @{
 * @brief        print string to kstring_t
*/

/**
 * @brief        print string to kstring_t
 * @param[in]    ks: pointer of kstring_t
 * @param[in]    fmt: format
 * @param[in]    ap: va_list
 * @return       int Number of characters
*/
extern int kvsprintf(kstring_t * ks,
                     const char *fmt,
                     va_list     ap)
    KS_ATTR_PRINTF(2, 0);

/**
 * @brief        print string to kstring_t
 * @param[in]    ks: pointer of kstring_t
 * @param[in]    fmt: format
 * @return       int Number of characters
*/
extern int ksprintf(kstring_t * ks,
                    const char *fmt,
                    ...)
    KS_ATTR_PRINTF(2, 3);

/** @} printf */

/**
 * @defgroup     ks_cnt
 * @{
 * @brief        count substring from kstring_t
*/

/**
 * @brief        count substring from kstring_t
 * @param[in]    ks: pointer of kstring_t
 * @param[in]    s: substring
 * @param[in]    l: length of substring
 * @return       size_t count of substring
*/
extern size_t ks_cnt_(const kstring_t *ks,
                      const char *     s,
                      size_t           l)
    __NONNULL((1, 2));

/**
 * @brief        count substring from kstring_t
 * @param[in]    ks: pointer of kstring_t
 * @param[in]    s: substring
 * @return       size_t count of substring
*/
extern size_t ks_cnt(const kstring_t *ks,
                     const char *     s)
    __NONNULL_ALL;

/** @} ks_cnt */

/**
 * @defgroup     ks_ins
 * @{
 * @brief        insert string in kstring_t
*/

/**
 * @brief        insert string in kstring_t
 * @param[in]    ks: pointer of kstring_t
 * @param[in]    s: string need to insert
 * @param[in]    l: length of string
 * @return       int 0(success) -1(failure)
*/
extern int ks_ins_(kstring_t * ks,
                   size_t      i,
                   const char *s,
                   size_t      l)
    __NONNULL((1, 3));

/**
 * @brief        insert string in kstring_t
 * @param[in]    ks: pointer of kstring_t
 * @param[in]    s: string need to insert
 * @return       int 0(success) -1(failure)
*/
extern int ks_ins(kstring_t * ks,
                  size_t      i,
                  const char *s)
    __NONNULL((1, 3));

/** @} ks_ins */

/**
 * @defgroup     ks_del
 * @{
 * @brief        delete substring from kstring_t
*/

/**
 * @brief        delete substring from kstring_t
 * @param[in]    ks: pointer of kstring_t
 * @param[in]    s: substring
 * @param[in]    l: length of substring
 * @return       size_t count of substring deleted
*/
extern size_t ks_del_(kstring_t * ks,
                      const char *s,
                      size_t      l)
    __NONNULL((1, 2));

/**
 * @brief        delete substring from kstring_t
 * @param[in]    ks: pointer of kstring_t
 * @param[in]    s: substring
 * @return       size_t count of substring deleted
*/
extern size_t ks_del(kstring_t * ks,
                     const char *s)
    __NONNULL_ALL;

/**
 * @brief        delete a substring from kstring_t
 * @param[in]    ks: pointer of kstring_t
 * @param[in]    s: substring
 * @param[in]    l: length of substring
 * @return       int 0(success) -1(failure)
*/
extern int ks_del1_(kstring_t * ks,
                    const char *s,
                    size_t      l)
    __NONNULL((1, 2));

/**
 * @brief        delete a substring from kstring_t
 * @param[in]    ks: pointer of kstring_t
 * @param[in]    s: substring
 * @return       int 0(success) -1(failure)
*/
extern int ks_del1(kstring_t * ks,
                   const char *s)
    __NONNULL_ALL;

/** @} ks_del */

/**
 * @defgroup     ks_mod
 * @{
 * @brief        replace src to ss from kstring_t
*/

/**
 * @brief        replace src to ss from kstring_t
 * @param[in]    ks: pointer of kstring_t
 * @param[in]    src: old substring
 * @param[in]    s: new substring
 * @param[in]    l: length of new substring
 * @return       size_t count of substring replaced
*/
extern size_t ks_mod_(kstring_t * ks,
                      const char *src,
                      const char *s,
                      size_t      l)
    __NONNULL((1, 2, 3));

/**
 * @brief        replace src to ss from kstring_t
 * @param[in]    ks: pointer of kstring_t
 * @param[in]    src: old substring
 * @param[in]    s: new substring
 * @return       size_t count of substring replaced
*/
extern size_t ks_mod(kstring_t * ks,
                     const char *src,
                     const char *s)
    __NONNULL_ALL;

/**
 * @brief        replace src to ss from kstring_t once
 * @param[in]    ks: pointer of kstring_t
 * @param[in]    src: old substring
 * @param[in]    s: new substring
 * @param[in]    l: length of new substring
 * @return       size_t count of substring replaced
*/
extern int ks_mod1_(kstring_t * ks,
                    const char *src,
                    const char *s,
                    size_t      l)
    __NONNULL((1, 2, 3));

/**
 * @brief        replace src to ss from kstring_t once
 * @param[in]    ks: pointer of kstring_t
 * @param[in]    src: old substring
 * @param[in]    s: new substring
 * @param[in]    l: length of new substring
 * @return       size_t count of substring replaced
*/
extern int ks_mod1(kstring_t * ks,
                   const char *src,
                   const char *s)
    __NONNULL_ALL;

__END_DECLS

/* Private defines -----------------------------------------------------------*/

/**
 * @defgroup     ks
 * @{
 * @brief        ks static inline functions
*/

__RESULT_USE_CHECK
/**
 * @brief        calloc kstring_t
 * @param[in]    none
 * @return       kstring_t *
*/
static inline kstring_t *ks_init(void)
{
    return (kstring_t *)calloc(1U, sizeof(kstring_t));
}

/**
 * @brief        free kstring_t pointer
 * @param[in]    ks: pointer of kstring_t
 * @return       none
*/
static inline void ks_free(kstring_t *ks)
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
/**
 * @brief        resize kstring memory
 * @param[in]    ks: pointer of kstring_t
 * @param[in]    m: size of new memory
 * @return       int 0(success) -1(failure)
*/
static inline int ks_resize(kstring_t *ks,
                            size_t     m)
{
    if (ks->m < m)
    {
        ks->m = m;
        __KROUNDUP32(ks->m);
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
/**
 * @brief        resize kstring memory
 * @param[in]    ks: pointer of kstring_t
 * @param[in]    m: size of new memory
 * @return       int 0(success) -1(failure)
*/
static inline int ks_resize_(kstring_t *ks,
                             size_t     m)
{
    ks->m = m;
    __KROUNDUP32(ks->m);
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
/**
 * @brief        get pointer of kstring_t string
 * @param[in]    ks: pointer of kstring_t
 * @return       char * pointer of kstring_t string
*/
static inline char *ks_str(kstring_t *ks)
{
    return ks->s;
}

__NONNULL_ALL
/**
 * @brief        get length of kstring_t string
 * @param[in]    ks: pointer of kstring_t
 * @return       size_t length of kstring_t string
*/
static inline size_t ks_len(kstring_t *ks)
{
    return ks->l;
}

__NONNULL_ALL
/**
 * @brief        release kstring_t
 * @note         Give ownership of underlying buffer away to something else
 *               (making that something else responsible for freeing it),
 *               leaving kstring_t empty and ready to be used again, or
 *               ready to go out of scope without needing  free(str.s)  to
 *               prevent a memory leak.
 * @param[in]    ks: pointer of kstring_t
 * @return       char * pointer of kstring_t string
*/
static inline char *ks_release(kstring_t *ks)
{
    char *s = ks->s;
    ks->l   = 0U;
    ks->m   = 0U;
    ks->s   = NULL;
    return s;
}

/** @} ks */

/**
 * @defgroup     kputs
 * @{
 * @brief        put string to ksting_t
*/

__NONNULL((1, 3))
/**
 * @brief        put n characters to s
 * @param[in]    p: pointer of data
 * @param[in]    l: number of data
 * @param[in]    ks: pointer of kstring_t
 * @return       int 0(success) -1(failure)
*/
static inline int kputsn(const char *p,
                         size_t      l,
                         kstring_t * ks)
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

__NONNULL((1, 3))
/**
 * @brief        put n characters to s
 * @param[in]    p: pointer of data
 * @param[in]    l: number of data
 * @param[in]    ks: pointer of kstring_t
 * @return       int 0(success) -1(failure)
*/
static inline int kputsn_(const void *p,
                          size_t      l,
                          kstring_t * ks)
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
/**
 * @brief        put string to s
 * @param[in]    p: string
 * @param[in]    ks: pointer of kstring_t
 * @return       int 0(success) -1(failure)
*/
static inline int kputs(const char *p,
                        kstring_t * ks)
{
    return kputsn(p, strlen(p), ks);
}

__NONNULL((2))
/**
 * @brief        put a character to kstring_t
 * @param[in]    c: character
 * @param[in]    ks: pointer of kstring_t
 * @return       int character
*/
static inline int kputc(int        c,
                        kstring_t *ks)
{
    if (ks_resize(ks, ks->l + 1U))
    {
        return EOF;
    }
    ks->s[ks->l++] = (char)c;
    ks->s[ks->l]   = 0;
    return c;
}

__NONNULL((2))
/**
 * @brief        put a character to kstring_t
 * @param[in]    c: character
 * @param[in]    ks: pointer of kstring_t
 * @return       int character
*/
static inline int kputc_(int        c,
                         kstring_t *ks)
{
    if (ks_resize(ks, ks->l + 1U))
    {
        return EOF;
    }
    ks->s[ks->l++] = (char)c;
    return c;
}

/** @} kputs */

/**
 * @defgroup     kput
 * @{
 * @brief        put num to ksting_t
*/

__NONNULL((2))
/**
 * @brief        put int to kstring_t
 * @param[in]    c: int data
 * @param[in]    ks: pointer of kstring_t
 * @return       int 0(success) -1(failure)
*/
static inline int kputw(int        c,
                        kstring_t *ks)
{
    char         buf[16U] = {0};
    unsigned int l        = 0U;
    int          x        = c;
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

__NONNULL((2))
/**
 * @brief        put unsigned int to kstring_t
 * @param[in]    c: unsigned int data
 * @param[in]    ks: pointer of kstring_t
 * @return       int 0(success) -1(failure)
*/
static inline int kputuw(unsigned int c,
                         kstring_t *  ks)
{
    char         buf[16U] = {0};
    unsigned int l        = 0U;
    unsigned int x        = c;
    if (c == 0U)
    {
        return kputc('0', ks);
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

__NONNULL((2))
/**
 * @brief        put long int to kstring_t
 * @param[in]    c: long int data
 * @param[in]    ks: pointer of kstring_t
 * @return       int 0(success) -1(failure)
*/
static inline int kputl(long       c,
                        kstring_t *ks)
{
    char         buf[32U] = {0};
    unsigned int l        = 0U;
    long int     x        = c;
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

__NONNULL((2))
/**
 * @brief        put unsigned long int to kstring_t
 * @param[in]    c: unsigned long int data
 * @param[in]    ks: pointer of kstring_t
 * @return       int 0(success) -1(failure)
*/
static inline int kputul(unsigned long int c,
                         kstring_t *       ks)
{
    char              buf[32U] = {0};
    unsigned int      l        = 0U;
    unsigned long int x        = c;
    if (c == 0U)
    {
        return kputc('0', ks);
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

/** @} kput */

/* __KSTRING_H__ -------------------------------------------------------------*/
#endif /* __KSTRING_H__ */

/************************ (C) COPYRIGHT tqfx *******************END OF FILE****/
