/*!
 @file           kvec.h
 @brief          vector library
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
#ifndef __KVEC_H__
#define __KVEC_H__

#include "klib.h"

#include <stdlib.h>
#include <string.h>

/* kvec_type */
#ifndef kvec_type
/*!
 @brief          Register type of vector structure
 @param[in]      name: identity name of vector structure
 @param[in]      type: type of vector data
*/
#define kvec_type(name, type)                   \
    typedef struct kvec_##name##_t              \
    {                                           \
        size_t n; /* number of elements      */ \
        size_t m; /* size of real memory     */ \
        type *v;  /* first address of vector */ \
    } kvec_##name##_t
#endif /* kvec_type */

/* kvec_t */
#ifndef kvec_t
/*!
 @brief          typedef of vector registration
 @param[in]      name: identity name of vector structure
*/
#define kvec_t(name) kvec_##name##_t
#endif /* kvec_t */

/* kvec_s */
#ifndef kvec_s
/*!
 @brief        Anonymous structure of vector
 @param[in]    type: type of vector data
*/
#define kvec_s(type)                            \
    struct                                      \
    {                                           \
        size_t n; /* number of elements      */ \
        size_t m; /* size of real memory     */ \
        type *v;  /* first address of vector */ \
    }
#endif /* kvec_s */

/* kv_init */
#ifndef kv_init
/*!
 @brief        Initialize vector structure
 @param[in]    kv: vector structure
*/
#define kv_init(kv) \
    (/**/ (kv).n = 0U, (kv).m = 0U, (kv).v = NULL /**/)
#endif /* kv_init */

