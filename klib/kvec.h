/**
 * *****************************************************************************
 * @file         kvec.h
 * @brief        vector library
 * @details      generic dynamic array
 * @author       tqfx
 * @date         20210421
 * @version      1
 * @copyright    Copyright (C) 2021
 * @code         utf-8                                                  @endcode
 * *****************************************************************************
*/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __KVEC_H__
#define __KVEC_H__

/* Includes ------------------------------------------------------------------*/
#include "klib.h"

/* Private includes ----------------------------------------------------------*/
#include <stdlib.h>
#include <string.h>

/* Exported macro ------------------------------------------------------------*/

/* __KVEC_TYPE ---------------------------------------------------------------*/
#undef __KVEC_TYPE

#define __KVEC_TYPE(_NAME_, _TYPE_)                 \
                                                    \
    typedef struct Kvec_##_NAME_ kvec_##_NAME_##_t; \
                                                    \
    struct Kvec_##_NAME_                            \
    {                                               \
        size_t  n; /* number of elements      */    \
        size_t  m; /* size of real memory     */    \
        _TYPE_ *v; /* first address of vector */    \
    }

#ifndef kvec_type

/**
 * @brief        Register type of vector structure
 * @param[in]    _name_: identity name of vector structure
 * @param[in]    _type_: type of vector data
*/
#define kvec_type(_name_, _type_) __KVEC_TYPE(_name_, _type_)

#endif /* kvec_type */

/* __KVEC_T ------------------------------------------------------------------*/
#undef __KVEC_T

#define __KVEC_T(_NAME_) kvec_##_NAME_##_t

#ifndef kvec_t

/**
 * @brief        typedef of vector registration
 * @param[in]    _name_: identity name of vector structure
*/
#define kvec_t(_name_) __KVEC_T(_name_)

#endif /* kvec_t */

/* __KVEC_S ------------------------------------------------------------------*/
#undef __KVEC_S

#define __KVEC_S(_TYPE_)                         \
                                                 \
    struct                                       \
    {                                            \
        size_t  n; /* number of elements      */ \
        size_t  m; /* size of real memory     */ \
        _TYPE_ *v; /* first address of vector */ \
    }

#ifndef kvec_s

/**
 * @brief        Anonymous structure of vector
 * @param[in]    _type_: type of vector data
*/
#define kvec_s(_type_) __KVEC_S(_type_)

#endif /* kvec_s */

/* __KV_INIT -----------------------------------------------------------------*/
#undef __KV_INIT

#define __KV_INIT(_KV_) \
                        \
    (/**/               \
     (_KV_).n = 0U,     \
     (_KV_).m = 0U,     \
     (_KV_).v = NULL /**/)

#ifndef kv_init

/**
 * @brief        Initialize vector structure
 * @param[in]    _kv_: vector structure
*/
#define kv_init(_kv_) __KV_INIT(_kv_)

#endif /* kv_init */

/* __KV_PINIT ----------------------------------------------------------------*/
#undef __KV_PINIT

