/**
 * *****************************************************************************
 * @file         klist.h
 * @brief        list library
 * @details      Generic single-linked list and memory pool
 * @author       tqfx
 * @date         20210421
 * @version      1
 * @copyright    Copyright (C) 2021
 * @code         utf-8                                                  @endcode
 * *****************************************************************************
*/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __KLIST_H__
#define __KLIST_H__

/* Includes ------------------------------------------------------------------*/
#include "klib.h"

/* Private includes ----------------------------------------------------------*/
#include <stdlib.h>

/* Exported macro ------------------------------------------------------------*/

/* __KMEMPOOL_TYPE -----------------------------------------------------------*/
#undef __KMEMPOOL_TYPE

#define __KMEMPOOL_TYPE(_NAME_, _TYPE_)                   \
                                                          \
    typedef struct Kmp_##_NAME_ kmp_##_NAME_##_t;         \
                                                          \
    struct Kmp_##_NAME_                                   \
    {                                                     \
        size_t   cnt; /* count of alloc memory         */ \
        size_t   n;   /* number of unused memory       */ \
        size_t   m;   /* size of real memory           */ \
        _TYPE_ **p;   /* first address of pointer list */ \
    }

#ifndef kmempool_type

/**
 * @brief        Register type of memory pool structure
 * @param[in]    _name_: identity name of memory pool structure
 * @param[in]    _type_: type of memory pool data
*/
#define kmempool_type(_name_, _type_) __KMEMPOOL_TYPE(_name_, _type_)

#endif /* kmempool_type */

/* __KMEMPOOL_T --------------------------------------------------------------*/
#undef __KMEMPOOL_T

#define __KMEMPOOL_T(_NAME_) kmp_##_NAME_##_t

#ifndef kmempool_t

/**
 * @brief        typedef of memory pool registration
 * @param[in]    _name_: identity name of memory pool structure
*/
#define kmempool_t(_name_) __KMEMPOOL_T(_name_)

#endif /* kmempool_t */

/* __KMEMPOOL_S --------------------------------------------------------------*/
#undef __KMEMPOOL_S

#define __KMEMPOOL_S(_TYPE_)                              \
                                                          \
    struct                                                \
    {                                                     \
        size_t   cnt; /* count of alloc memory         */ \
        size_t   n;   /* number of unused memory       */ \
        size_t   m;   /* size of real memory           */ \
        _TYPE_ **p;   /* first address of pointer list */ \
    }

#ifndef kmempool_s

/**
 * @brief        Anonymous structure of memory pool
 * @param[in]    _type_: type of memory pool data
*/
#define kmempool_s(_type_) __KMEMPOOL_S(_type_)

#endif /* kmempool_s */

/* __KMP_INIT ----------------------------------------------------------------*/
#undef __KMP_INIT

#define __KMP_INIT(_KMP_) \
                          \
    (/**/                 \
     (_KMP_).cnt = 0U,    \
     (_KMP_).n   = 0U,    \
     (_KMP_).m   = 0U,    \
     (_KMP_).p   = NULL /**/)

#ifndef kmp_init

/**
 * @brief        Initialize memory pool structure
 * @param[in]    _kmp_: memory pool structure
*/
#define kmp_init(_kmp_) __KMP_INIT(_kmp_)

#endif /* kmp_init */

/* __KMP_PINIT ---------------------------------------------------------------*/
#undef __KMP_PINIT