/* kv_pinit */
#ifndef kv_pinit
/*!
 @brief        Initialize pointer of vector structure
 @param[in]    name: identity name of vector structure
 @param[out]   pkv: pointer of vector structure
*/
#define kv_pinit(name, pkv)                                  \
    (/**/ (pkv) = (kvec_##name##_t *)malloc(sizeof(*(pkv))), \
     kv_init(*(pkv)) /**/)
#endif /* kv_pinit */

/* kv_clear */
#ifndef kv_clear
/*!
 @brief        Free memory of data and clear vector structure
 @param[in]    kv: vector structure
*/
#define kv_clear(kv) \
    (/**/ (kv).n = 0U, (kv).m = 0U, free((kv).v), (kv).v = NULL /**/)
#endif /* kv_clear */

/* kv_pclear */
#ifndef kv_pclear
/*!
 @brief        Free memory and clear pointer of vector structure
 @param[in]    pkv: pointer of vector structure
*/
#define kv_pclear(pkv) \
    (/**/ kv_clear(*(pkv)), free(pkv), (pkv) = NULL /**/)
#endif /* kv_pclear */

/* kv_resize */
#ifndef kv_resize
/*!
 @brief        Resize real memory of data
 @param[in]    type: type of vector data
 @param[in]    kv: vector structure
 @param[in]    n: new size of real memory
*/
#define kv_resize(type, kv, n) \
    (/**/                      \
     (kv).m = (n),             \
     (kv).v = (type *)realloc((kv).v, sizeof(*(kv).v) * (n)) /**/)
#endif /* kv_resize */

/* kv_presize */
#ifndef kv_presize
/*!
 @brief        Resize real memory of data by pointer
 @param[in]    type: type of vector data
 @param[in]    pkv: pointer of vector structure
 @param[in]    n: new size of real memory
*/
#define kv_presize(type, pkv, n) kv_resize(type, *(pkv), n)
#endif /* kv_presize */

/* kv_v */
#ifndef kv_v
/*!
 @brief        element whose index is i. static
 @param[in]    kv: vector structure
 @param[in]    i: index of element
 @return       (kv).v[(i)]
*/
#define kv_v(kv, i) (kv).v[(i)]
#endif /* kv_v */

/* kv_pv */
#ifndef kv_pv
/*!
 @brief        element whose index is i. static by pointer
 @param[in]    pkv: pointer of vector structure
 @param[in]    i: index of element
 @return       (pkv)->v[(i)]
*/
#define kv_pv(pkv, i) kv_v(*(pkv), i)
#endif /* kv_pv */

/* kv_size */
#ifndef kv_size
/*!
 @brief        number of elements
 @param[in]    kv: vector structure
 @return       (kv).n
*/
#define kv_size(kv) (kv).n
#endif /* kv_size */

/* kv_psize */
#ifndef kv_psize
/*!
 @brief        number of elements by pointer
 @param[in]    pkv: pointer of vector structure
 @return       (pkv)->n
*/
#define kv_psize(pkv) kv_size(*(pkv))
#endif /* kv_psize */

/* kv_max */
#ifndef kv_max
/*!
 @brief        size of real memory
 @param[in]    kv: vector structure
 @return       (kv).m
*/
#define kv_max(kv) (kv).m
#endif /* kv_max */

/* __KV_PMAX */
#ifndef kv_pmax
/*!
 @brief        size of real memory by pointer
 @param[in]    pkv: pointer of vector structure
 @return       (pkv)->m
*/
#define kv_pmax(pkv) kv_max(*(pkv))
#endif /* kv_pmax */

/* kv_copy */
#ifndef kv_copy
/*!
 @brief        Copy kv0 to kv1 by vector structure
 @param[in]    type: type of vector data
 @param[out]   kv1: vector structure, destination
 @param[in]    kv0: vector structure, source
*/
#define kv_copy(type, kv1, kv0)          \
    (/**/                                \
     (kv1).m < (kv0).n                   \
         ? kv_resize(type, kv1, (kv0).n) \
         : 0, /* (kv1).m >= (kv0).n */   \
     (kv1).n = (kv0).n,                  \
     (void)memcpy(                       \
         (kv1).v,                        \
         (kv0).v,                        \
         sizeof(*(kv0).v) * (kv0).n) /**/)
#endif /* kv_copy */

/* kv_pcopy */
#ifndef kv_pcopy
/*!
 @brief        Copy pkv0 to pkv1 by pointer of vector structure
 @param[in]    name: identity name of vector structure
 @param[in]    type: type of vector data
 @param[out]   pkv1: pointer of vector structure, destination
 @param[in]    pkv0: pointer of vector structure, source
*/
#define kv_pcopy(name, type, pkv1, pkv0) \
    (/**/                                \
     (pkv1)                              \
         ? 0 /* pkv1 != NULL */          \
         : kv_pinit(name, pkv1),         \
     kv_copy(type, *(pkv1), *(pkv0)) /**/)
#endif /* kv_pcopy */

/* kv_pop */
#ifndef kv_pop
/*!
 @brief        Pop a element by vector structure
 @param[in]    kv: vector structure
 @return       (kv).v[(kv).n ? --(kv).n : 0U]
*/
#define kv_pop(kv) (kv).v[(kv).n ? --(kv).n : 0U]
#endif /* kv_pop */

/* kv_ppop */
#ifndef kv_ppop
/*!
 @brief        Pop a element pointer of vector structure
 @param[in]    pkv: pointer of vector structure
 @return       (pkv)->v[(pkv)->n ? --(pkv)->n : 0U]
*/
#define kv_ppop(pkv) kv_pop(*(pkv))
#endif /* kv_ppop */

/* kv_push */
#ifndef kv_push
/*!
 @brief        Push a element by vector structure
 @param[in]    type: type of vector data
 @param[in]    kv: vector structure
 @param[in]    x: element whose pushed
*/
#define kv_push(type, kv, x)                               \
    (/**/                                                  \
     (kv).n == (kv).m                                      \
         ? ((kv).m = ((kv).m                               \
                          ? ((kv).m << 1U) /* m != 0 */    \
                          : 2U),           /* m == 0 */    \
            (kv).v = (type *)                              \
                realloc((kv).v, sizeof(*(kv).v) * (kv).m), \
            0)                                             \
         : (/* n != m */ 0),                               \
     (kv).v[(kv).n++] = (x) /**/)
#endif /* kv_push */

/* kv_ppush */
#ifndef kv_ppush
/*!
 @brief        Push a element by pointer of vector structure
 @param[in]    type: type of vector data
 @param[in]    pkv: pointer of vector structure
 @param[in]    x: element whose pushed
*/
#define kv_ppush(type, pkv, x) kv_push(type, *(pkv), x)
#endif /* kv_ppush */

/* kv_pushp */
#ifndef kv_pushp

/*!
 @brief        address of element to be pushed
 @param[in]    type: type of vector data
 @param[in]    kv: vector structure
 @return       ((kv).v + (kv).n++)
*/
#define kv_pushp(type, kv)                                  \
    ((/**/                                                  \
      (kv).n == (kv).m                                      \
          ? (/* n == m */                                   \
             (kv).m = ((kv).m                               \
                           ? ((kv).m << 1U)                 \
                           : 2U),                           \
             (kv).v = (type *)                              \
                 realloc((kv).v, sizeof(*(kv).v) * (kv).m), \
             0)                                             \
          : (/* n != m */ 0),                               \
      /**/ 0),                                              \
     (kv).v + (kv).n++)
#endif /* kv_pushp */

/* kv_ppushp */
#ifndef kv_ppushp
/*!
 @brief        address of element to be pushed
 @param[in]    type: type of vector data
 @param[in]    pkv: pointer of vector structure
 @return       ((kv)->v + (kv)->n++)
*/
#define kv_ppushp(type, pkv) kv_pushp(type, *(pkv))
#endif /* kv_ppushp */

/* kv_vi */
#ifndef kv_vi
/*!
 @brief        element whose index is i. dynamic
 @param[in]    type: type of vector data
 @param[in]    kv: vector structure
 @param[in]    i: index of element
 @return       (kv).v[(i)]
*/
#define kv_vi(type, kv, i)                                 \
                                                           \
    (/**/                                                  \
     (kv).m <= (i)                                         \
         ? (/*m <= i*/                                     \
            (kv).m = (kv).n = (i) + 1U,                    \
            kroundup32((kv).m), /* m = n = i + 1 */        \
            (kv).v = (type *)                              \
                realloc((kv).v, sizeof(*(kv).v) * (kv).m), \
            0)                                             \
         : (/*m > i*/                                      \
            (kv).n <= (i)                                  \
                ? (/* n <= i */ (kv).n = (i) + 1U)         \
                : (/* n > i */ 0),                         \
            0),                                            \
     /**/ 0),                                              \
        (kv).v[(i)]
#endif /* kv_vi */

/* kv_pvi */
#ifndef kv_pvi
/*!
 @brief        element whose index is i. dynamic by pointer
 @param[in]    type: type of vector data
 @param[in]    pkv: pointer of vector structure
 @param[in]    i: index of element
 @return       (kv)->v[(i)]
*/
#define kv_pvi(type, pkv, i) kv_vi(type, *(pkv), i)
#endif /* kv_pvi */

/* __KVEC_IMPL */
#undef __KVEC_IMPL
#define __KVEC_IMPL(SCOPE, NAME, TYPE)                          \
                                                                \
    __NONNULL_ALL                                               \
    SCOPE                                                       \
    void kv_##NAME##_init(kvec_##NAME##_t *kv)                  \
    {                                                           \
        kv->n = 0U;                                             \
        kv->m = 0U;                                             \
        kv->v = NULL;                                           \
    }                                                           \
                                                                \
    __NONNULL_ALL                                               \
    SCOPE                                                       \
    int kv_##NAME##_pinit(kvec_##NAME##_t **pkv)                \
    {                                                           \
        *pkv = (kvec_##NAME##_t *)malloc(sizeof(**pkv));        \
        if (!*pkv)                                              \
        {                                                       \
            return -1;                                          \
        }                                                       \
        (*pkv)->n = 0U;                                         \
        (*pkv)->m = 0U;                                         \
        (*pkv)->v = NULL;                                       \
        return 0;                                               \
    }                                                           \
                                                                \
    __NONNULL_ALL                                               \
    SCOPE                                                       \
    void kv_##NAME##_clear(kvec_##NAME##_t *kv)                 \
    {                                                           \
        kv->n = 0U;                                             \
        kv->m = 0U;                                             \
        free(kv->v);                                            \
        kv->v = NULL;                                           \
    }                                                           \
                                                                \
    __NONNULL_ALL                                               \
    SCOPE                                                       \
    void kv_##NAME##_pclear(kvec_##NAME##_t **pkv)              \
    {                                                           \
        (*pkv)->n = (*pkv)->m = 0U;                             \
        free((*pkv)->v);                                        \
        (*pkv)->v = NULL;                                       \
        free(*pkv);                                             \
        *pkv = NULL;                                            \
    }                                                           \
                                                                \
    __NONNULL((1))                                              \
    SCOPE                                                       \
    int kv_##NAME##_resize(kvec_##NAME##_t *kv,                 \
                           size_t n)                            \
    {                                                           \
        void *p = realloc(kv->v, sizeof(*kv->v) * n);           \
        if (p || !n)                                            \
        {                                                       \
            kv->v = (TYPE *)p;                                  \
            p = NULL;                                           \
            kv->m = n;                                          \
            return 0;                                           \
        }                                                       \
        return -1;                                              \
    }                                                           \
                                                                \
    __NONNULL((1, 2))                                           \
    SCOPE                                                       \
    int kv_##NAME##_v(TYPE *dst,                                \
                      const kvec_##NAME##_t *kv,                \
                      size_t i)                                 \
    {                                                           \
        if (i < kv->n)                                          \
        {                                                       \
            *dst = kv->v[i];                                    \
            return 0;                                           \
        }                                                       \
        return -1;                                              \
    }                                                           \
                                                                \
    __NONNULL_ALL                                               \
    SCOPE                                                       \
    size_t kv_##NAME##_size(const kvec_##NAME##_t *kv)          \
    {                                                           \
        return kv->n;                                           \
    }                                                           \
                                                                \
    __NONNULL_ALL                                               \
    SCOPE                                                       \
    size_t kv_##NAME##_max(const kvec_##NAME##_t *kv)           \
    {                                                           \
        return kv->m;                                           \
    }                                                           \
                                                                \
    __NONNULL_ALL                                               \
    SCOPE                                                       \
    int kv_##NAME##_copy(kvec_##NAME##_t *kv1,                  \
                         const kvec_##NAME##_t *kv0)            \
    {                                                           \
        if (kv1->m < kv0->n)                                    \
        {                                                       \
            if (kv_##NAME##_resize(kv1, kv0->n))                \
            {                                                   \
                return -1;                                      \
            }                                                   \
        }                                                       \
        kv1->n = kv0->n;                                        \
        (void)memcpy(kv1->v, kv0->v, sizeof(*kv0->v) * kv0->n); \
        return 0;                                               \
    }                                                           \
                                                                \
    __NONNULL_ALL                                               \
    SCOPE                                                       \
    int kv_##NAME##_pop(TYPE *dst,                              \
                        kvec_##NAME##_t *kv)                    \
    {                                                           \
        if (kv->n)                                              \
        {                                                       \
            *dst = kv->v[--kv->n];                              \
            return 0;                                           \
        }                                                       \
        return -1;                                              \
    }                                                           \
                                                                \
    __NONNULL((1))                                              \
    SCOPE                                                       \
    int kv_##NAME##_push(kvec_##NAME##_t *kv,                   \
                         TYPE v)                                \
    {                                                           \
        if (kv->n == kv->m)                                     \
        {                                                       \
            kv->m = (kv->m ? (kv->m << 1U) : 2U);               \
            void *p = realloc(kv->v, sizeof(*kv->v) * kv->m);   \
            if (p)                                              \
            {                                                   \
                kv->v = (TYPE *)p;                              \
                p = NULL;                                       \
            }                                                   \
            else                                                \
            {                                                   \
                kv->m = kv->n;                                  \
                return -1;                                      \
            }                                                   \
        }                                                       \
        kv->v[kv->n++] = v;                                     \
        return 0;                                               \
    }                                                           \
                                                                \
    __NONNULL((1))                                              \
    SCOPE                                                       \
    int kv_##NAME##_vi(kvec_##NAME##_t *kv,                     \
                       size_t i,                                \
                       TYPE v)                                  \
    {                                                           \
        if (kv->m <= i)                                         \
        {                                                       \
            size_t m = i + 1U;                                  \
            kroundup32(m);                                      \
            void *p = realloc(kv->v, sizeof(*kv->v) * m);       \
            if (p)                                              \
            {                                                   \
                kv->v = (TYPE *)p;                              \
                p = NULL;                                       \
                kv->m = m;                                      \
            }                                                   \
            else                                                \
            {                                                   \
                return -1;                                      \
            }                                                   \
            kv->n = i + 1U;                                     \
        }                                                       \
        else if (kv->n <= i)                                    \
        {                                                       \
            kv->n = i + 1U;                                     \
        }                                                       \
        kv->v[i] = v;                                           \
        return 0;                                               \
    }

#ifndef kvec_impl
/*!
 @brief        Vector function Initial Microprogram Loading
 @param[in]    scope: scope of function
 @param[in]    name: identity name of vector structure
 @param[in]    type: type of vector data
*/
#define kvec_impl(scope, name, type) __KVEC_IMPL(scope, name, type)
#endif /* kvec_impl */

/* __KVEC_INIT */
#undef __KVEC_INIT
#define __KVEC_INIT(NAME, TYPE) \
    kvec_type(NAME, TYPE);      \
    __KVEC_IMPL(__STATIC_INLINE __UNUSED, NAME, TYPE)

#ifndef kvec_init
/*!
 @brief        Vector function Initial Microprogram Loading
 @param[in]    name: identity name of vector structure
 @param[in]    type: type of vector data
*/
#define kvec_init(name, type) __KVEC_INIT(name, type)
#endif /* kvec_init */

/* Enddef to prevent recursive inclusion */
#endif /* __KVEC_H__ */

/* END OF FILE */
