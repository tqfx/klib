/*!
 @file           ksort.h
 @brief          sort library
 @details        generic sort, including introsort, merge sort, heap sort,
                 comb sort, Knuth shuffle and  k-small algorithm.
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
#ifndef __KSORT_H__
#define __KSORT_H__

#include "klib.h"

#include <stdlib.h>
#include <string.h>

/* swap */
#ifndef ksort_swap
/*!
 @brief          swap a and b
 @param[in]      t: type of swep
 @param[in]      a: variable that need to swap
 @param[in]      b: variable that need to swap
*/
#define ksort_swap(t, a, b) \
    do                      \
    {                       \
        t _swap = (a);      \
        (a) = (b);          \
        (b) = _swap;        \
    } while (0)
#endif /* ksort_swap */

/* merge sort */
#ifndef ksort_merge
/*!
 @brief          Merge sort
 @param[in]      t: type of data array
 @param[in]      p: pointer of data array
 @param[in]      n: length of data array
 @param[in]      func: function of compare
 @param[in]      a: pointer of buffer, length >= n
*/
#define ksort_merge(t, p, n, func, a)                          \
    do                                                         \
    {                                                          \
        t *_merge_p[2U] = {                                    \
            (p),                                               \
            (a)                                                \
                ? (a)                                          \
                : (t *)malloc(sizeof(*(p)) * (n)),             \
        };                                                     \
        unsigned int _merge_site = 0U;                         \
        for (size_t _merge_step = 1U;                          \
             _merge_step < (n);                                \
             _merge_step <<= 1U)                               \
        {                                                      \
            t *_merge_a = _merge_p[_merge_site];               \
            t *_merge_b = _merge_p[!_merge_site];              \
            while (_merge_b != (_merge_p[!_merge_site] + (n))) \
            {                                                  \
                t *_merge_a1 = _merge_a;                       \
                t *_merge_e1 =                                 \
                    (_merge_a + _merge_step) <                 \
                            (_merge_p[_merge_site] + (n))      \
                        ? (_merge_a + _merge_step)             \
                        : (_merge_p[_merge_site] + (n));       \
                t *_merge_a2 = _merge_e1;                      \
                t *_merge_e2 =                                 \
                    (_merge_a + (_merge_step << 1U)) <         \
                            (_merge_p[_merge_site] + (n))      \
                        ? (_merge_a + (_merge_step << 1U))     \
                        : (_merge_p[_merge_site] + (n));       \
                while (_merge_a1 != _merge_e1 &&               \
                       _merge_a2 != _merge_e2)                 \
                {                                              \
                    if (func(*_merge_a1, *_merge_a2))          \
                    {                                          \
                        *_merge_b++ = *_merge_a1++;            \
                    }                                          \
                    else                                       \
                    {                                          \
                        *_merge_b++ = *_merge_a2++;            \
                    }                                          \
                }                                              \
                while (_merge_a1 != _merge_e1)                 \
                {                                              \
                    *_merge_b++ = *_merge_a1++;                \
                }                                              \
                while (_merge_a2 != _merge_e2)                 \
                {                                              \
                    *_merge_b++ = *_merge_a2++;                \
                }                                              \
                _merge_a = _merge_e2;                          \
            }                                                  \
            _merge_site = !_merge_site;                        \
        }                                                      \
        if (_merge_site)                                       \
        {                                                      \
            t *_merge_a = _merge_p[0U];                        \
            t *_merge_b = _merge_p[1U];                        \
            while (_merge_a != (_merge_p[0U] + (n)))           \
            {                                                  \
                *_merge_a++ = *_merge_b++;                     \
            }                                                  \
        }                                                      \
        if (!(a))                                              \
        {                                                      \
            free(_merge_p[1U]);                                \
            _merge_p[1U] = NULL;                               \
        }                                                      \
    } while (0)
#endif /* ksort_merge */