#define __KMP_PINIT(_NAME_, _PKMP_)                            \
                                                               \
    (/**/                                                      \
     (_PKMP_) = (kmp_##_NAME_##_t *)malloc(sizeof(*(_PKMP_))), \
     __KMP_INIT(*(_PKMP_)) /**/)

#ifndef kmp_pinit

/**
 * @brief        Initialize pointer of memory pool structure
 * @param[in]    _name_: identity name of memory pool structure
 * @param[out]   _pkmp_: pointer of memory pool structure
*/
#define kmp_pinit(_name_, _pkmp_) __KMP_PINIT(_name_, _pkmp_)

#endif /* kmp_pinit */

/* __KMP_CLEAR ---------------------------------------------------------------*/
#undef __KMP_CLEAR

#define __KMP_CLEAR(_FUN_, _KMP_)        \
                                         \
    do                                   \
    {                                    \
        while ((_KMP_).n)                \
        {                                \
            --(_KMP_).n;                 \
            _FUN_((_KMP_).p[(_KMP_).n]); \
            free((_KMP_).p[(_KMP_).n]);  \
            (_KMP_).p[(_KMP_).n] = NULL; \
        }                                \
        if ((_KMP_).m)                   \
        {                                \
            free((_KMP_).p);             \
            (_KMP_).p = NULL;            \
            (_KMP_).m = 0U;              \
        }                                \
    } while (0)

#ifndef kmp_clear

/**
 * @brief        Clear memory pool struture
 * @param[in]    _fun_: function that free data
 * @param[in]    _kmp_: memory pool structure
*/
#define kmp_clear(_fun_, _kmp_) __KMP_CLEAR(_fun_, _kmp_)

#endif /* kmp_clear */

/* __KMP_PCLEAR --------------------------------------------------------------*/
#undef __KMP_PCLEAR

#define __KMP_PCLEAR(_FUN_, _PKMP_)    \
                                       \
    do                                 \
    {                                  \
        __KMP_CLEAR(_FUN_, *(_PKMP_)); \
        free(_PKMP_);                  \
        (_PKMP_) = NULL;               \
    } while (0)

#ifndef kmp_pclear

/**
 * @brief        Clear memory pool pointer
 * @param[in]    _fun_: function that free data
 * @param[in]    _pkmp_: pointer of memory pool structure
*/
#define kmp_pclear(_fun_, _pkmp_) __KMP_PCLEAR(_fun_, _pkmp_)

#endif /* kmp_pclear */

/* __KMP_ALLOC ---------------------------------------------------------------*/
#undef __KMP_ALLOC

#define __KMP_ALLOC(_TYPE_, _KMP_)            \
                                              \
    (/**/                                     \
     ++(_KMP_).cnt,                           \
     (_KMP_).n                                \
         ? /* n > 0 */ (_KMP_).p[--(_KMP_).n] \
         : /* n = 0 */ (_TYPE_ *)calloc(1U, sizeof(**(_KMP_).p)) /**/)

#ifndef kmp_alloc

/**
 * @brief        Memory pool structure allocate
 * @param[in]    _type_: type of memory pool data
 * @param[in]    _kmp_: memory pool structure
 * @return       _type_ *
*/
#define kmp_alloc(_type_, _kmp_) __KMP_ALLOC(_type_, _kmp_)

#endif /* kmp_alloc */

/* __KMP_PALLOC --------------------------------------------------------------*/
#undef __KMP_PALLOC

#define __KMP_PALLOC(_TYPE_, _PKMP_) __KMP_ALLOC(_TYPE_, *(_PKMP_))

#ifndef kmp_palloc

/**
 * @brief        Memory pool pointer allocate
 * @param[in]    _type_: type of memory pool data
 * @param[in]    _pkmp_: pointer of memory pool structure
 * @return       _type_ *
*/
#define kmp_palloc(_type_, _pkmp_) __KMP_ALLOC(_type_, _pkmp_)

#endif /* kmp_palloc */

/* __KMP_FREE ----------------------------------------------------------------*/
#undef __KMP_FREE

#define __KMP_FREE(_TYPE_, _KMP_, _PDAT_)                           \
                                                                    \
    (/**/                                                           \
     --(_KMP_).cnt,                                                 \
     (_KMP_).n == (_KMP_).m                                         \
         ? (/* n == m */                                            \
            (_KMP_).m =                                             \
                ((_KMP_).m                                          \
                     ? /* m > 0 */ (_KMP_).m << 1U                  \
                     : /* m == 0 */ 16U),                           \
            (_KMP_).p = (_TYPE_ **)                                 \
                realloc((_KMP_).p, sizeof(*(_KMP_).p) * (_KMP_).m), \
            0)                                                      \
         : (/* n != m */ 0),                                        \
     (_KMP_).p[(_KMP_).n++] = (_PDAT_) /**/)

#ifndef kmp_free

/**
 * @brief        Memory pool structure free
 * @param[in]    _type_: type of memory pool data
 * @param[in]    _kmp_: memory pool structure
 * @param[in]    _pdat_: pointer that free data
*/
#define kmp_free(_type_, _kmp_, _pdat_) __KMP_FREE(_type_, _kmp_, _pdat_)

#endif /* kmp_free */

/* __KMP_PFREE ---------------------------------------------------------------*/
#undef __KMP_PFREE

#define __KMP_PFREE(_TYPE_, _PKMP_, _PDAT_) \
                                            \
    __KMP_FREE(_TYPE_, *(_PKMP_), _PDAT_)

#ifndef kmp_pfree

/**
 * @brief        Memory pool pointer free
 * @param[in]    _type_: type of memory pool data
 * @param[in]    _pkmp_: pointer of memory pool structure
 * @param[in]    _pdat_: pointer that free data
*/
#define kmp_pfree(_type_, _pkmp_, _pdat_) __KMP_PFREE(_type_, _pkmp_, _pdat_)

#endif /* kmp_pfree */

/* __KLIST1_TYPE -------------------------------------------------------------*/
#undef __KLIST1_TYPE

#define __KLIST1_TYPE(_NAME_, _TYPE_)                              \
                                                                   \
    typedef struct Kl1_##_NAME_ kl1_##_NAME_##_t;                  \
                                                                   \
    struct Kl1_##_NAME_                                            \
    {                                                              \
        struct Kl1_##_NAME_ *next; /* address of next node      */ \
        _TYPE_               data; /* variable that stores data */ \
    }

#ifndef klist1_type

/**
 * @brief        Register type of singly list structure
 * @param[in]    _name_: identity name of singly list structure
 * @param[in]    _type_: type of Singly list data
*/
#define klist1_type(_name_, _type_) __KLIST1_TYPE(_name_, _type_)

#endif /* klist1_type */

/* __KLIST1_T ----------------------------------------------------------------*/
#undef __KLIST1_T

#define __KLIST1_T(_NAME_) kl1_##_NAME_##_t

#ifndef klist1_t

/**
 * @brief        typedef of singly list registration
 * @param[in]    _name_: identity name of singly list structure
*/
#define klist1_t(_name_) __KLIST1_T(_name_)

#endif /* klist1_t */

/* __KL1_V -------------------------------------------------------------------*/
#undef __KL1_V

#define __KL1_V(_KL1_) (_KL1_).data

#ifndef kl1_v

/**
 * @brief        data of singly list structure
 * @param[in]    _kl1_: singly list structure
*/
#define kl1_v(_kl1_) __KL1_V(_kl1_)

#endif /* kl1_v */

/* __KL1_PV ------------------------------------------------------------------*/
#undef __KL1_PV

#define __KL1_PV(_PKL1_) __KL1_V(*(_PKL1_))

#ifndef kl1_pv

/**
 * @brief        data of singly list pointer
 * @param[in]    _pkl1_: pointer of singly list structure
*/
#define kl1_pv(_pkl1_) __KL1_PV(_pkl1_)

#endif /* kl1_v */

/* __KL1_NEXT ----------------------------------------------------------------*/
#undef __KL1_NEXT

#define __KL1_NEXT(_KL1_) (_KL1_).next

#ifndef kl1_next

/**
 * @brief        next node of singly list structure
 * @param[in]    _kl1_: singly list structure
*/
#define kl1_next(_kl1_) __KL1_NEXT(_kl1_)

#endif /* kl1_next */

/* __KL1_PNEXT ---------------------------------------------------------------*/
#undef __KL1_PNEXT

#define __KL1_PNEXT(_PKL1_) __KL1_NEXT(*(_PKL1_))

#ifndef kl1_pnext

/**
 * @brief        next node of singly list pointer
 * @param[in]    _pkl1_: pointer of singly list structure
*/
#define kl1_pnext(_pkl1_) __KL1_PNEXT(_pkl1_)

#endif /* kl1_pnext */

/* __KLIST_TYPE --------------------------------------------------------------*/
#undef __KLIST_TYPE

#define __KLIST_TYPE(_NAME_)                                 \
                                                             \
    typedef struct Kl_##_NAME_ kl_##_NAME_##_t;              \
                                                             \
    struct Kl_##_NAME_                                       \
    {                                                        \
        size_t            size; /* count of node      */     \
        kl1_##_NAME_##_t *head; /* head address of list   */ \
        kl1_##_NAME_##_t *tail; /* tail address of list   */ \
        kmp_##_NAME_##_t *kmp;  /* address of memory pool */ \
    }

#ifndef klist_type

/**
 * @brief        Register type of link list structure
 * @param[in]    _name_: identity name of link list structure
*/
#define klist_type(_name_) __KLIST_TYPE(_name_)

#endif /* klist_type */

/* __KLIST_T -----------------------------------------------------------------*/
#undef __KLIST_T

#define __KLIST_T(_NAME_) kl_##_NAME_##_t

#ifndef klist_t

/**
 * @brief        typedef of link list registration
 * @param[in]    _name_: identity name of link list structure
*/
#define klist_t(_name_) __KLIST_T(_name_)

#endif /* klist_t */

/* __KLIST_S -----------------------------------------------------------------*/
#undef __KLIST_S

#define __KLIST_S(_NAME_)                                    \
                                                             \
    struct                                                   \
    {                                                        \
        size_t            size; /* count of node          */ \
        kl1_##_NAME_##_t *head; /* head address of list   */ \
        kl1_##_NAME_##_t *tail; /* tail address of list   */ \
        kmp_##_NAME_##_t *kmp;  /* address of memory pool */ \
    }

#ifndef klist_s

/**
 * @brief        Anonymous structure of link list
 * @param[in]    _name_: identity name of link list structure
*/
#define klist_s(_name_) __KLIST_S(_name_)

#endif /* klist_s */

/* __KL_BEGIN ----------------------------------------------------------------*/
#undef __KL_BEGIN

#define __KL_BEGIN(_KL_) (_KL_).head

#ifndef kl_begin

/**
 * @brief        begin node of link list structure
 * @param[in]    _kl_: link list structure
*/
#define kl_begin(_kl_) __KL_BEGIN(_kl_)

#endif /* kl_begin */

/* __KL_PBEGIN ---------------------------------------------------------------*/
#undef __KL_PBEGIN

#define __KL_PBEGIN(_PKL_) __KL_BEGIN(*(_PKL_))

#ifndef kl_pbegin

/**
 * @brief        begin node of link list pointer
 * @param[in]    _pkl_: pointer of link list structure
*/
#define kl_pbegin(_pkl_) __KL_PBEGIN(_pkl_)

#endif /* kl_pbegin */

/* __KL_END ------------------------------------------------------------------*/
#undef __KL_END

#define __KL_END(_KL_) (_KL_).tail

#ifndef kl_end

/**
 * @brief        end node of link list structure
 * @param[in]    _kl_: link list structure
*/
#define kl_end(_kl_) __KL_END(_kl_)

#endif /* kl_end */

/* __KL_PEND -----------------------------------------------------------------*/
#undef __KL_PEND

#define __KL_PEND(_PKL_) __KL_END(*(_PKL_))

#ifndef kl_pend

/**
 * @brief        end node of link list pointer
 * @param[in]    _pkl_: pointer of link list structure
*/
#define kl_pend(_pkl_) __KL_PEND(_pkl_)

#endif /* kl_pend */

/* __KL_INIT -----------------------------------------------------------------*/
#undef __KL_INIT

#define __KL_INIT(_NAME_, _KL_)                                      \
                                                                     \
    (/**/                                                            \
     (_KL_).size = 0U,                                               \
     __KMP_PINIT(_NAME_, (_KL_).kmp),                                \
     (_KL_).tail       = __KMP_PALLOC(kl1_##_NAME_##_t, (_KL_).kmp), \
     (_KL_).head       = (_KL_).tail,                                \
     (_KL_).head->next = NULL /**/)

#ifndef kl_init

/**
 * @brief        Initialize link list structure
 * @param[in]    _name_: identity name of link list structure
 * @param[in]    _kl_: link list structure
*/
#define kl_init(_name_, _kl_) __KL_INIT(_name_, _kl_)

#endif /* kl_init */

/* __KL_PINIT ----------------------------------------------------------------*/
#undef __KL_PINIT

#define __KL_PINIT(_NAME_, _PKL_)                           \
                                                            \
    (/**/                                                   \
     (_PKL_) = (kl_##_NAME_##_t *)malloc(sizeof(*(_PKL_))), \
     __KL_INIT(_NAME_, *(_PKL_)) /**/)

#ifndef kl_pinit

/**
 * @brief        Initialize link list pointer
 * @param[in]    _name_: identity name of link list structure
 * @param[out]   _pkl_: pointer of link list structure
*/
#define kl_pinit(_name_, _pkl_) __KL_PINIT(_name_, _pkl_)

#endif /* kl_pinit */

/* __KL_CLEAR ----------------------------------------------------------------*/
#undef __KL_CLEAR

#define __KL_CLEAR(_NAME_, _FUN_, _KL_)                             \
                                                                    \
    do                                                              \
    {                                                               \
        while ((_KL_).head != (_KL_).tail)                          \
        {                                                           \
            __KMP_PFREE(kl1_##_NAME_##_t, (_KL_).kmp, (_KL_).head); \
            (_KL_).head = (_KL_).head->next;                        \
        }                                                           \
        __KMP_PFREE(kl1_##_NAME_##_t, (_KL_).kmp, (_KL_).tail);     \
        __KMP_PCLEAR(_FUN_, (_KL_).kmp);                            \
        (_KL_).size = 0U;                                           \
    } while (0)

#ifndef kl_clear

/**
 * @brief        Clear link list structure
 * @param[in]    _name_: identity name of link list structure
 * @param[in]    _fun_: function that free data
 * @param[in]    _kl_: link list structure
*/
#define kl_clear(_name_, _fun_, _kl_) __KL_CLEAR(_name_, _fun_, _kl_)

#endif /* kl_clear */

/* __KL_PCLEAR ---------------------------------------------------------------*/
#undef __KL_PCLEAR

#define __KL_PCLEAR(_NAME_, _FUN_, _PKL_)    \
                                             \
    do                                       \
    {                                        \
        __KL_CLEAR(_NAME_, _FUN_, *(_PKL_)); \
        free(_PKL_);                         \
        (_PKL_) = NULL;                      \
    } while (0)

#ifndef kl_pclear

/**
 * @brief        Clear link list pointer
 * @param[in]    _name_: identity name of link list structure
 * @param[in]    _fun_: function that free data
 * @param[in]    _pkl_: pointer of link list structure
*/
#define kl_pclear(_name_, _fun_, _pkl_) __KL_PCLEAR(_name_, _fun_, _pkl_)

#endif /* kl_pclear */

/* __KL_PUSH -----------------------------------------------------------------*/
#undef __KL_PUSH

#define __KL_PUSH(_NAME_, _KL_, _X_)                                       \
                                                                           \
    (/**/ ++(_KL_).size,                                                   \
     (_KL_).tail->next       = __KMP_PALLOC(kl1_##_NAME_##_t, (_KL_).kmp), \
     (_KL_).tail->next->next = NULL,                                       \
     (_KL_).tail->data       = (_X_),                                      \
     (_KL_).tail             = (_KL_).tail->next /**/)

#ifndef kl_push

/**
 * @brief        Push data to link list structure
 * @param[in]    _name_: identity name of link list structure
 * @param[in]    _kl_: link list structure
 * @param[in]    _x_: data whose pushed
*/
#define kl_push(_name_, _kl_, _x_) __KL_PUSH(_name_, _kl_, _x_)

#endif /* kl_push */

/* __KL_PPUSH ----------------------------------------------------------------*/
#undef __KL_PPUSH

#define __KL_PPUSH(_NAME_, _PKL_, _X_) __KL_PUSH(_NAME_, *(_PKL_), _X_)

#ifndef kl_ppush

/**
 * @brief        Push data to link list pointer
 * @param[in]    _name_: identity name of link list structure
 * @param[in]    _pkl_: pointer of link list structure
 * @param[in]    _x_: data whose pushed
*/
#define kl_ppush(_name_, _pkl_, _x_) __KL_PPUSH(_name_, _pkl_, _x_)

#endif /* kl_ppush */

/* __KL_PUSHP ----------------------------------------------------------------*/
#undef __KL_PUSHP

#define __KL_PUSHP(_NAME_, _KL_, _PX_)                                     \
                                                                           \
    (/**/ ++(_KL_).size,                                                   \
     (_KL_).tail->next       = __KMP_PALLOC(kl1_##_NAME_##_t, (_KL_).kmp), \
     (_KL_).tail->next->next = NULL,                                       \
     (_PX_)                  = &(_KL_).tail->data,                         \
     (_KL_).tail             = (_KL_).tail->next /**/)

#ifndef kl_pushp

/**
 * @brief        Get address of stored data variable
 * @param[in]    _name_: identity name of link list structure
 * @param[in]    _kl_: link list structure
 * @param[out]   _px_: pointer that stores data address
*/
#define kl_pushp(_name_, _kl_, _px_) __KL_PUSHP(_name_, _kl_, _px_)

#endif /* kl_pushp */

/* __KL_PPUSHP ----------------------------------------------------------------*/
#undef __KL_PPUSHP

#define __KL_PPUSHP(_NAME_, _PKL_, _PX_) __KL_PUSHP(_NAME_, *(_PKL_), _PX_)

#ifndef kl_ppushp

/**
 * @brief        Get address of stored data variable
 * @param[in]    _name_: identity name of link list structure
 * @param[in]    _pkl_: pointer of link list structure
 * @param[out]   _px_: pointer that stores data address
*/
#define kl_ppushp(_name_, _pkl_, _px_) __KL_PPUSHP(_name_, _pkl_, _px_)

#endif /* kl_ppushp */

/* __KL_SHIFT ----------------------------------------------------------------*/
#undef __KL_SHIFT

#define __KL_SHIFT(_NAME_, _KL_, _X_)                               \
                                                                    \
    (/**/ (_KL_).head->next                                         \
         ? (/* head->next != NULL */                                \
            --(_KL_).size,                                          \
            (_X_) = (_KL_).head->data,                              \
            __KMP_PFREE(kl1_##_NAME_##_t, (_KL_).kmp, (_KL_).head), \
            (_KL_).head = (_KL_).head->next,                        \
            0)                                                      \
         : (/* head->next == NULL */ -1) /**/)

#ifndef kl_shift

/**
 * @brief        Shift data to variable from link list structure
 * @param[in]    _name_: identity name of link list structure
 * @param[in]    _kl_: link list structure
 * @param[out]   _x_: variable that stores data
 * @return       int 0(success) -1(failure)
*/
#define kl_shift(_name_, _kl_, _x_) __KL_SHIFT(_name_, _kl_, _x_)

#endif /* kl_shift */

/* __KL_PSHIFT ---------------------------------------------------------------*/
#undef __KL_PSHIFT

#define __KL_PSHIFT(_NAME_, _PKL_, _X_) __KL_SHIFT(_NAME_, *(_PKL_), _X_)

#ifndef kl_pshift

/**
 * @brief        Shift data to variable from link list pointer
 * @param[in]    _name_: identity name of link list structure
 * @param[in]    _pkl_: pointer of link list structure
 * @param[out]   _x_: variable that stores data
 * @return       int 0(success) -1(failure)
*/
#define kl_pshift(_name_, _pkl_, _x_) __KL_PSHIFT(_name_, _pkl_, _x_)

#endif /* kl_pshift */

/* __KL_SHIFTP ---------------------------------------------------------------*/
#undef __KL_SHIFTP

#define __KL_SHIFTP(_NAME_, _KL_, _PX_)                             \
                                                                    \
    (/**/ (_KL_).head->next                                         \
         ? (/* head->next != NULL */                                \
            --(_KL_).size,                                          \
            (_PX_) = &(_KL_).head->data,                            \
            __KMP_PFREE(kl1_##_NAME_##_t, (_KL_).kmp, (_KL_).head), \
            (_KL_).head = (_KL_).head->next,                        \
            0)                                                      \
         : (/* head->next == NULL */ -1) /**/)

#ifndef kl_shiftp

/**
 * @brief        Get shift data address to variable from link list structure
 * @param[in]    _name_: identity name of link list structure
 * @param[in]    _kl_: link list structure
 * @param[out]   _px_: pointer that stores data variable
 * @return       int 0(success) -1(failure)
*/
#define kl_shiftp(_name_, _kl_, _px_) __KL_SHIFTP(_name_, _kl_, _px_)

#endif /* kl_shiftp */

/* __KL_PSHIFTP ---------------------------------------------------------------*/
#undef __KL_PSHIFTP

#define __KL_PSHIFTP(_NAME_, _PKL_, _PX_) __KL_SHIFTP(_NAME_, *(_PKL_), _PX_)

#ifndef kl_pshiftp

/**
 * @brief        Get shift data address to variable from link list pointer
 * @param[in]    _name_: identity name of link list structure
 * @param[in]    _pkl_: pointer of link list structure
 * @param[out]   _px_: pointer that stores data variable
 * @return       int 0(success) -1(failure)
*/
#define kl_pshiftp(_name_, _pkl_, _px_) __KL_PSHIFTP(_name_, _pkl_, _px_)

#endif /* kl_pshift */

/* __KMEMPOOL_IMPL -----------------------------------------------------------*/
#undef __KMEMPOOL_IMPL

#define __KMEMPOOL_IMPL(_SCOPE_, _NAME_, _TYPE_, _FUN_)      \
                                                             \
    __NONNULL_ALL                                            \
    _SCOPE_                                                  \
    void kmp_##_NAME_##_init(kmp_##_NAME_##_t *kmp)          \
    {                                                        \
        kmp->cnt = 0U;                                       \
        kmp->n   = 0U;                                       \
        kmp->m   = 0U;                                       \
        kmp->p   = NULL;                                     \
    }                                                        \
                                                             \
    __NONNULL_ALL                                            \
    _SCOPE_                                                  \
    int kmp_##_NAME_##_pinit(kmp_##_NAME_##_t **pkmp)        \
    {                                                        \
        *pkmp = (kmp_##_NAME_##_t *)malloc(sizeof(**pkmp));  \
        if (!*pkmp)                                          \
        {                                                    \
            return -1;                                       \
        }                                                    \
        (*pkmp)->cnt = 0U;                                   \
        (*pkmp)->n   = 0U;                                   \
        (*pkmp)->m   = 0U;                                   \
        (*pkmp)->p   = NULL;                                 \
        return 0;                                            \
    }                                                        \
                                                             \
    __RESULT_USE_CHECK                                       \
    _SCOPE_                                                  \
    kmp_##_NAME_##_t *kmp_##_NAME_##_initp(void)             \
    {                                                        \
        return (kmp_##_NAME_##_t *)                          \
            calloc(1U, sizeof(kmp_##_NAME_##_t));            \
    }                                                        \
                                                             \
    __NONNULL_ALL                                            \
    _SCOPE_                                                  \
    void kmp_##_NAME_##_clear(kmp_##_NAME_##_t *kmp)         \
    {                                                        \
        while (kmp->n)                                       \
        {                                                    \
            --kmp->n;                                        \
            _FUN_(kmp->p[kmp->n]);                           \
            free(kmp->p[kmp->n]);                            \
            kmp->p[kmp->n] = NULL;                           \
        }                                                    \
        if (kmp->m)                                          \
        {                                                    \
            free(kmp->p);                                    \
            kmp->p = NULL;                                   \
            kmp->m = 0U;                                     \
        }                                                    \
    }                                                        \
                                                             \
    __NONNULL_ALL                                            \
    _SCOPE_                                                  \
    void kmp_##_NAME_##_pclear(kmp_##_NAME_##_t **pkmp)      \
    {                                                        \
        while ((*pkmp)->n)                                   \
        {                                                    \
            --(*pkmp)->n;                                    \
            _FUN_((*pkmp)->p[(*pkmp)->n]);                   \
            free((*pkmp)->p[(*pkmp)->n]);                    \
            (*pkmp)->p[(*pkmp)->n] = NULL;                   \
        }                                                    \
        if ((*pkmp)->m)                                      \
        {                                                    \
            free((*pkmp)->p);                                \
            (*pkmp)->p = NULL;                               \
            (*pkmp)->m = 0U;                                 \
        }                                                    \
        free(*pkmp);                                         \
        *pkmp = NULL;                                        \
    }                                                        \
                                                             \
    __NONNULL_ALL                                            \
    _SCOPE_                                                  \
    _TYPE_ *kmp_##_NAME_##_alloc(kmp_##_NAME_##_t *kmp)      \
    {                                                        \
        ++kmp->cnt;                                          \
        if (kmp->n)                                          \
        {                                                    \
            return kmp->p[--kmp->n];                         \
        }                                                    \
        else                                                 \
        {                                                    \
            return (_TYPE_ *)calloc(1U, sizeof(**kmp->p));   \
        }                                                    \
    }                                                        \
                                                             \
    __NONNULL_ALL                                            \
    _SCOPE_                                                  \
    int kmp_##_NAME_##_free(kmp_##_NAME_##_t *kmp,           \
                            _TYPE_ *          pdat)          \
    {                                                        \
        --kmp->cnt;                                          \
        if (kmp->n == kmp->m)                                \
        {                                                    \
            size_t m = kmp->m ? kmp->m << 1U : 16U;          \
            void * p = realloc(kmp->p, sizeof(*kmp->p) * m); \
            if (p)                                           \
            {                                                \
                kmp->p = (_TYPE_ **)p;                       \
                kmp->m = m;                                  \
            }                                                \
            else                                             \
            {                                                \
                return -1;                                   \
            }                                                \
        }                                                    \
        kmp->p[kmp->n++] = pdat;                             \
        return 0;                                            \
    }

#ifndef kmempool_impl

/**
 * @brief        Memory pool function Initial Microprogram Loading
 * @param[in]    _scope_: scope of function
 * @param[in]    _name_: identity name of memory pool structure
 * @param[in]    _type_: type of memory pool data
 * @param[in]    _fun_: function of free data
*/
#define kmempool_impl(_scope_, _name_, _type_, _fun_) \
                                                      \
    __KMEMPOOL_IMPL(_scope_, _name_, _type_, _fun_)

#endif /* kmempool_impl */

/* __KMEMPOOL_INIT -----------------------------------------------------------*/
#undef __KMEMPOOL_INIT

#define __KMEMPOOL_INIT(_NAME_, _TYPE_, _FUN_) \
                                               \
    __KMEMPOOL_TYPE(_NAME_, _TYPE_);           \
    __KMEMPOOL_IMPL(static inline __UNUSED, _NAME_, _TYPE_, _FUN_)

#ifndef kmempool_init

/**
 * @brief        Memory pool function Initial Microprogram Loading
 * @param[in]    _name_: identity name of memory pool structure
 * @param[in]    _type_: type of memory pool data
 * @param[in]    _fun_: function of free data
*/
#define kmempool_init(_name_, _type_, _fun_) \
                                             \
    __KMEMPOOL_INIT(_name_, _type_, _fun_)

#endif /* kmempool_init */

/* __KLIST_IMPL --------------------------------------------------------------*/
#undef __KLIST_IMPL

#define __KLIST_IMPL(_SCOPE_, _NAME_, _TYPE_)                \
                                                             \
    __NONNULL_ALL                                            \
    _SCOPE_                                                  \
    int kl_##_NAME_##_init(kl_##_NAME_##_t *kl)              \
    {                                                        \
        kl->size = 0U;                                       \
        kl->kmp  = kmp_##_NAME_##_initp();                   \
        if (!kl->kmp)                                        \
        {                                                    \
            return -1;                                       \
        }                                                    \
        kl->tail = kmp_##_NAME_##_alloc(kl->kmp);            \
        kl->head = kl->tail;                                 \
        if (!kl->head)                                       \
        {                                                    \
            return -1;                                       \
        }                                                    \
        kl->head->next = NULL;                               \
        return 0;                                            \
    }                                                        \
                                                             \
    __NONNULL_ALL                                            \
    _SCOPE_                                                  \
    int kl_##_NAME_##_pinit(kl_##_NAME_##_t **pkl)           \
    {                                                        \
        *pkl = (kl_##_NAME_##_t *)malloc(sizeof(**pkl));     \
        if (!*pkl)                                           \
        {                                                    \
            return -1;                                       \
        }                                                    \
        (*pkl)->size = 0U;                                   \
        (*pkl)->kmp  = kmp_##_NAME_##_initp();               \
        if (!(*pkl)->kmp)                                    \
        {                                                    \
            return -1;                                       \
        }                                                    \
        (*pkl)->tail = kmp_##_NAME_##_alloc((*pkl)->kmp);    \
        (*pkl)->head = (*pkl)->tail;                         \
        if (!(*pkl)->tail)                                   \
        {                                                    \
            return -1;                                       \
        }                                                    \
        (*pkl)->head->next = NULL;                           \
        return 0;                                            \
    }                                                        \
                                                             \
    __RESULT_USE_CHECK                                       \
    _SCOPE_                                                  \
    kl_##_NAME_##_t *kl_##_NAME_##_initp(void)               \
    {                                                        \
        kl_##_NAME_##_t *pkl = (kl_##_NAME_##_t *)           \
            malloc(sizeof(kl_##_NAME_##_t));                 \
        if (!pkl)                                            \
        {                                                    \
            return NULL;                                     \
        }                                                    \
        pkl->size       = 0U;                                \
        pkl->kmp        = kmp_##_NAME_##_initp();            \
        pkl->tail       = kmp_##_NAME_##_alloc(pkl->kmp);    \
        pkl->head       = pkl->tail;                         \
        pkl->head->next = NULL;                              \
        return pkl;                                          \
    }                                                        \
                                                             \
    __NONNULL_ALL                                            \
    _SCOPE_                                                  \
    void kl_##_NAME_##_clear(kl_##_NAME_##_t *kl)            \
    {                                                        \
        while (kl->head != kl->tail)                         \
        {                                                    \
            kmp_##_NAME_##_free(kl->kmp, kl->head);          \
            kl->head = kl->head->next;                       \
        }                                                    \
        kmp_##_NAME_##_free(kl->kmp, kl->tail);              \
        kmp_##_NAME_##_clear(kl->kmp);                       \
        free(kl->kmp);                                       \
        kl->kmp  = NULL;                                     \
        kl->size = 0U;                                       \
    }                                                        \
                                                             \
    __NONNULL_ALL                                            \
    _SCOPE_                                                  \
    void kl_##_NAME_##_pclear(kl_##_NAME_##_t **pkl)         \
    {                                                        \
        while ((*pkl)->head != (*pkl)->tail)                 \
        {                                                    \
            kmp_##_NAME_##_free((*pkl)->kmp, (*pkl)->head);  \
            (*pkl)->head = (*pkl)->head->next;               \
        }                                                    \
        kmp_##_NAME_##_free((*pkl)->kmp, (*pkl)->tail);      \
        kmp_##_NAME_##_clear((*pkl)->kmp);                   \
        free((*pkl)->kmp);                                   \
        (*pkl)->kmp  = NULL;                                 \
        (*pkl)->size = 0U;                                   \
        free(*pkl);                                          \
        *pkl = NULL;                                         \
    }                                                        \
                                                             \
    __NONNULL((1))                                           \
    _SCOPE_                                                  \
    int kl_##_NAME_##_push(kl_##_NAME_##_t *kl,              \
                           _TYPE_           x)               \
    {                                                        \
        kl->tail->next = kmp_##_NAME_##_alloc(kl->kmp);      \
        if (!kl->tail->next)                                 \
        {                                                    \
            return -1;                                       \
        }                                                    \
        kl->tail->next->next = NULL;                         \
        kl->tail->data       = x;                            \
        kl->tail             = kl->tail->next;               \
        kl->size++;                                          \
        return 0;                                            \
    }                                                        \
                                                             \
    __NONNULL_ALL                                            \
    __RESULT_USE_CHECK                                       \
    _SCOPE_                                                  \
    _TYPE_ *kl_##_NAME_##_pushp(kl_##_NAME_##_t *kl)         \
    {                                                        \
        kl1_##_NAME_##_t *p = kl->tail;                      \
        kl->tail->next      = kmp_##_NAME_##_alloc(kl->kmp); \
        if (!kl->tail->next)                                 \
        {                                                    \
            return NULL;                                     \
        }                                                    \
        kl->tail->next->next = NULL;                         \
        kl->tail             = kl->tail->next;               \
        kl->size++;                                          \
        return &p->data;                                     \
    }                                                        \
                                                             \
    __NONNULL_ALL                                            \
    _SCOPE_                                                  \
    int kl_##_NAME_##_shift(kl_##_NAME_##_t *kl,             \
                            _TYPE_ *         px)             \
    {                                                        \
        if (!kl->head->next)                                 \
        {                                                    \
            return -1;                                       \
        }                                                    \
        *px = kl->head->data;                                \
        kmp_##_NAME_##_free(kl->kmp, kl->head);              \
        kl->head = kl->head->next;                           \
        kl->size--;                                          \
        return 0;                                            \
    }

#ifndef klist_impl

/**
 * @brief        List function Initial Microprogram Loading
 * @param[in]    _scope_: scope of function
 * @param[in]    _name_: identity name of link list structure
 * @param[in]    _type_: type of link list data
*/
#define klist_impl(_scope_, _name_, _type_) \
                                            \
    __KLIST_IMPL(_scope_, _name_, _type_)

#endif /* klist_impl */

/* __KLIST_INIT --------------------------------------------------------------*/
#undef __KLIST_INIT

#define __KLIST_INIT(_NAME_, _TYPE_, _FUN_)                                    \
                                                                               \
    __KLIST1_TYPE(_NAME_, _TYPE_);                                             \
    __KMEMPOOL_TYPE(_NAME_, __KLIST1_T(_NAME_));                               \
    __KLIST_TYPE(_NAME_);                                                      \
    __KMEMPOOL_IMPL(static inline __UNUSED, _NAME_, __KLIST1_T(_NAME_), _FUN_) \
    __KLIST_IMPL(static inline __UNUSED, _NAME_, _TYPE_)

#ifndef klist_init

/**
 * @brief        List function Initial Microprogram Loading
 * @param[in]    _name_: identity name of link list structure
 * @param[in]    _type_: type of link list data
 * @param[in]    _fun_: function of free data
*/
#define klist_init(_name_, _type_, _fun_) __KLIST_INIT(_name_, _type_, _fun_)

#endif /* klist_init */

/* __KLIST_H__ ---------------------------------------------------------------*/
#endif /* __KLIST_H__ */

/************************ (C) COPYRIGHT tqfx *******************END OF FILE****/
