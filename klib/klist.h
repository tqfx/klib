/*!
 @file           klist.h
 @brief          Generic single-linked list and memory pool
 @author         tqfx tqfx@foxmail.com
 @version        0
 @date           2021-05-31
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
#ifndef __KLIST_H__
#define __KLIST_H__

#include "klib.h"

#include <stdlib.h>

/* kmempool_type */
#ifndef kmempool_type
/*!
 @brief          Register type of memory pool structure
 @param[in]      name: identity name of memory pool structure
 @param[in]      type: type of memory pool data
*/
#define kmempool_type(name, type)                       \
    typedef struct kmp_##name##_t                       \
    {                                                   \
        size_t cnt; /* count of alloc memory         */ \
        size_t n;   /* number of unused memory       */ \
        size_t m;   /* size of real memory           */ \
        type **p;   /* first address of pointer list */ \
    } kmp_##name##_t
#endif /* kmempool_type */

/* kmempool_t */
#ifndef kmempool_t
/*!
 @brief          typedef of memory pool registration
 @param[in]      name: identity name of memory pool structure
*/
#define kmempool_t(name) kmp_##name##_t
#endif /* kmempool_t */

/* kmempool_s */
#ifndef kmempool_s
/*!
 @brief          Anonymous structure of memory pool
 @param[in]      type: type of memory pool data
*/
#define kmempool_s(type)                                \
    struct                                              \
    {                                                   \
        size_t cnt; /* count of alloc memory         */ \
        size_t n;   /* number of unused memory       */ \
        size_t m;   /* size of real memory           */ \
        type **p;   /* first address of pointer list */ \
    }
#endif /* kmempool_s */

/* kmp_init */
#ifndef kmp_init
/*!
 @brief          Initialize memory pool structure
 @param[in]      kmp: memory pool structure
*/
#define kmp_init(kmp) \
    (/**/             \
     (kmp).cnt = 0U,  \
     (kmp).n = 0U,    \
     (kmp).m = 0U,    \
     (kmp).p = NULL /**/)
#endif /* kmp_init */