#define __KV_PINIT(_NAME_, _PKV_)                             \
                                                              \
    (/**/                                                     \
     (_PKV_) = (kvec_##_NAME_##_t *)malloc(sizeof(*(_PKV_))), \
     __KV_INIT(*(_PKV_)) /**/)

#ifndef kv_pinit

/**
 * @brief        Initialize pointer of vector structure
 * @param[in]    _name_: identity name of vector structure
 * @param[out]   _pkv_: pointer of vector structure
*/
#define kv_pinit(_name_, _pkv_) __KV_PINIT(_name_, _pkv_)

#endif /* kv_pinit */

/* __KV_CLEAR ----------------------------------------------------------------*/
#undef __KV_CLEAR

#define __KV_CLEAR(_KV_) \
                         \
    (/**/                \
     (_KV_).n = 0U,      \
     (_KV_).m = 0U,      \
     free((_KV_).v),     \
     (_KV_).v = NULL /**/)

#ifndef kv_clear

/**
 * @brief        Free memory of data and clear vector structure
 * @param[in]    _kv_: vector structure
*/
#define kv_clear(_kv_) __KV_CLEAR(_kv_)

#endif /* kv_clear */

/* __KV_PCLEAR ---------------------------------------------------------------*/
#undef __KV_PCLEAR

#define __KV_PCLEAR(_PKV_) \
                           \
    (/**/                  \
     __KV_CLEAR(*(_PKV_)), \
     free(_PKV_),          \
     (_PKV_) = NULL /**/)

#ifndef kv_pclear

/**
 * @brief        Free memory and clear pointer of vector structure
 * @param[in]    _pkv_: pointer of vector structure
*/
#define kv_pclear(_pkv_) __KV_PCLEAR(_pkv_)

#endif /* kv_pclear */

/* __KV_RESIZE ---------------------------------------------------------------*/
#undef __KV_RESIZE

#define __KV_RESIZE(_TYPE_, _KV_, _N_) \
                                       \
    (/**/                              \
     (_KV_).m = (_N_),                 \
     (_KV_).v = (_TYPE_ *)realloc((_KV_).v, sizeof(*(_KV_).v) * (_N_)) /**/)

#ifndef kv_resize

/**
 * @brief        Resize real memory of data
 * @param[in]    _type_: type of vector data
 * @param[in]    _kv_: vector structure
 * @param[in]    _n_: new size of real memory
*/
#define kv_resize(_type_, _kv_, _n_) __KV_RESIZE(_type_, _kv_, _n_)

#endif /* kv_resize */

/* __KV_PRESIZE --------------------------------------------------------------*/
#undef __KV_PRESIZE

#define __KV_PRESIZE(_TYPE_, _PKV_, _N_) __KV_RESIZE(_TYPE_, *(_PKV_), _N_)

#ifndef kv_presize

/**
 * @brief        Resize real memory of data by pointer
 * @param[in]    _type_: type of vector data
 * @param[in]    _pkv_: pointer of vector structure
 * @param[in]    _n_: new size of real memory
*/
#define kv_presize(_type_, _pkv_, _n_) __KV_PRESIZE(_type_, _pkv_, _n_)

#endif /* kv_presize */

/* __KV_V --------------------------------------------------------------------*/
#undef __KV_V

#define __KV_V(_KV_, _I_) (_KV_).v[(_I_)]

#ifndef kv_v

/**
 * @brief        element whose index is i. static
 * @param[in]    _kv_: vector structure
 * @param[in]    _i_: index of element
 * @return       (_kv_).v[(_i_)]
*/
#define kv_v(_kv_, _i_) __KV_V(_kv_, _i_)

#endif /* kv_v */

/* __KV_PV -------------------------------------------------------------------*/
#undef __KV_PV

#define __KV_PV(_PKV_, _I_) __KV_V(*(_PKV_), _I_)

#ifndef kv_pv

/**
 * @brief        element whose index is i. static by pointer
 * @param[in]    _pkv_: pointer of vector structure
 * @param[in]    _i_: index of element
 * @return       (_pkv_)->v[(_i_)]
*/
#define kv_pv(_pkv_, _i_) __KV_PV(_pkv_, _i_)

#endif /* kv_pv */

/* __KV_SIZE -----------------------------------------------------------------*/
#undef __KV_SIZE

#define __KV_SIZE(_KV_) (_KV_).n

#ifndef kv_size

/**
 * @brief        number of elements
 * @param[in]    _kv_: vector structure
 * @return       (_kv_).n
*/
#define kv_size(_kv_) __KV_SIZE(_kv_)

#endif /* kv_size */

/* __KV_PSIZE ----------------------------------------------------------------*/
#undef __KV_PSIZE

#define __KV_PSIZE(_PKV_) __KV_SIZE(*(_PKV_))

#ifndef kv_psize

/**
 * @brief        number of elements by pointer
 * @param[in]    _pkv_: pointer of vector structure
 * @return       (_pkv_)->n
*/
#define kv_psize(_pkv_) __KV_PSIZE(_pkv_)

#endif /* kv_psize */

/* __KV_MAX ------------------------------------------------------------------*/
#undef __KV_MAX

#define __KV_MAX(_KV_) (_KV_).m

#ifndef kv_max

/**
 * @brief        size of real memory
 * @param[in]    _kv_: vector structure
 * @return       (_kv_).m
*/
#define kv_max(_kv_) __KV_MAX(_kv_)

#endif /* kv_max */

/* __KV_PMAX -----------------------------------------------------------------*/
#undef __KV_PMAX

#define __KV_PMAX(_PKV_) __KV_MAX(*(_PKV_))

#ifndef kv_pmax

/**
 * @brief        size of real memory by pointer
 * @param[in]    _pkv_: pointer of vector structure
 * @return       (_pkv_)->m
*/
#define kv_pmax(_pkv_) __KV_PMAX(_pkv_)

#endif /* kv_pmax */

/* __KV_COPY -----------------------------------------------------------------*/
#undef __KV_COPY

#define __KV_COPY(_TYPE_, _KV1_, _KV0_)          \
                                                 \
    (/**/                                        \
     (_KV1_).m < (_KV0_).n                       \
         ? __KV_RESIZE(_TYPE_, _KV1_, (_KV0_).n) \
         : 0, /* (_KV1_).m >= (_KV0_).n */       \
     (_KV1_).n = (_KV0_).n,                      \
     (void)memcpy(                               \
         (_KV1_).v,                              \
         (_KV0_).v,                              \
         sizeof(*(_KV0_).v) * (_KV0_).n) /**/)

#ifndef kv_copy

/**
 * @brief        Copy kv0 to kv1 by vector structure
 * @param[in]    _type_: type of vector data
 * @param[out]   _kv1_: vector structure, destination
 * @param[in]    _kv0_: vector structure, source
*/
#define kv_copy(_type_, _kv1_, _kv0_) __KV_COPY(_type_, _kv1_, _kv0_)

#endif /* kv_copy */

/* __KV_PCOPY ----------------------------------------------------------------*/
#undef __KV_PCOPY

#define __KV_PCOPY(_NAME_, _TYPE_, _PKV1_, _PKV0_) \
                                                   \
    (/**/                                          \
     (_PKV1_)                                      \
         ? 0 /* _PKV1_ != NULL */                  \
         : __KV_PINIT(_NAME_, _PKV1_),             \
     __KV_COPY(_TYPE_, *(_PKV1_), *(_PKV0_)) /**/)

#ifndef kv_pcopy

/**
 * @brief        Copy pkv0 to pkv1 by pointer of vector structure
 * @param[in]    _name_: identity name of vector structure
 * @param[in]    _type_: type of vector data
 * @param[out]   _pkv1_: pointer of vector structure, destination
 * @param[in]    _pkv0_: pointer of vector structure, source
*/
#define kv_pcopy(_name_, _type_, _pkv1_, _pkv0_) \
                                                 \
    __KV_PCOPY(_name_, _type_, _pkv1_, _pkv0_)

#endif /* kv_pcopy */

/* __KV_POP ------------------------------------------------------------------*/
#undef __KV_POP

#define __KV_POP(_KV_) (_KV_).v[(/**/ (_KV_).n ? --(_KV_).n : 0U /**/)]

#ifndef kv_pop

/**
 * @brief        Pop a element by vector structure
 * @param[in]    _kv_: vector structure
 * @return       (_kv_).v[((_kv_).n ? --(_kv_).n : 0U)]
*/
#define kv_pop(_kv_) __KV_POP(_kv_)

#endif /* kv_pop */

/* __KV_PPOP -----------------------------------------------------------------*/
#undef __KV_PPOP

#define __KV_PPOP(_PKV_) __KV_POP(*(_PKV_))

#ifndef kv_ppop

/**
 * @brief        Pop a element pointer of vector structure
 * @param[in]    _pkv_: pointer of vector structure
 * @return       (_pkv_)->v[((_pkv_)->n ? --(_pkv_)->n : 0U)]
*/
#define kv_ppop(_pkv_) __KV_PPOP(_pkv_)

#endif /* kv_ppop */

/* __KV_PUSH -----------------------------------------------------------------*/
#undef __KV_PUSH

#define __KV_PUSH(_TYPE_, _KV_, _X_)                             \
    (/**/                                                        \
     (_KV_).n == (_KV_).m                                        \
         ? ((_KV_).m = ((_KV_).m                                 \
                            ? ((_KV_).m << 1U) /* m != 0 */      \
                            : 2U),             /* m == 0 */      \
            (_KV_).v = (_TYPE_ *)                                \
                realloc((_KV_).v, sizeof(*(_KV_).v) * (_KV_).m), \
            0)                                                   \
         : (/* n != m */ 0),                                     \
     (_KV_).v[(_KV_).n++] = (_X_) /**/)

#ifndef kv_push

/**
 * @brief        Push a element by vector structure
 * @param[in]    _type_: type of vector data
 * @param[in]    _kv_: vector structure
 * @param[in]    _x_: element whose pushed
*/
#define kv_push(_type_, _kv_, _x_) __KV_PUSH(_type_, _kv_, _x_)

#endif /* kv_push */

/* __KV_PPUSH ----------------------------------------------------------------*/
#undef __KV_PPUSH

#define __KV_PPUSH(_TYPE_, _PKV_, _X_) __KV_PUSH(_TYPE_, *(_PKV_), _X_)

#ifndef kv_ppush

/**
 * @brief        Push a element by pointer of vector structure
 * @param[in]    _type_: type of vector data
 * @param[in]    _pkv_: pointer of vector structure
 * @param[in]    _x_: element whose pushed
*/
#define kv_ppush(_type_, _pkv_, _x_) __KV_PPUSH(_type_, _pkv_, _x_)

#endif /* kv_ppush */

/* __KV_PUSHP ----------------------------------------------------------------*/
#undef __KV_PUSHP

#define __KV_PUSHP(_TYPE_, _KV_)                                  \
                                                                  \
    ((/**/                                                        \
      (_KV_).n == (_KV_).m                                        \
          ? (/* n == m */                                         \
             (_KV_).m = ((_KV_).m                                 \
                             ? ((_KV_).m << 1U)                   \
                             : 2U),                               \
             (_KV_).v = (_TYPE_ *)                                \
                 realloc((_KV_).v, sizeof(*(_KV_).v) * (_KV_).m), \
             0)                                                   \
          : (/* n != m */ 0),                                     \
      /**/ 0),                                                    \
     (_KV_).v + (_KV_).n++)

#ifndef kv_pushp

/**
 * @brief        address of element to be pushed
 * @param[in]    _type_: type of vector data
 * @param[in]    _kv_: vector structure
 * @return       ((_kv_).v + (_kv_).n++)
*/
#define kv_pushp(_type_, _kv_) __KV_PUSHP(_type_, _kv_)

#endif /* kv_pushp */

/* __KV_PPUSHP ---------------------------------------------------------------*/
#undef __KV_PPUSHP

#define __KV_PPUSHP(_TYPE_, _PKV_) __KV_PUSHP(_TYPE_, *(_PKV_))

#ifndef kv_ppushp

/**
 * @brief        address of element to be pushed
 * @param[in]    _type_: type of vector data
 * @param[in]    _pkv_: pointer of vector structure
 * @return       ((_kv_)->v + (_kv_)->n++)
*/
#define kv_ppushp(_type_, _pkv_) __KV_PPUSHP(_type_, _pkv_)

#endif /* kv_ppushp */

/* __KV_VI -------------------------------------------------------------------*/
#undef __KV_VI

#define __KV_VI(_TYPE_, _KV_, _I_)                               \
                                                                 \
    (/**/                                                        \
     (_KV_).m <= (_I_)                                           \
         ? (/*m <= i*/                                           \
            (_KV_).m = (_KV_).n = (_I_) + 1U,                    \
            __KROUNDUP32((_KV_).m), /* m = n = i + 1 */          \
            (_KV_).v = (_TYPE_ *)                                \
                realloc((_KV_).v, sizeof(*(_KV_).v) * (_KV_).m), \
            0)                                                   \
         : (/*m > i*/                                            \
            (_KV_).n <= (_I_)                                    \
                ? (/* n <= i */ (_KV_).n = (_I_) + 1U)           \
                : (/* n > i */ 0),                               \
            0),                                                  \
     /**/ 0),                                                    \
        (_KV_).v[(_I_)]

#ifndef kv_vi

/**
 * @brief        element whose index is i. dynamic
 * @param[in]    _type_: type of vector data
 * @param[in]    _kv_: vector structure
 * @param[in]    _i_: index of element
 * @return       (_kv_).v[(_i_)]
*/
#define kv_vi(_type_, _kv_, _i_) __KV_VI(_type_, _kv_, _i_)

#endif /* kv_vi */

/* __KV_PVI ------------------------------------------------------------------*/
#undef __KV_PVI

#define __KV_PVI(_TYPE_, _PKV_, _I_) __KV_VI(_TYPE_, *(_PKV_), _I_)

#ifndef kv_pvi

/**
 * @brief        element whose index is i. dynamic by pointer
 * @param[in]    _type_: type of vector data
 * @param[in]    _pkv_: pointer of vector structure
 * @param[in]    _i_: index of element
 * @return       (_kv_)->v[(_i_)]
*/
#define kv_pvi(_type_, _pkv_, _i_) __KV_PVI(_type_, _pkv_, _i_)

#endif /* kv_pvi */

/* __KVEC_IMPL ---------------------------------------------------------------*/
#undef __KVEC_IMPL

#define __KVEC_IMPL(_SCOPE_, _NAME_, _TYPE_)                    \
                                                                \
    __NONNULL_ALL                                               \
    _SCOPE_                                                     \
    void kv_##_NAME_##_init(kvec_##_NAME_##_t *kv)              \
    {                                                           \
        kv->n = 0U;                                             \
        kv->m = 0U;                                             \
        kv->v = NULL;                                           \
    }                                                           \
                                                                \
    __NONNULL_ALL                                               \
    _SCOPE_                                                     \
    int kv_##_NAME_##_pinit(kvec_##_NAME_##_t **pkv)            \
    {                                                           \
        *pkv = (kvec_##_NAME_##_t *)malloc(sizeof(**pkv));      \
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
    _SCOPE_                                                     \
    void kv_##_NAME_##_clear(kvec_##_NAME_##_t *kv)             \
    {                                                           \
        kv->n = 0U;                                             \
        kv->m = 0U;                                             \
        free(kv->v);                                            \
        kv->v = NULL;                                           \
    }                                                           \
                                                                \
    __NONNULL_ALL                                               \
    _SCOPE_                                                     \
    void kv_##_NAME_##_pclear(kvec_##_NAME_##_t **pkv)          \
    {                                                           \
        (*pkv)->n = (*pkv)->m = 0U;                             \
        free((*pkv)->v);                                        \
        (*pkv)->v = NULL;                                       \
        free(*pkv);                                             \
        *pkv = NULL;                                            \
    }                                                           \
                                                                \
    __NONNULL((1))                                              \
    _SCOPE_                                                     \
    int kv_##_NAME_##_resize(kvec_##_NAME_##_t *kv,             \
                             size_t             n)              \
    {                                                           \
        void *p = realloc(kv->v, sizeof(*kv->v) * n);           \
        if (p || !n)                                            \
        {                                                       \
            kv->v = (_TYPE_ *)p;                                \
            p     = NULL;                                       \
            kv->m = n;                                          \
            return 0;                                           \
        }                                                       \
        return -1;                                              \
    }                                                           \
                                                                \
    __NONNULL((1, 2))                                           \
    _SCOPE_                                                     \
    int kv_##_NAME_##_v(_TYPE_ *                 dst,           \
                        const kvec_##_NAME_##_t *kv,            \
                        size_t                   i)             \
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
    _SCOPE_                                                     \
    size_t kv_##_NAME_##_size(const kvec_##_NAME_##_t *kv)      \
    {                                                           \
        return kv->n;                                           \
    }                                                           \
                                                                \
    __NONNULL_ALL                                               \
    _SCOPE_                                                     \
    size_t kv_##_NAME_##_max(const kvec_##_NAME_##_t *kv)       \
    {                                                           \
        return kv->m;                                           \
    }                                                           \
                                                                \
    __NONNULL_ALL                                               \
    _SCOPE_                                                     \
    int kv_##_NAME_##_copy(kvec_##_NAME_##_t *      kv1,        \
                           const kvec_##_NAME_##_t *kv0)        \
    {                                                           \
        if (kv1->m < kv0->n)                                    \
        {                                                       \
            if (kv_##_NAME_##_resize(kv1, kv0->n))              \
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
    _SCOPE_                                                     \
    int kv_##_NAME_##_pop(_TYPE_ *           dst,               \
                          kvec_##_NAME_##_t *kv)                \
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
    _SCOPE_                                                     \
    int kv_##_NAME_##_push(kvec_##_NAME_##_t *kv,               \
                           _TYPE_             v)                \
    {                                                           \
        if (kv->n == kv->m)                                     \
        {                                                       \
            kv->m   = (kv->m ? (kv->m << 1U) : 2U);             \
            void *p = realloc(kv->v, sizeof(*kv->v) * kv->m);   \
            if (p)                                              \
            {                                                   \
                kv->v = (_TYPE_ *)p;                            \
                p     = NULL;                                   \
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
    _SCOPE_                                                     \
    int kv_##_NAME_##_vi(kvec_##_NAME_##_t *kv,                 \
                         size_t             i,                  \
                         _TYPE_             v)                  \
    {                                                           \
        if (kv->m <= i)                                         \
        {                                                       \
            size_t m = i + 1U;                                  \
            __KROUNDUP32(m);                                    \
            void *p = realloc(kv->v, sizeof(*kv->v) * m);       \
            if (p)                                              \
            {                                                   \
                kv->v = (_TYPE_ *)p;                            \
                p     = NULL;                                   \
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

/**
 * @brief        Vector function Initial Microprogram Loading
 * @param[in]    _scope_: scope of function
 * @param[in]    _name_: identity name of vector structure
 * @param[in]    _type_: type of vector data
*/
#define kvec_impl(_scope_, _name_, _type_) __KVEC_IMPL(_scope_, _name_, _type_)

#endif /* kvec_impl */

/* __KVEC_INIT ---------------------------------------------------------------*/
#undef __KVEC_INIT

#define __KVEC_INIT(_NAME_, _TYPE_) \
                                    \
    __KVEC_TYPE(_NAME_, _TYPE_);    \
    __KVEC_IMPL(static inline __UNUSED, _NAME_, _TYPE_)

#ifndef kvec_init

/**
 * @brief        Vector function Initial Microprogram Loading
 * @param[in]    _name_ identity name of vector structure
 * @param[in]    _type_ type of vector data
*/
#define kvec_init(_name_, _type_) __KVEC_INIT(_name_, _type_)

#endif /* kvec_init */

/* __KVEC_H__ ----------------------------------------------------------------*/
#endif /* __KVEC_H__ */

/************************ (C) COPYRIGHT tqfx *******************END OF FILE****/
