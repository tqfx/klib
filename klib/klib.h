/*!
 @file           klib.h
 @brief          Some macros of klib
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
#ifndef __KLIB_H__
#define __KLIB_H__

/* C --> C++ */
#undef __BEGIN_DECLS
#undef __END_DECLS

#ifdef __cplusplus
#define __BEGIN_DECLS \
    extern "C"        \
    {
#define __END_DECLS \
    }
#else
#define __BEGIN_DECLS
#define __END_DECLS
#endif /* __cplusplus */

/* GCC version check */
#if defined __GNUC__ && defined __GNUC_MINOR__

#ifndef __GNUC_PREREQ
#define __GNUC_PREREQ(maj, min) \
    ((__GNUC__ << 16) + __GNUC_MINOR__ >= ((maj) << 16) + (min))
#endif /* __GNUC_PREREQ */

#else

#ifndef __GNUC_PREREQ
#define __GNUC_PREREQ(maj, min) 0
#endif /* __GNUC_PREREQ */

#endif /* defined __GNUC__ && defined __GNUC_MINOR__ */

/* clang version check */
#if defined __clang_major__ && defined __clang_minor__

#ifndef __glibc_clang_prereq
#define __glibc_clang_prereq(maj, min) \
    ((__clang_major__ << 16) + __clang_minor__ >= ((maj) << 16) + (min))
#endif /* __glibc_clang_prereq */

#else

#ifndef __glibc_clang_prereq
#define __glibc_clang_prereq(maj, min) 0
#endif /* __glibc_clang_prereq */

#endif /* defined __clang_major__ && defined __clang_minor__ */

/* attribute nonnull */
#if __GNUC_PREREQ(3, 3)

#ifndef __NONNULL
#define __NONNULL(x) __attribute__((__nonnull__ x))
#endif /* __NONNULL */
#ifndef __NONNULL_ALL
#define __NONNULL_ALL __attribute__((__nonnull__))
#endif /* __NONNULL_ALL */

#else

#ifndef __NONNULL
#define __NONNULL(x)
#endif /* __NONNULL */
#ifndef __NONNULL_ALL
#define __NONNULL_ALL
#endif /* __NONNULL_ALL */

#endif /* __GNUC_PREREQ(3, 3) */

/* attribute warn unused result */
#if __GNUC_PREREQ(3, 4)

#ifndef __RESULT_USE_CHECK
#define __RESULT_USE_CHECK __attribute__((__warn_unused_result__))
#endif /* __RESULT_USE_CHECK */

#else

#ifndef __RESULT_USE_CHECK
#define __RESULT_USE_CHECK
#endif /* __RESULT_USE_CHECK */

#endif /* __GNUC_PREREQ(3, 4) */

/* attribute always inline */
#if __GNUC_PREREQ(3, 2)

#ifndef __ALEAYS_INLINE
#define __ALEAYS_INLINE __inline __attribute__((__always_inline__))
#endif /* __ALEAYS_INLINE */

#else

#ifndef __ALEAYS_INLINE
#define __ALEAYS_INLINE
#endif /* __ALEAYS_INLINE */

#endif /* __GNUC_PREREQ (3,2) */

/* builtin expect */
#if defined __GNUC__ && __GNUC__ >= 3

#ifndef __PREDICT_TRUE
#define __PREDICT_TRUE(exp) __builtin_expect((exp), 1)
#endif /* __PREDICT_TRUE */
#ifndef __PREDICT_FALSE
#define __PREDICT_FALSE(exp) __builtin_expect((exp), 0)
#endif /* __PREDICT_FALSE */

#else /* Not GCC || __GNUC__ < 3 */

#ifndef __PREDICT_TRUE
#define __PREDICT_TRUE(exp) (exp)
#endif /* __PREDICT_TRUE */
#ifndef __PREDICT_FALSE
#define __PREDICT_FALSE(exp) (exp)
#endif /* __PREDICT_FALSE */

#endif /* defined __GNUC__ && __GNUC__ >= 3 */

/* attribute weak */
#if defined __GNUC__ && __GNUC__ >= 3

#ifndef __WEAK
#define __WEAK __attribute__((__weak__))
#endif /* __WEAK */

#else /* Not gcc || __GNUC__ < 3 */

#ifndef __WEAK
#define __WEAK
#endif /* __WEAK */

#endif /* defined __GNUC__ && __GNUC__ >= 3 */

/* attribute unused */
#if __glibc_clang_prereq(3, 3)

#ifndef __UNUSED
#define __UNUSED __attribute__((__unused__))
#endif /* __UNUSED */

#else

#ifndef __UNUSED
#define __UNUSED
#endif /* __UNUSED */

#endif /* __glibc_clang_prereq(3, 3) */

/* static inline */
#ifndef __STATIC_INLINE
#define __STATIC_INLINE static inline
#endif /* __STATIC_INLINE */

/* klib roundup x -> 2^* */
#ifndef kroundup32
#define kroundup32(x)  \
    (/**/ --(x),       \
     (x) |= (x) >> 1,  \
     (x) |= (x) >> 2,  \
     (x) |= (x) >> 4,  \
     (x) |= (x) >> 8,  \
     (x) |= (x) >> 16, \
     ++(x) /**/)
#endif /* kroundup32 */

/* pointer free */
#ifndef pfree
#define pfree(func, p) (/**/ (void)func(p), p = ((void *)0) /**/)
#endif /* pfree */

/* Enddef to prevent recursive inclusion */
#endif /* __KLIB_H__ */

/* END OF FILE */