/* heap adjust */
#ifndef ksort_heap_adjust
/*!
 @brief          Heap adjust
 @param[in]      t: type of data array
 @param[in]      p: pointer of data array
 @param[in]      i: index of data array
 @param[in]      n: length of data array
 @param[in]      func: function of compare
*/
#define ksort_heap_adjust(t, p, i, n, func)            \
    do                                                 \
    {                                                  \
        t _heap_p = (p)[(i)];                          \
        size_t _heap_i = (i);                          \
        size_t _heap_j = (i);                          \
        while ((_heap_i = (_heap_i << 1U) + 1U) < (n)) \
        {                                              \
            if (_heap_i != (n)-1U &&                   \
                func((p)[_heap_i], (p)[_heap_i + 1U])) \
            {                                          \
                ++_heap_i;                             \
            }                                          \
            if (func((p)[_heap_i], _heap_p))           \
            {                                          \
                break;                                 \
            }                                          \
            (p)[_heap_j] = (p)[_heap_i];               \
            _heap_j = _heap_i;                         \
        }                                              \
        (p)[_heap_j] = _heap_p;                        \
    } while (0)
#endif /* ksort_heap_adjust */

/* heap make */
#ifndef ksort_heap_make
/*!
 @brief          Heap make
 @param[in]      t: type of data array
 @param[in]      p: pointer of data array
 @param[in]      n: length of data array
 @param[in]      func: function of compare
*/
#define ksort_heap_make(t, p, n, func)                 \
    do                                                 \
    {                                                  \
        for (size_t _heap_k = ((n) >> 1U) - 1U;        \
             _heap_k != (size_t)(-1);                  \
             --_heap_k)                                \
        {                                              \
            ksort_heap_adjust(t, p, _heap_k, n, func); \
        }                                              \
    } while (0)
#endif /* ksort_heap_make */

/* heap sort */
#ifndef ksort_heap
/*!
 @brief          Heap sort
 @param[in]      t: type of data array
 @param[in]      p: pointer of data array
 @param[in]      n: length of data array
 @param[in]      func: function of compare
*/
#define ksort_heap(t, p, n, func)                         \
    do                                                    \
    {                                                     \
        for (size_t _heap_k = (n)-1U; _heap_k; --_heap_k) \
        {                                                 \
            ksort_swap(t, *(p), (p)[_heap_k]);            \
            ksort_heap_adjust(t, p, 0U, _heap_k, func);   \
        }                                                 \
    } while (0)
#endif /* ksort_heap */

/* insert sort */
#ifndef ksort_insert
/*!
 @brief          Insert sort
 @param[in]      t: type of data array
 @param[in]      p: pointer of data array
 @param[in]      n: length of data array
 @param[in]      func: function of compare
*/
#define ksort_insert(t, p, n, func)                           \
    do                                                        \
    {                                                         \
        for (t *_insert_i = (p) + 1U;                         \
             _insert_i != ((p) + (n));                        \
             ++_insert_i)                                     \
        {                                                     \
            for (t *_insert_j = _insert_i;                    \
                 _insert_j != (p) &&                          \
                 func(*_insert_j, *(_insert_j - 1U));         \
                 --_insert_j)                                 \
            {                                                 \
                ksort_swap(t, *_insert_j, *(_insert_j - 1U)); \
            }                                                 \
        }                                                     \
    } while (0)
#endif /* ksort_insert */

/* comb sort */
#ifndef ksort_comb
/*!
 @brief          Comb sort
 @param[in]      t: type of data array
 @param[in]      p: pointer of data array
 @param[in]      n: length of data array
 @param[in]      func: function of compare
*/
#define ksort_comb(t, p, n, func)                                         \
    do                                                                    \
    {                                                                     \
        const double _shrink_factor = 1.2473309501039786540366528676643;  \
        unsigned int _comb_swap = 0U;                                     \
        size_t _comb_gap = (n);                                           \
        do                                                                \
        {                                                                 \
            if (_comb_gap > 2U)                                           \
            {                                                             \
                _comb_gap = (size_t)((double)_comb_gap / _shrink_factor); \
                if (_comb_gap == 9U || _comb_gap == 10U)                  \
                {                                                         \
                    _comb_gap = 11U;                                      \
                }                                                         \
            }                                                             \
            _comb_swap = 0U;                                              \
            for (t *_comb_i = (p);                                        \
                 _comb_i < (p) + (n)-_comb_gap;                           \
                 ++_comb_i)                                               \
            {                                                             \
                t *_comb_j = _comb_i + _comb_gap;                         \
                if (func(*_comb_j, *_comb_i))                             \
                {                                                         \
                    ksort_swap(t, *_comb_i, *_comb_j);                    \
                    _comb_swap = 1U;                                      \
                }                                                         \
            }                                                             \
        } while (_comb_swap || _comb_gap > 2U);                           \
        if (_comb_gap != 1U)                                              \
        {                                                                 \
            ksort_insert(t, p, n, func);                                  \
        }                                                                 \
    } while (0)
