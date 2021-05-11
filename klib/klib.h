/**
 * *****************************************************************************
 * @file         klib.h
 * @brief        Some macros of klib
 * @details      
 * @author       tqfx
 * @date         20210212
 * @version      1
 * @copyright    Copyright (C) 2021
 * @code         utf-8                                                  @endcode
 * *****************************************************************************
*/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __KLIB_H__
#define __KLIB_H__

/* C --> C++ -----------------------------------------------------------------*/
#undef __BEGIN_DECLS
#undef __END_DECLS

#ifdef __cplusplus
#define __BEGIN_DECLS \
    extern "C"        \
    {
#define __END_DECLS }
#else
#define __BEGIN_DECLS
#define __END_DECLS
#endif /* __cplusplus */

/* GCC version check ---------------------------------------------------------*/
#if defined __GNUC__ && defined __GNUC_MINOR__
#define __GNUC_PREREQ(maj, min) \
    ((__GNUC__ << 16) + __GNUC_MINOR__ >= ((maj) << 16) + (min))
#else
#define __GNUC_PREREQ(maj, min) 0
#endif /* defined __GNUC__ && defined __GNUC_MINOR__ */

/* clang version check -------------------------------------------------------*/
#if defined __clang_major__ && defined __clang_minor__
#define __glibc_clang_prereq(maj, min) \
    ((__clang_major__ << 16) + __clang_minor__ >= ((maj) << 16) + (min))
#else
#define __glibc_clang_prereq(maj, min) 0
#endif /* defined __clang_major__ && defined __clang_minor__ */

/* attribute nonnull ---------------------------------------------------------*/
#undef __NONNULL
#undef __NONNULL_ALL

#if __GNUC_PREREQ(3, 3)
#define __NONNULL(_X_) __attribute__((__nonnull__ _X_))
#define __NONNULL_ALL  __attribute__((__nonnull__))
#else
#define __NONNULL(_X_)
#define __NONNULL_ALL
#endif /* __GNUC_PREREQ(3, 3) */

#ifndef __nonnull
#define __nonnull(_x_) __NONNULL(_x_)
#endif /* __nonnull */
#ifndef __nonnull_all
#define __nonnull_all __NONNULL_ALL
#endif /* __nonnull_all */

/* attribute warn unused result ----------------------------------------------*/
#undef __RESULT_USE_CHECK

#if __GNUC_PREREQ(3, 4)
#define __RESULT_USE_CHECK __attribute__((__warn_unused_result__))
#else
#define __RESULT_USE_CHECK
#endif /* __GNUC_PREREQ(3, 4) */

#ifndef __result_use_check
#define __result_use_check __RESULT_USE_CHECK
#endif /* __result_use_check */

/* attribute always inline ---------------------------------------------------*/
#undef __ALWAYS_INLINE

#if __GNUC_PREREQ(3, 2)
#define __ALWAYS_INLINE __inline __attribute__((__always_inline__))
#else
#define __ALWAYS_INLINE
#endif /* __GNUC_PREREQ (3,2) */

#ifndef __always_inline
#define __always_inline __ALWAYS_INLINE
#endif /* __always_inline */

/* builtin expect ------------------------------------------------------------*/
#undef __PREDICT_TRUE
#undef __PREDICT_FALSE

#if defined __GNUC__
#if __GNUC__ >= 3
#define __PREDICT_TRUE(_EXP_)  __builtin_expect((_EXP_), 1)
#define __PREDICT_FALSE(_EXP_) __builtin_expect((_EXP_), 0)
#else /* __GNUC__ < 3 */
#define __PREDICT_TRUE(_EXP_)  (_EXP_)
#define __PREDICT_FALSE(_EXP_) (_EXP_)
#endif /* __GNUC__ >= 3 */
#else  /* Not GCC */
#define __PREDICT_TRUE(_EXP_)  (_EXP_)
#define __PREDICT_FALSE(_EXP_) (_EXP_)
#endif /* __GNUC__ */

#ifndef __predict_true
#define __predict_true(_exp_) __PREDICT_TRUE(_exp_)
#endif /* __predict_true */
#ifndef __predict_false
#define __predict_false(_exp_) __PREDICT_FALSE(_exp_)
#endif /* __predict_false */

/* attribute weak ------------------------------------------------------------*/
#undef __WEAK

#if defined __GNUC__
#if __GNUC__ >= 3
#define __WEAK __attribute__((__weak__))
#else /* __GNUC__ < 3 */
#define __WEAK
#endif /* __GNUC__ >= 3 */
#else  /* Not GCC */
#define __WEAK
#endif /* __GNUC__ */

#ifndef __weak
#define __weak __WEAK
#endif /* __weak */

/* attribute unused ----------------------------------------------------------*/
#undef __UNUSED

#if __glibc_clang_prereq(3, 3)
#define __UNUSED __attribute__((__unused__))
#else
#define __UNUSED
#endif /* __glibc_clang_prereq(3, 3) */

#ifndef __unused
#define __unused __UNUSED
#endif /* __unused */

/* klib roundup x -> 2^* -----------------------------------------------------*/
#undef __KROUNDUP32

#define __KROUNDUP32(_X_)   \
                            \
    (/**/ --(_X_),          \
     (_X_) |= (_X_) >> 1U,  \
     (_X_) |= (_X_) >> 2U,  \
     (_X_) |= (_X_) >> 4U,  \
     (_X_) |= (_X_) >> 8U,  \
     (_X_) |= (_X_) >> 16U, \
     ++(_X_) /**/)

#ifndef kroundup32
#define kroundup32(_x_) __KROUNDUP32(_x_)
#endif /* kroundup32 */

/* pointer free --------------------------------------------------------------*/
#undef __PFREE

#define __PFREE(_FUN_, _P_) \
                            \
    (/**/                   \
     (void)_FUN_(_P_),      \
     _P_ = NULL /**/)

#ifndef pfree
#define pfree(_fun_, _p_) __PFREE(_fun_, _p_)
#endif /* pfree */

/* __KLIB_H__ ----------------------------------------------------------------*/
#endif /* __KLIB_H__ */

/************************ (C) COPYRIGHT tqfx *******************END OF FILE****/