/* kmp_pinit */
#ifndef kmp_pinit
/*!
 @brief          Initialize pointer of memory pool structure
 @param[in]      name: identity name of memory pool structure
 @param[out]     pkmp: pointer of memory pool structure
*/
#define kmp_pinit(name, pkmp)                                 \
    (/**/ (pkmp) = (kmp_##name##_t *)malloc(sizeof(*(pkmp))), \
     kmp_init(*(pkmp)) /**/)
#endif /* kmp_pinit */

/* kmp_clear */
#ifndef kmp_clear
/*!
 @brief          Clear memory pool struture
 @param[in]      func: function that free data
 @param[in]      kmp: memory pool structure
*/
#define kmp_clear(func, kmp)         \
                                     \
    do                               \
    {                                \
        while ((kmp).n)              \
        {                            \
            --(kmp).n;               \
            func((kmp).p[(kmp).n]);  \
            free((kmp).p[(kmp).n]);  \
            (kmp).p[(kmp).n] = NULL; \
        }                            \
        if ((kmp).m)                 \
        {                            \
            free((kmp).p);           \
            (kmp).p = NULL;          \
            (kmp).m = 0U;            \
        }                            \
    } while (0)
#endif /* kmp_clear */

/* kmp_pclear */
#ifndef kmp_pclear
/*!
 @brief          Clear memory pool pointer
 @param[in]      func: function that free data
 @param[in]      pkmp: pointer of memory pool structure
*/
#define kmp_pclear(func, pkmp)    \
                                  \
    do                            \
    {                             \
        kmp_clear(func, *(pkmp)); \
        free(pkmp);               \
        (pkmp) = NULL;            \
    } while (0)
#endif /* kmp_pclear */

/* kmp_alloc */
#ifndef kmp_alloc
/*!
 @brief          Memory pool structure allocate
 @param[in]      type: type of memory pool data
 @param[in]      kmp: memory pool structure
 @return         type *
*/
#define kmp_alloc(type, kmp)              \
                                          \
    (/**/ ++(kmp).cnt,                    \
     (kmp).n                              \
         ? /* n > 0 */ (kmp).p[--(kmp).n] \
         : /* n = 0 */ (type *)calloc(1U, sizeof(**(kmp).p)) /**/)
#endif /* kmp_alloc */

/* kmp_palloc */
#ifndef kmp_palloc
/*!
 @brief          Memory pool pointer allocate
 @param[in]      type: type of memory pool data
 @param[in]      pkmp: pointer of memory pool structure
 @return         type *
*/
#define kmp_palloc(type, pkmp) kmp_alloc(type, *(pkmp))
#endif /* kmp_palloc */

/* kmp_free */
#ifndef kmp_free
/*!
 @brief          Memory pool structure free
 @param[in]      type: type of memory pool data
 @param[in]      kmp: memory pool structure
 @param[in]      pdat: pointer that free data
*/
#define kmp_free(type, kmp, pdat)                             \
                                                              \
    (/**/ --(kmp).cnt,                                        \
     (kmp).n == (kmp).m                                       \
         ? (/* n == m */                                      \
            (kmp).m =                                         \
                ((kmp).m                                      \
                     ? /* m > 0 */ (kmp).m << 1U              \
                     : /* m == 0 */ 16U),                     \
            (kmp).p = (type **)                               \
                realloc((kmp).p, sizeof(*(kmp).p) * (kmp).m), \
            0)                                                \
         : (/* n != m */ 0),                                  \
     (kmp).p[(kmp).n++] = (pdat) /**/)
#endif /* kmp_free */

/* kmp_pfree */
#ifndef kmp_pfree
/*!
 @brief          Memory pool pointer free
 @param[in]      type: type of memory pool data
 @param[in]      pkmp: pointer of memory pool structure
 @param[in]      pdat: pointer that free data
*/
#define kmp_pfree(type, pkmp, pdat) kmp_free(type, *(pkmp), pdat)
#endif /* kmp_pfree */

/* klist1_type */
#ifndef klist1_type
/*!
 @brief          Register type of singly list structure
 @param[in]      name: identity name of singly list structure
 @param[in]      type: type of Singly list data
*/
#define klist1_type(name, type)                                      \
    typedef struct kl1_##name##_t                                    \
    {                                                                \
        struct kl1_##name##_t *next; /* address of next node      */ \
        type data;                   /* variable that stores data */ \
    } kl1_##name##_t
#endif /* klist1_type */

/* klist1_t */
#ifndef klist1_t
/*!
 @brief          typedef of singly list registration
 @param[in]      name: identity name of singly list structure
*/
#define klist1_t(name) kl1_##name##_t
#endif /* klist1_t */

/* kl1_v */
#ifndef kl1_v
/*!
 @brief          data of singly list structure
 @param[in]      kl1: singly list structure
*/
#define kl1_v(kl1) (kl1).data
#endif /* kl1_v */

/* kl1_pv */
#ifndef kl1_pv
/*!
 @brief          data of singly list pointer
 @param[in]      pkl1: pointer of singly list structure
*/
#define kl1_pv(pkl1) kl1_v(*(pkl1))
#endif /* kl1_v */

/* kl1_next */
#ifndef kl1_next
/*!
 @brief          next node of singly list structure
 @param[in]      kl1: singly list structure
*/
#define kl1_next(kl1) (kl1).next
#endif /* kl1_next */

/* kl1_pnext */
#ifndef kl1_pnext
/*!
 @brief          next node of singly list pointer
 @param[in]      pkl1: pointer of singly list structure
*/
#define kl1_pnext(pkl1) kl1_next(*(pkl1))
#endif /* kl1_pnext */

/* klist_type */
#ifndef klist_type
/*!
 @brief          Register type of link list structure
 @param[in]      name: identity name of link list structure
*/
#define klist_type(name)                                   \
    typedef struct kl_##name##_t                           \
    {                                                      \
        size_t size;          /* count of node      */     \
        kl1_##name##_t *head; /* head address of list   */ \
        kl1_##name##_t *tail; /* tail address of list   */ \
        kmp_##name##_t *kmp;  /* address of memory pool */ \
    } kl_##name##_t
#endif /* klist_type */

/* klist_t */
#ifndef klist_t
/*!
 @brief          typedef of link list registration
 @param[in]      name: identity name of link list structure
*/
#define klist_t(name) kl_##name##_t
#endif /* klist_t */

/* klist_s */
#ifndef klist_s
/*!
 @brief          Anonymous structure of link list
 @param[in]      name: identity name of link list structure
*/
#define klist_s(name)                                      \
    struct                                                 \
    {                                                      \
        size_t size;          /* count of node          */ \
        kl1_##name##_t *head; /* head address of list   */ \
        kl1_##name##_t *tail; /* tail address of list   */ \
        kmp_##name##_t *kmp;  /* address of memory pool */ \
    }
#endif /* klist_s */

/* kl_begin */
#ifndef kl_begin
/*!
 @brief          begin node of link list structure
 @param[in]      kl: link list structure
*/
#define kl_begin(kl) (kl).head
#endif /* kl_begin */

/* kl_pbegin */
#ifndef kl_pbegin
/*!
 @brief          begin node of link list pointer
 @param[in]      pkl: pointer of link list structure
*/
#define kl_pbegin(pkl) kl_begin(*(pkl))
#endif /* kl_pbegin */

/* kl_end */
#ifndef kl_end
/*!
 @brief          end node of link list structure
 @param[in]      kl: link list structure
*/
#define kl_end(kl) (kl).tail
#endif /* kl_end */

/* kl_pend */
#ifndef kl_pend
/*!
 @brief          end node of link list pointer
 @param[in]      pkl: pointer of link list structure
*/
#define kl_pend(pkl) kl_end(*(pkl))
#endif /* kl_pend */

/* kl_init */
#ifndef kl_init
/*!
 @brief          Initialize link list structure
 @param[in]      name: identity name of link list structure
 @param[in]      kl: link list structure
*/
#define kl_init(name, kl)                              \
    (/**/ (kl).size = 0U,                              \
     kmp_pinit(name, (kl).kmp),                        \
     (kl).tail = kmp_palloc(kl1_##name##_t, (kl).kmp), \
     (kl).head = (kl).tail,                            \
     (kl).head->next = NULL /**/)
#endif /* kl_init */

/* kl_pinit */
#ifndef kl_pinit
/*!
 @brief          Initialize link list pointer
 @param[in]      name: identity name of link list structure
 @param[out]     pkl: pointer of link list structure
*/
#define kl_pinit(name, pkl)                                \
    (/**/ (pkl) = (kl_##name##_t *)malloc(sizeof(*(pkl))), \
     kl_init(name, *(pkl)) /**/)
#endif /* kl_pinit */

/* kl_clear */
#ifndef kl_clear
/*!
 @brief          Clear link list structure
 @param[in]      name: identity name of link list structure
 @param[in]      func: function that free data
 @param[in]      kl: link list structure
*/
#define kl_clear(name, func, kl)                            \
    do                                                      \
    {                                                       \
        while ((kl).head != (kl).tail)                      \
        {                                                   \
            kmp_pfree(kl1_##name##_t, (kl).kmp, (kl).head); \
            (kl).head = (kl).head->next;                    \
        }                                                   \
        kmp_pfree(kl1_##name##_t, (kl).kmp, (kl).tail);     \
        kmp_pclear(func, (kl).kmp);                         \
        (kl).size = 0U;                                     \
    } while (0)
#endif /* kl_clear */

/* kl_pclear */
#ifndef kl_pclear
/*!
 @brief          Clear link list pointer
 @param[in]      name: identity name of link list structure
 @param[in]      func: function that free data
 @param[in]      pkl: pointer of link list structure
*/
#define kl_pclear(name, func, pkl)    \
    do                                \
    {                                 \
        kl_clear(name, func, *(pkl)); \
        free(pkl);                    \
        (pkl) = NULL;                 \
    } while (0)
#endif /* kl_pclear */

/* kl_push */
#ifndef kl_push
/*!
 @brief          Push data to link list structure
 @param[in]      name: identity name of link list structure
 @param[in]      kl: link list structure
 @param[in]      x: data whose pushed
*/
#define kl_push(name, kl, x)                                 \
    (/**/ ++(kl).size,                                       \
     (kl).tail->next = kmp_palloc(kl1_##name##_t, (kl).kmp), \
     (kl).tail->next->next = NULL,                           \
     (kl).tail->data = (x),                                  \
     (kl).tail = (kl).tail->next /**/)
#endif /* kl_push */

/* kl_ppush */
#ifndef kl_ppush
/*!
 @brief          Push data to link list pointer
 @param[in]      name: identity name of link list structure
 @param[in]      pkl: pointer of link list structure
 @param[in]      x: data whose pushed
*/
#define kl_ppush(name, pkl, x) kl_push(name, *(pkl), x)
#endif /* kl_ppush */

/* kl_pushp */
#ifndef kl_pushp
/*!
 @brief          Get address of stored data variable
 @param[in]      name: identity name of link list structure
 @param[in]      kl: link list structure
 @param[out]     px: pointer that stores data address
*/
#define kl_pushp(name, kl, px)                               \
    (/**/ ++(kl).size,                                       \
     (kl).tail->next = kmp_palloc(kl1_##name##_t, (kl).kmp), \
     (kl).tail->next->next = NULL,                           \
     (px) = &(kl).tail->data,                                \
     (kl).tail = (kl).tail->next /**/)
#endif /* kl_pushp */

/* kl_ppushp */
#ifndef kl_ppushp
/*!
 @brief          Get address of stored data variable
 @param[in]      name: identity name of link list structure
 @param[in]      pkl: pointer of link list structure
 @param[out]     px: pointer that stores data address
*/
#define kl_ppushp(name, pkl, px) kl_pushp(name, *(pkl), px)
#endif /* kl_ppushp */

/* kl_shift */
#ifndef kl_shift
/*!
 @brief          Shift data to variable from link list structure
 @param[in]      name: identity name of link list structure
 @param[in]      kl: link list structure
 @param[out]     x: variable that stores data
 @return         The execution state of the function
  @retval        0  success
  @retval        -1 failure
*/
#define kl_shift(name, kl, x)                               \
    (/**/ (kl).head->next                                   \
         ? (/* head->next != NULL */                        \
            --(kl).size,                                    \
            (x) = (kl).head->data,                          \
            kmp_pfree(kl1_##name##_t, (kl).kmp, (kl).head), \
            (kl).head = (kl).head->next,                    \
            0)                                              \
         : (/* head->next == NULL */ -1) /**/)
#endif /* kl_shift */

/* kl_pshift */
#ifndef kl_pshift
/*!
 @brief          Shift data to variable from link list pointer
 @param[in]      name: identity name of link list structure
 @param[in]      pkl: pointer of link list structure
 @param[out]     x: variable that stores data
 @return         The execution state of the function
  @retval        0  success
  @retval        -1 failure
*/
#define kl_pshift(name, pkl, x) kl_shift(name, *(pkl), x)
#endif /* kl_pshift */

/* kl_shiftp */
#ifndef kl_shiftp
/*!
 @brief          Get shift data address to variable from link list structure
 @param[in]      name: identity name of link list structure
 @param[in]      kl: link list structure
 @param[out]     px: pointer that stores data variable
 @return         The execution state of the function
  @retval        0  success
  @retval        -1 failure
*/
#define kl_shiftp(name, kl, px)                             \
    (/**/ (kl).head->next                                   \
         ? (/* head->next != NULL */                        \
            --(kl).size,                                    \
            (px) = &(kl).head->data,                        \
            kmp_pfree(kl1_##name##_t, (kl).kmp, (kl).head), \
            (kl).head = (kl).head->next,                    \
            0)                                              \
         : (/* head->next == NULL */ -1) /**/)
#endif /* kl_shiftp */

/* kl_pshiftp */
#ifndef kl_pshiftp
/*!
 @brief          Get shift data address to variable from link list pointer
 @param[in]      name: identity name of link list structure
 @param[in]      pkl: pointer of link list structure
 @param[out]     px: pointer that stores data variable
 @return         The execution state of the function
  @retval        0  success
  @retval        -1 failure
*/
#define kl_pshiftp(name, pkl, px) kl_shiftp(name, *(pkl), px)
#endif /* kl_pshift */

/* __KMEMPOOL_IMPL */
#undef __KMEMPOOL_IMPL
#define __KMEMPOOL_IMPL(SCOPE, NAME, TYPE, FUNC)            \
                                                            \
    __NONNULL_ALL                                           \
    SCOPE                                                   \
    void kmp_##NAME##_init(kmp_##NAME##_t *kmp)             \
    {                                                       \
        kmp->cnt = 0U;                                      \
        kmp->n = 0U;                                        \
        kmp->m = 0U;                                        \
        kmp->p = NULL;                                      \
    }                                                       \
                                                            \
    __NONNULL_ALL                                           \
    SCOPE                                                   \
    int kmp_##NAME##_pinit(kmp_##NAME##_t **pkmp)           \
    {                                                       \
        *pkmp = (kmp_##NAME##_t *)malloc(sizeof(**pkmp));   \
        if (!*pkmp)                                         \
        {                                                   \
            return -1;                                      \
        }                                                   \
        (*pkmp)->cnt = 0U;                                  \
        (*pkmp)->n = 0U;                                    \
        (*pkmp)->m = 0U;                                    \
        (*pkmp)->p = NULL;                                  \
        return 0;                                           \
    }                                                       \
                                                            \
    __RESULT_USE_CHECK                                      \
    SCOPE                                                   \
    kmp_##NAME##_t *kmp_##NAME##_initp(void)                \
    {                                                       \
        return (kmp_##NAME##_t *)                           \
            calloc(1U, sizeof(kmp_##NAME##_t));             \
    }                                                       \
                                                            \
    __NONNULL_ALL                                           \
    SCOPE                                                   \
    void kmp_##NAME##_clear(kmp_##NAME##_t *kmp)            \
    {                                                       \
        while (kmp->n)                                      \
        {                                                   \
            --kmp->n;                                       \
            FUNC(kmp->p[kmp->n]);                           \
            free(kmp->p[kmp->n]);                           \
            kmp->p[kmp->n] = NULL;                          \
        }                                                   \
        if (kmp->m)                                         \
        {                                                   \
            free(kmp->p);                                   \
            kmp->p = NULL;                                  \
            kmp->m = 0U;                                    \
        }                                                   \
    }                                                       \
                                                            \
    __NONNULL_ALL                                           \
    SCOPE                                                   \
    void kmp_##NAME##_pclear(kmp_##NAME##_t **pkmp)         \
    {                                                       \
        while ((*pkmp)->n)                                  \
        {                                                   \
            --(*pkmp)->n;                                   \
            FUNC((*pkmp)->p[(*pkmp)->n]);                   \
            free((*pkmp)->p[(*pkmp)->n]);                   \
            (*pkmp)->p[(*pkmp)->n] = NULL;                  \
        }                                                   \
        if ((*pkmp)->m)                                     \
        {                                                   \
            free((*pkmp)->p);                               \
            (*pkmp)->p = NULL;                              \
            (*pkmp)->m = 0U;                                \
        }                                                   \
        free(*pkmp);                                        \
        *pkmp = NULL;                                       \
    }                                                       \
                                                            \
    __NONNULL_ALL                                           \
    SCOPE                                                   \
    TYPE *kmp_##NAME##_alloc(kmp_##NAME##_t *kmp)           \
    {                                                       \
        ++kmp->cnt;                                         \
        if (kmp->n)                                         \
        {                                                   \
            return kmp->p[--kmp->n];                        \
        }                                                   \
        else                                                \
        {                                                   \
            return (TYPE *)calloc(1U, sizeof(**kmp->p));    \
        }                                                   \
    }                                                       \
                                                            \
    __NONNULL_ALL                                           \
    SCOPE                                                   \
    int kmp_##NAME##_free(kmp_##NAME##_t *kmp,              \
                          TYPE *pdat)                       \
    {                                                       \
        --kmp->cnt;                                         \
        if (kmp->n == kmp->m)                               \
        {                                                   \
            size_t m = kmp->m ? kmp->m << 1U : 16U;         \
            void *p = realloc(kmp->p, sizeof(*kmp->p) * m); \
            if (p)                                          \
            {                                               \
                kmp->p = (TYPE **)p;                        \
                kmp->m = m;                                 \
            }                                               \
            else                                            \
            {                                               \
                return -1;                                  \
            }                                               \
        }                                                   \
        kmp->p[kmp->n++] = pdat;                            \
        return 0;                                           \
    }

#ifndef kmempool_impl
/*!
 @brief          Memory pool function Initial Microprogram Loading
 @param[in]      scope: scope of function
 @param[in]      name: identity name of memory pool structure
 @param[in]      type: type of memory pool data
 @param[in]      func: function of free data
*/
#define kmempool_impl(scope, name, type, func) \
    __KMEMPOOL_IMPL(scope, name, type, func)
#endif /* kmempool_impl */

/* __KMEMPOOL_INIT */
#undef __KMEMPOOL_INIT
#define __KMEMPOOL_INIT(NAME, TYPE, FUNC) \
    kmempool_type(NAME, TYPE);            \
    __KMEMPOOL_IMPL(__STATIC_INLINE __UNUSED, NAME, TYPE, FUNC)

#ifndef kmempool_init
/*!
 @brief          Memory pool function Initial Microprogram Loading
 @param[in]      name: identity name of memory pool structure
 @param[in]      type: type of memory pool data
 @param[in]      func: function of free data
*/
#define kmempool_init(name, type, func) \
    __KMEMPOOL_INIT(name, type, func)
#endif /* kmempool_init */

/* __KLIST_IMPL */
#undef __KLIST_IMPL
#define __KLIST_IMPL(SCOPE, NAME, TYPE)                   \
                                                          \
    __NONNULL_ALL                                         \
    SCOPE                                                 \
    int kl_##NAME##_init(kl_##NAME##_t *kl)               \
    {                                                     \
        kl->size = 0U;                                    \
        kl->kmp = kmp_##NAME##_initp();                   \
        if (!kl->kmp)                                     \
        {                                                 \
            return -1;                                    \
        }                                                 \
        kl->tail = kmp_##NAME##_alloc(kl->kmp);           \
        kl->head = kl->tail;                              \
        if (!kl->head)                                    \
        {                                                 \
            return -1;                                    \
        }                                                 \
        kl->head->next = NULL;                            \
        return 0;                                         \
    }                                                     \
                                                          \
    __NONNULL_ALL                                         \
    SCOPE                                                 \
    int kl_##NAME##_pinit(kl_##NAME##_t **pkl)            \
    {                                                     \
        *pkl = (kl_##NAME##_t *)malloc(sizeof(**pkl));    \
        if (!*pkl)                                        \
        {                                                 \
            return -1;                                    \
        }                                                 \
        (*pkl)->size = 0U;                                \
        (*pkl)->kmp = kmp_##NAME##_initp();               \
        if (!(*pkl)->kmp)                                 \
        {                                                 \
            return -1;                                    \
        }                                                 \
        (*pkl)->tail = kmp_##NAME##_alloc((*pkl)->kmp);   \
        (*pkl)->head = (*pkl)->tail;                      \
        if (!(*pkl)->tail)                                \
        {                                                 \
            return -1;                                    \
        }                                                 \
        (*pkl)->head->next = NULL;                        \
        return 0;                                         \
    }                                                     \
                                                          \
    __RESULT_USE_CHECK                                    \
    SCOPE                                                 \
    kl_##NAME##_t *kl_##NAME##_initp(void)                \
    {                                                     \
        kl_##NAME##_t *pkl = (kl_##NAME##_t *)            \
            malloc(sizeof(kl_##NAME##_t));                \
        if (!pkl)                                         \
        {                                                 \
            return NULL;                                  \
        }                                                 \
        pkl->size = 0U;                                   \
        pkl->kmp = kmp_##NAME##_initp();                  \
        pkl->tail = kmp_##NAME##_alloc(pkl->kmp);         \
        pkl->head = pkl->tail;                            \
        pkl->head->next = NULL;                           \
        return pkl;                                       \
    }                                                     \
                                                          \
    __NONNULL_ALL                                         \
    SCOPE                                                 \
    void kl_##NAME##_clear(kl_##NAME##_t *kl)             \
    {                                                     \
        while (kl->head != kl->tail)                      \
        {                                                 \
            kmp_##NAME##_free(kl->kmp, kl->head);         \
            kl->head = kl->head->next;                    \
        }                                                 \
        kmp_##NAME##_free(kl->kmp, kl->tail);             \
        kmp_##NAME##_clear(kl->kmp);                      \
        free(kl->kmp);                                    \
        kl->kmp = NULL;                                   \
        kl->size = 0U;                                    \
    }                                                     \
                                                          \
    __NONNULL_ALL                                         \
    SCOPE                                                 \
    void kl_##NAME##_pclear(kl_##NAME##_t **pkl)          \
    {                                                     \
        while ((*pkl)->head != (*pkl)->tail)              \
        {                                                 \
            kmp_##NAME##_free((*pkl)->kmp, (*pkl)->head); \
            (*pkl)->head = (*pkl)->head->next;            \
        }                                                 \
        kmp_##NAME##_free((*pkl)->kmp, (*pkl)->tail);     \
        kmp_##NAME##_clear((*pkl)->kmp);                  \
        free((*pkl)->kmp);                                \
        (*pkl)->kmp = NULL;                               \
        (*pkl)->size = 0U;                                \
        free(*pkl);                                       \
        *pkl = NULL;                                      \
    }                                                     \
                                                          \
    __NONNULL((1))                                        \
    SCOPE                                                 \
    int kl_##NAME##_push(kl_##NAME##_t *kl,               \
                         TYPE x)                          \
    {                                                     \
        kl->tail->next = kmp_##NAME##_alloc(kl->kmp);     \
        if (!kl->tail->next)                              \
        {                                                 \
            return -1;                                    \
        }                                                 \
        kl->tail->next->next = NULL;                      \
        kl->tail->data = x;                               \
        kl->tail = kl->tail->next;                        \
        kl->size++;                                       \
        return 0;                                         \
    }                                                     \
                                                          \
    __NONNULL_ALL                                         \
    __RESULT_USE_CHECK                                    \
    SCOPE                                                 \
    TYPE *kl_##NAME##_pushp(kl_##NAME##_t *kl)            \
    {                                                     \
        kl1_##NAME##_t *p = kl->tail;                     \
        kl->tail->next = kmp_##NAME##_alloc(kl->kmp);     \
        if (!kl->tail->next)                              \
        {                                                 \
            return NULL;                                  \
        }                                                 \
        kl->tail->next->next = NULL;                      \
        kl->tail = kl->tail->next;                        \
        kl->size++;                                       \
        return &p->data;                                  \
    }                                                     \
                                                          \
    __NONNULL_ALL                                         \
    SCOPE                                                 \
    int kl_##NAME##_shift(kl_##NAME##_t *kl,              \
                          TYPE *px)                       \
    {                                                     \
        if (!kl->head->next)                              \
        {                                                 \
            return -1;                                    \
        }                                                 \
        *px = kl->head->data;                             \
        kmp_##NAME##_free(kl->kmp, kl->head);             \
        kl->head = kl->head->next;                        \
        kl->size--;                                       \
        return 0;                                         \
    }

#ifndef klist_impl
/*!
 @brief          List function Initial Microprogram Loading
 @param[in]      scope: scope of function
 @param[in]      name: identity name of link list structure
 @param[in]      type: type of link list data
*/
#define klist_impl(scope, name, type) \
    __KLIST_IMPL(scope, name, type)
#endif /* klist_impl */

/* __KLIST_INIT */
#undef __KLIST_INIT
#define __KLIST_INIT(NAME, TYPE, FUNC)                                    \
    klist1_type(NAME, TYPE);                                              \
    kmempool_type(NAME, klist1_t(NAME));                                  \
    klist_type(NAME);                                                     \
    __KMEMPOOL_IMPL(__STATIC_INLINE __UNUSED, NAME, klist1_t(NAME), FUNC) \
    __KLIST_IMPL(__STATIC_INLINE __UNUSED, NAME, TYPE)

#ifndef klist_init
/*!
 @brief          List function Initial Microprogram Loading
 @param[in]      name: identity name of link list structure
 @param[in]      type: type of link list data
 @param[in]      func: function of free data
*/
#define klist_init(name, type, func) \
    __KLIST_INIT(name, type, func)
#endif /* klist_init */

/* Enddef to prevent recursive inclusion */
#endif /* __KLIST_H__ */

/* END OF FILE */