#endif /* ksort_comb */

/* intro sort */

typedef struct ksort_stack_t
{
    void *left;
    void *right;

    unsigned int depth;
} ksort_stack_t;

#ifndef ksort_intro
/*!
 @brief          Intro sort
 @param[in]      t: type of data array
 @param[in]      p: pointer of data array
 @param[in]      n: length of data array
 @param[in]      func: function of compare
*/
#define ksort_intro(t, p, n, func)                                   \
    do                                                               \
    {                                                                \
        if ((n) < 1U)                                                \
        {                                                            \
            break;                                                   \
        }                                                            \
        else if ((n) == 2U)                                          \
        {                                                            \
            if (func(*(p + 1U), *(p)))                               \
            {                                                        \
                ksort_swap(t, *(p), *(p + 1U));                      \
            }                                                        \
            break;                                                   \
        }                                                            \
        unsigned int _intro_d = 2U;                                  \
        while (1ULL << _intro_d < (n))                               \
        {                                                            \
            ++_intro_d;                                              \
        }                                                            \
        ksort_stack_t *_intro_stack = (ksort_stack_t *)              \
            malloc(sizeof(ksort_stack_t) *                           \
                   (sizeof(size_t) * _intro_d + 2U));                \
        ksort_stack_t *_intro_top = _intro_stack;                    \
        _intro_d <<= 1U;                                             \
        t *_intro_s = (p);                                           \
        t *_intro_t = (p) + (n)-1U;                                  \
        t *_intro_i = NULL;                                          \
        t *_intro_j = NULL;                                          \
        t *_intro_k = NULL;                                          \
        for (;;)                                                     \
        {                                                            \
            if (_intro_s < _intro_t)                                 \
            {                                                        \
                if (--_intro_d == 0U)                                \
                {                                                    \
                    ksort_comb(t,                                    \
                               _intro_s,                             \
                               (size_t)(_intro_t - _intro_s) + 1U,   \
                               func);                                \
                    _intro_t = _intro_s;                             \
                    continue;                                        \
                }                                                    \
                _intro_i = _intro_s;                                 \
                _intro_j = _intro_t;                                 \
                _intro_k = _intro_i +                                \
                           ((_intro_j - _intro_i) >> 1U) + 1U;       \
                if (func(*_intro_k, *_intro_i))                      \
                {                                                    \
                    if (func(*_intro_k, *_intro_j))                  \
                    {                                                \
                        _intro_k = _intro_j;                         \
                    }                                                \
                }                                                    \
                else                                                 \
                {                                                    \
                    _intro_k = func(*_intro_j, *_intro_i)            \
                                   ? _intro_i                        \
                                   : _intro_j;                       \
                }                                                    \
                t _intro_rp = *_intro_k;                             \
                if (_intro_k != _intro_t)                            \
                {                                                    \
                    ksort_swap(t, *_intro_k, *_intro_t);             \
                }                                                    \
                for (;;)                                             \
                {                                                    \
                    do                                               \
                    {                                                \
                        ++_intro_i;                                  \
                    } while (func(*_intro_i, _intro_rp));            \
                    do                                               \
                    {                                                \
                        --_intro_j;                                  \
                    } while (_intro_i <= _intro_j &&                 \
                             func(_intro_rp, *_intro_j));            \
                    if (_intro_j <= _intro_i)                        \
                    {                                                \
                        break;                                       \
                    }                                                \
                    ksort_swap(t, *_intro_i, *_intro_j);             \
                }                                                    \
                ksort_swap(t, *_intro_i, *_intro_t);                 \
                if (_intro_i - _intro_s > _intro_t - _intro_i)       \
                {                                                    \
                    if (_intro_i - _intro_s > 16U)                   \
                    {                                                \
                        _intro_top->left = (void *)_intro_s;         \
                        _intro_top->right = (void *)(_intro_i - 1U); \
                        _intro_top->depth = _intro_d;                \
                        ++_intro_top;                                \
                    }                                                \
                    _intro_s = _intro_t - _intro_i > 16U             \
                                   ? _intro_i + 1U                   \
                                   : _intro_t;                       \
                }                                                    \
                else                                                 \
                {                                                    \
                    if (_intro_t - _intro_i > 16U)                   \
                    {                                                \
                        _intro_top->left = (void *)(_intro_i + 1U);  \
                        _intro_top->right = (void *)_intro_t;        \
                        _intro_top->depth = _intro_d;                \
                        ++_intro_top;                                \
                    }                                                \
                    _intro_t = _intro_i - _intro_s > 16U             \
                                   ? _intro_i - 1U                   \
                                   : _intro_s;                       \
                }                                                    \
            }                                                        \
            else                                                     \
            {                                                        \
                if (_intro_top == _intro_stack)                      \
                {                                                    \
                    free(_intro_stack);                              \
                    _intro_stack = NULL;                             \
                    ksort_insert(t, p, n, func);                     \
                    break;                                           \
                }                                                    \
                else                                                 \
                {                                                    \
                    --_intro_top;                                    \
                    _intro_s = (t *)_intro_top->left;                \
                    _intro_t = (t *)_intro_top->right;               \
                    _intro_d = _intro_top->depth;                    \
                }                                                    \
            }                                                        \
        }                                                            \
    } while (0)
#endif /* ksort_intro */

/* ksmall */
#ifndef ksort_ksmall
/*!
 @brief          Ksmall
 @param[in]      t: type of data array
 @param[out]     ret return variable of macro
 @param[in]      p: pointer of data array
 @param[in]      n: length of data array
 @param[in]      func: function of compare
 @param[in]      k   0U <= k < n
*/
#define ksort_ksmall(t, ret, p, n, func, k)                     \
    do                                                          \
    {                                                           \
        t *_ksmall_low = (p);                                   \
        t *_ksmall_high = (p) + (n)-1U;                         \
        t *_ksmall_k = (p) + (k) % (n);                         \
        t *_ksmall_ll = NULL;                                   \
        t *_ksmall_hh = NULL;                                   \
        t *_ksmall_mid = NULL;                                  \
        for (;;)                                                \
        {                                                       \
            if (_ksmall_high <= _ksmall_low)                    \
            {                                                   \
                ret = *_ksmall_k;                               \
                break;                                          \
            }                                                   \
            if (_ksmall_high == _ksmall_low + 1U)               \
            {                                                   \
                if (func(*_ksmall_high, *_ksmall_low))          \
                {                                               \
                    ksort_swap(t, *_ksmall_low, *_ksmall_high); \
                }                                               \
                ret = *_ksmall_k;                               \
                break;                                          \
            }                                                   \
            _ksmall_mid = _ksmall_low +                         \
                          (_ksmall_high - _ksmall_low) / 2U;    \
            if (func(*_ksmall_high, *_ksmall_mid))              \
            {                                                   \
                ksort_swap(t, *_ksmall_high, *_ksmall_mid);     \
            }                                                   \
            if (func(*_ksmall_high, *_ksmall_low))              \
            {                                                   \
                ksort_swap(t, *_ksmall_high, *_ksmall_low);     \
            }                                                   \
            if (func(*_ksmall_low, *_ksmall_mid))               \
            {                                                   \
                ksort_swap(t, *_ksmall_low, *_ksmall_mid);      \
            }                                                   \
            ksort_swap(t, *_ksmall_mid, *(_ksmall_low + 1U));   \
            _ksmall_ll = _ksmall_low + 1U;                      \
            _ksmall_hh = _ksmall_high;                          \
            for (;;)                                            \
            {                                                   \
                do                                              \
                {                                               \
                    ++_ksmall_ll;                               \
                } while (func(*_ksmall_ll, *_ksmall_low));      \
                do                                              \
                {                                               \
                    --_ksmall_hh;                               \
                } while (func(*_ksmall_low, *_ksmall_hh));      \
                if (_ksmall_hh < _ksmall_ll)                    \
                {                                               \
                    break;                                      \
                }                                               \
                ksort_swap(t, *_ksmall_ll, *_ksmall_hh);        \
            }                                                   \
            ksort_swap(t, *_ksmall_low, *_ksmall_hh);           \
            if (_ksmall_hh <= _ksmall_k)                        \
            {                                                   \
                _ksmall_low = _ksmall_ll;                       \
            }                                                   \
            if (_ksmall_hh >= _ksmall_k)                        \
            {                                                   \
                _ksmall_high = _ksmall_hh - 1U;                 \
            }                                                   \
        }                                                       \
    } while (0)
#endif /* ksort_ksmall */

/* Enddef to prevent recursive inclusion */
#endif /* __KSORT_H__ */

/* END OF FILE */
