/**
 * *****************************************************************************
 * @file         ksort.h
 * @brief        sort library
 * @details      generic sort, including introsort, merge sort, heap sort,
 *               comb sort, Knuth shuffle and  k-small algorithm.
 * @author       tqfx
 * @date         20210421
 * @version      1
 * @copyright    Copyright (C) 2021
 * @code         utf-8                                                  @endcode
 * *****************************************************************************
*/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __KSORT_H__
#define __KSORT_H__

/* Includes ------------------------------------------------------------------*/
#include "klib.h"

/* Private includes ----------------------------------------------------------*/
#include <stdlib.h>
#include <string.h>

/* swap ----------------------------------------------------------------------*/
#undef __KSORT_SWAP

#define __KSORT_SWAP(_T_, _A_, _B_) \
                                    \
    do                              \
    {                               \
        _T_ _swap = (_A_);          \
        (_A_)     = (_B_);          \
        (_B_)     = _swap;          \
    } while (0)

#ifndef ksort_swap

/**
 * @brief        swap _a_ and _b_
 * @param[in]    _t_: type of swep
 * @param[in]    _a_: variable that need to swap
 * @param[in]    _b_: variable that need to swap
*/
#define ksort_swap(_t_, _a_, _b_) \
                                  \
    __KSORT_SWAP(_t_, _a_, _b_)

#endif /* ksort_swap */

/* merge sort ----------------------------------------------------------------*/
#undef __KSORT_MERGE

#define __KSORT_MERGE(_T_, _P_, _N_, _FUN_, _A_)                    \
                                                                    \
    do                                                              \
    {                                                               \
        _T_* _merge_p_[2U] = {                                      \
            (_P_),                                                  \
            (_A_)                                                   \
                ? (_A_)                                             \
                : (_T_*)malloc(sizeof(*(_P_)) * (_N_)),             \
        };                                                          \
        unsigned int _merge_site_ = 0U;                             \
        for (size_t _merge_step_ = 1U;                              \
             _merge_step_ < (_N_);                                  \
             _merge_step_ <<= 1U)                                   \
        {                                                           \
            _T_* _merge_a_ = _merge_p_[_merge_site_];               \
            _T_* _merge_b_ = _merge_p_[!_merge_site_];              \
            while (_merge_b_ != (_merge_p_[!_merge_site_] + (_N_))) \
            {                                                       \
                _T_* _merge_a1_ = _merge_a_;                        \
                _T_* _merge_e1_ =                                   \
                    (_merge_a_ + _merge_step_) <                    \
                            (_merge_p_[_merge_site_] + (_N_))       \
                        ? (_merge_a_ + _merge_step_)                \
                        : (_merge_p_[_merge_site_] + (_N_));        \
                _T_* _merge_a2_ = _merge_e1_;                       \
                _T_* _merge_e2_ =                                   \
                    (_merge_a_ + (_merge_step_ << 1U)) <            \
                            (_merge_p_[_merge_site_] + (_N_))       \
                        ? (_merge_a_ + (_merge_step_ << 1U))        \
                        : (_merge_p_[_merge_site_] + (_N_));        \
                while (_merge_a1_ != _merge_e1_ &&                  \
                       _merge_a2_ != _merge_e2_)                    \
                {                                                   \
                    if (_FUN_(*_merge_a1_, *_merge_a2_))            \
                    {                                               \
                        *_merge_b_++ = *_merge_a1_++;               \
                    }                                               \
                    else                                            \
                    {                                               \
                        *_merge_b_++ = *_merge_a2_++;               \
                    }                                               \
                }                                                   \
                while (_merge_a1_ != _merge_e1_)                    \
                {                                                   \
                    *_merge_b_++ = *_merge_a1_++;                   \
                }                                                   \
                while (_merge_a2_ != _merge_e2_)                    \
                {                                                   \
                    *_merge_b_++ = *_merge_a2_++;                   \
                }                                                   \
                _merge_a_ = _merge_e2_;                             \
            }                                                       \
            _merge_site_ = !_merge_site_;                           \
        }                                                           \
        if (_merge_site_)                                           \
        {                                                           \
            _T_* _merge_a_ = _merge_p_[0U];                         \
            _T_* _merge_b_ = _merge_p_[1U];                         \
            while (_merge_a_ != (_merge_p_[0U] + (_N_)))            \
            {                                                       \
                *_merge_a_++ = *_merge_b_++;                        \
            }                                                       \
        }                                                           \
        if (!(_A_))                                                 \
        {                                                           \
            free(_merge_p_[1U]);                                    \
            _merge_p_[1U] = NULL;                                   \
        }                                                           \
    } while (0)

#ifndef ksort_merge

/**
 * @brief        Merge sort
 * @param[in]    _t_: type of data array
 * @param[in]    _p_: pointer of data array
 * @param[in]    _n_: length of data array
 * @param[in]    _fun_: function of compare
 * @param[in]    _a_: pointer of buffer, length >= _n_
*/
#define ksort_merge(_t_, _p_, _n_, _fun_, _a_) \
                                               \
    __KSORT_MERGE(_t_, _p_, _n_, _fun_, _a_)

#endif /* ksort_merge */

/* heap adjust ---------------------------------------------------------------*/
#undef __KSORT_HEAP_ADJUST

#define __KSORT_HEAP_ADJUST(_T_, _P_, _I_, _N_, _FUN_)        \
                                                              \
    do                                                        \
    {                                                         \
        _T_    _heap_p_ = (_P_)[(_I_)];                       \
        size_t _heap_i_ = (_I_);                              \
        size_t _heap_j_ = (_I_);                              \
        while ((_heap_i_ = (_heap_i_ << 1U) + 1U) < (_N_))    \
        {                                                     \
            if (_heap_i_ != (_N_)-1U &&                       \
                _FUN_((_P_)[_heap_i_], (_P_)[_heap_i_ + 1U])) \
            {                                                 \
                ++_heap_i_;                                   \
            }                                                 \
            if (_FUN_((_P_)[_heap_i_], _heap_p_))             \
            {                                                 \
                break;                                        \
            }                                                 \
            (_P_)[_heap_j_] = (_P_)[_heap_i_];                \
            _heap_j_        = _heap_i_;                       \
        }                                                     \
        (_P_)[_heap_j_] = _heap_p_;                           \
    } while (0)

#ifndef ksort_heap_adjust

/**
 * @brief        Heap adjust
 * @param[in]    _t_: type of data array
 * @param[in]    _p_: pointer of data array
 * @param[in]    _i_: index of data array
 * @param[in]    _n_: length of data array
 * @param[in]    _fun_: function of compare
*/
#define ksort_heap_adjust(_t_, _p_, _i_, _n_, _fun_) \
                                                     \
    __KSORT_HEAP_ADJUST(_t_, _p_, _i_, _n_, _fun_)

#endif /* ksort_heap_adjust */

/* heap make -----------------------------------------------------------------*/
#undef __KSORT_HEAP_MAKE

#define __KSORT_HEAP_MAKE(_T_, _P_, _N_, _FUN_)                  \
                                                                 \
    do                                                           \
    {                                                            \
        for (size_t _heap_k_ = ((_N_) >> 1U) - 1U;               \
             _heap_k_ != (size_t)(-1);                           \
             --_heap_k_)                                         \
        {                                                        \
            __KSORT_HEAP_ADJUST(_T_, _P_, _heap_k_, _N_, _FUN_); \
        }                                                        \
    } while (0)

#ifndef ksort_heap_make

/**
 * @brief        Heap make
 * @param[in]    _t_: type of data array
 * @param[in]    _p_: pointer of data array
 * @param[in]    _n_: length of data array
 * @param[in]    _fun_: function of compare
*/
#define ksort_heap_make(_t_, _p_, _n_, _fun_) \
                                              \
    __KSORT_HEAP_MAKE(_t_, _p_, _n_, _fun_)

#endif /* ksort_heap_make */

/* heap sort -----------------------------------------------------------------*/
#undef __KSORT_HEAP

#define __KSORT_HEAP(_T_, _P_, _N_, _FUN_)                      \
                                                                \
    do                                                          \
    {                                                           \
        for (size_t _heap_k_ = (_N_)-1U; _heap_k_; --_heap_k_)  \
        {                                                       \
            __KSORT_SWAP(_T_, *(_P_), (_P_)[_heap_k_]);         \
            __KSORT_HEAP_ADJUST(_T_, _P_, 0U, _heap_k_, _FUN_); \
        }                                                       \
    } while (0)

#ifndef ksort_heap

/**
 * @brief        Heap sort
 * @param[in]    _t_: type of data array
 * @param[in]    _p_: pointer of data array
 * @param[in]    _n_: length of data array
 * @param[in]    _fun_: function of compare
*/
#define ksort_heap(_t_, _p_, _n_, _fun_) \
                                         \
    __KSORT_HEAP(_t_, _p_, _n_, _fun_)

#endif /* ksort_heap */

/* insert sort ---------------------------------------------------------------*/
#undef __KSORT_INSERT

#define __KSORT_INSERT(_T_, _P_, _N_, _FUN_)                        \
                                                                    \
    do                                                              \
    {                                                               \
        for (_T_* _insert_i_ = (_P_) + 1U;                          \
             _insert_i_ != ((_P_) + (_N_));                         \
             ++_insert_i_)                                          \
        {                                                           \
            for (_T_* _insert_j_ = _insert_i_;                      \
                 _insert_j_ != (_P_) &&                             \
                 _FUN_(*_insert_j_, *(_insert_j_ - 1U));            \
                 --_insert_j_)                                      \
            {                                                       \
                __KSORT_SWAP(_T_, *_insert_j_, *(_insert_j_ - 1U)); \
            }                                                       \
        }                                                           \
    } while (0)

#ifndef ksort_insert

/**
 * @brief        Insert sort
 * @param[in]    _t_: type of data array
 * @param[in]    _p_: pointer of data array
 * @param[in]    _n_: length of data array
 * @param[in]    _fun_: function of compare
*/
#define ksort_insert(_t_, _p_, _n_, _fun_) \
                                           \
    __KSORT_INSERT(_t_, _p_, _n_, _fun_)

#endif /* ksort_insert */

/* comb sort -----------------------------------------------------------------*/
#undef __KSORT_COMB

#define __KSORT_COMB(_T_, _P_, _N_, _FUN_)                                   \
                                                                             \
    do                                                                       \
    {                                                                        \
        const double _shrink_factor_ = 1.2473309501039786540366528676643;    \
        unsigned int _comb_swap_     = 0U;                                   \
        size_t       _comb_gap_      = (_N_);                                \
        do                                                                   \
        {                                                                    \
            if (_comb_gap_ > 2U)                                             \
            {                                                                \
                _comb_gap_ = (size_t)((double)_comb_gap_ / _shrink_factor_); \
                if (_comb_gap_ == 9U || _comb_gap_ == 10U)                   \
                {                                                            \
                    _comb_gap_ = 11U;                                        \
                }                                                            \
            }                                                                \
            _comb_swap_ = 0U;                                                \
            for (_T_* _comb_i_ = (_P_);                                      \
                 _comb_i_ < (_P_) + (_N_)-_comb_gap_;                        \
                 ++_comb_i_)                                                 \
            {                                                                \
                _T_* _comb_j_ = _comb_i_ + _comb_gap_;                       \
                if (_FUN_(*_comb_j_, *_comb_i_))                             \
                {                                                            \
                    __KSORT_SWAP(_T_, *_comb_i_, *_comb_j_);                 \
                    _comb_swap_ = 1U;                                        \
                }                                                            \
            }                                                                \
        } while (_comb_swap_ || _comb_gap_ > 2U);                            \
        if (_comb_gap_ != 1U)                                                \
        {                                                                    \
            __KSORT_INSERT(_T_, _P_, _N_, _FUN_);                            \
        }                                                                    \
    } while (0)

#ifndef ksort_comb

/**
 * @brief        Comb sort
 * @param[in]    _t_: type of data array
 * @param[in]    _p_: pointer of data array
 * @param[in]    _n_: length of data array
 * @param[in]    _fun_: function of compare
*/
#define ksort_comb(_t_, _p_, _n_, _fun_) \
                                         \
    __KSORT_COMB(_t_, _p_, _n_, _fun_)

#endif /* ksort_comb */

/* intro sort ----------------------------------------------------------------*/

typedef struct
{
    void* left;
    void* right;

    unsigned int depth;
} ksort_stack_t;

#define __KSORT_INTRO(_T_, _P_, _N_, _FUN_)                            \
                                                                       \
    do                                                                 \
    {                                                                  \
        if ((_N_) < 1U)                                                \
        {                                                              \
            break;                                                     \
        }                                                              \
        else if ((_N_) == 2U)                                          \
        {                                                              \
            if (_FUN_(*(_P_ + 1U), *(_P_)))                            \
            {                                                          \
                __KSORT_SWAP(_T_, *(_P_), *(_P_ + 1U));                \
            }                                                          \
            break;                                                     \
        }                                                              \
        unsigned int _intro_d_ = 2U;                                   \
        while (1ULL << _intro_d_ < (_N_))                              \
        {                                                              \
            ++_intro_d_;                                               \
        }                                                              \
        ksort_stack_t* _intro_stack_ = (ksort_stack_t*)                \
            malloc(sizeof(ksort_stack_t) *                             \
                   (sizeof(size_t) * _intro_d_ + 2U));                 \
        ksort_stack_t* _intro_top_ = _intro_stack_;                    \
        _intro_d_ <<= 1U;                                              \
        _T_* _intro_s_ = (_P_);                                        \
        _T_* _intro_t_ = (_P_) + (_N_)-1U;                             \
        _T_* _intro_i_ = NULL;                                         \
        _T_* _intro_j_ = NULL;                                         \
        _T_* _intro_k_ = NULL;                                         \
        for (;;)                                                       \
        {                                                              \
            if (_intro_s_ < _intro_t_)                                 \
            {                                                          \
                if (--_intro_d_ == 0U)                                 \
                {                                                      \
                    __KSORT_COMB(_T_,                                  \
                                 _intro_s_,                            \
                                 (size_t)(_intro_t_ - _intro_s_) + 1U, \
                                 _FUN_);                               \
                    _intro_t_ = _intro_s_;                             \
                    continue;                                          \
                }                                                      \
                _intro_i_ = _intro_s_;                                 \
                _intro_j_ = _intro_t_;                                 \
                _intro_k_ = _intro_i_ +                                \
                            ((_intro_j_ - _intro_i_) >> 1U) + 1U;      \
                if (_FUN_(*_intro_k_, *_intro_i_))                     \
                {                                                      \
                    if (_FUN_(*_intro_k_, *_intro_j_))                 \
                    {                                                  \
                        _intro_k_ = _intro_j_;                         \
                    }                                                  \
                }                                                      \
                else                                                   \
                {                                                      \
                    _intro_k_ = _FUN_(*_intro_j_, *_intro_i_)          \
                                    ? _intro_i_                        \
                                    : _intro_j_;                       \
                }                                                      \
                _T_ _intro_rp_ = *_intro_k_;                           \
                if (_intro_k_ != _intro_t_)                            \
                {                                                      \
                    __KSORT_SWAP(_T_, *_intro_k_, *_intro_t_);         \
                }                                                      \
                for (;;)                                               \
                {                                                      \
                    do                                                 \
                    {                                                  \
                        ++_intro_i_;                                   \
                    } while (_FUN_(*_intro_i_, _intro_rp_));           \
                    do                                                 \
                    {                                                  \
                        --_intro_j_;                                   \
                    } while (_intro_i_ <= _intro_j_ &&                 \
                             _FUN_(_intro_rp_, *_intro_j_));           \
                    if (_intro_j_ <= _intro_i_)                        \
                    {                                                  \
                        break;                                         \
                    }                                                  \
                    __KSORT_SWAP(_T_, *_intro_i_, *_intro_j_);         \
                }                                                      \
                __KSORT_SWAP(_T_, *_intro_i_, *_intro_t_);             \
                if (_intro_i_ - _intro_s_ > _intro_t_ - _intro_i_)     \
                {                                                      \
                    if (_intro_i_ - _intro_s_ > 16U)                   \
                    {                                                  \
                        _intro_top_->left  = (void*)_intro_s_;         \
                        _intro_top_->right = (void*)(_intro_i_ - 1U);  \
                        _intro_top_->depth = _intro_d_;                \
                        ++_intro_top_;                                 \
                    }                                                  \
                    _intro_s_ = _intro_t_ - _intro_i_ > 16U            \
                                    ? _intro_i_ + 1U                   \
                                    : _intro_t_;                       \
                }                                                      \
                else                                                   \
                {                                                      \
                    if (_intro_t_ - _intro_i_ > 16U)                   \
                    {                                                  \
                        _intro_top_->left  = (void*)(_intro_i_ + 1U);  \
                        _intro_top_->right = (void*)_intro_t_;         \
                        _intro_top_->depth = _intro_d_;                \
                        ++_intro_top_;                                 \
                    }                                                  \
                    _intro_t_ = _intro_i_ - _intro_s_ > 16U            \
                                    ? _intro_i_ - 1U                   \
                                    : _intro_s_;                       \
                }                                                      \
            }                                                          \
            else                                                       \
            {                                                          \
                if (_intro_top_ == _intro_stack_)                      \
                {                                                      \
                    free(_intro_stack_);                               \
                    _intro_stack_ = NULL;                              \
                    __KSORT_INSERT(_T_, _P_, _N_, _FUN_);              \
                    break;                                             \
                }                                                      \
                else                                                   \
                {                                                      \
                    --_intro_top_;                                     \
                    _intro_s_ = (_T_*)_intro_top_->left;               \
                    _intro_t_ = (_T_*)_intro_top_->right;              \
                    _intro_d_ = _intro_top_->depth;                    \
                }                                                      \
            }                                                          \
        }                                                              \
    } while (0)

#ifndef ksort_intro

/**
 * @brief        Intro sort
 * @param[in]    _t_: type of data array
 * @param[in]    _p_: pointer of data array
 * @param[in]    _n_: length of data array
 * @param[in]    _fun_: function of compare
*/
#define ksort_intro(_t_, _p_, _n_, _fun_) \
                                          \
    __KSORT_INTRO(_t_, _p_, _n_, _fun_)

#endif /* ksort_intro */

/* intro sort ----------------------------------------------------------------*/
#undef __KSORT_KSMALL

#define __KSORT_KSMALL(_T_, _RET_, _P_, _N_, _FUN_, _K_)              \
                                                                      \
    do                                                                \
    {                                                                 \
        _T_* _ksmall_low_  = (_P_);                                   \
        _T_* _ksmall_high_ = (_P_) + (_N_)-1U;                        \
        _T_* _ksmall_k_    = (_P_) + (_K_) % (_N_);                   \
        _T_* _ksmall_ll_   = NULL;                                    \
        _T_* _ksmall_hh_   = NULL;                                    \
        _T_* _ksmall_mid_  = NULL;                                    \
        for (;;)                                                      \
        {                                                             \
            if (_ksmall_high_ <= _ksmall_low_)                        \
            {                                                         \
                _RET_ = *_ksmall_k_;                                  \
                break;                                                \
            }                                                         \
            if (_ksmall_high_ == _ksmall_low_ + 1U)                   \
            {                                                         \
                if (_FUN_(*_ksmall_high_, *_ksmall_low_))             \
                {                                                     \
                    __KSORT_SWAP(_T_, *_ksmall_low_, *_ksmall_high_); \
                }                                                     \
                _RET_ = *_ksmall_k_;                                  \
                break;                                                \
            }                                                         \
            _ksmall_mid_ = _ksmall_low_ +                             \
                           (_ksmall_high_ - _ksmall_low_) / 2U;       \
            if (_FUN_(*_ksmall_high_, *_ksmall_mid_))                 \
            {                                                         \
                __KSORT_SWAP(_T_, *_ksmall_high_, *_ksmall_mid_);     \
            }                                                         \
            if (_FUN_(*_ksmall_high_, *_ksmall_low_))                 \
            {                                                         \
                __KSORT_SWAP(_T_, *_ksmall_high_, *_ksmall_low_);     \
            }                                                         \
            if (_FUN_(*_ksmall_low_, *_ksmall_mid_))                  \
            {                                                         \
                __KSORT_SWAP(_T_, *_ksmall_low_, *_ksmall_mid_);      \
            }                                                         \
            __KSORT_SWAP(_T_, *_ksmall_mid_, *(_ksmall_low_ + 1U));   \
            _ksmall_ll_ = _ksmall_low_ + 1U;                          \
            _ksmall_hh_ = _ksmall_high_;                              \
            for (;;)                                                  \
            {                                                         \
                do                                                    \
                {                                                     \
                    ++_ksmall_ll_;                                    \
                } while (_FUN_(*_ksmall_ll_, *_ksmall_low_));         \
                do                                                    \
                {                                                     \
                    --_ksmall_hh_;                                    \
                } while (_FUN_(*_ksmall_low_, *_ksmall_hh_));         \
                if (_ksmall_hh_ < _ksmall_ll_)                        \
                {                                                     \
                    break;                                            \
                }                                                     \
                __KSORT_SWAP(_T_, *_ksmall_ll_, *_ksmall_hh_);        \
            }                                                         \
            __KSORT_SWAP(_T_, *_ksmall_low_, *_ksmall_hh_);           \
            if (_ksmall_hh_ <= _ksmall_k_)                            \
            {                                                         \
                _ksmall_low_ = _ksmall_ll_;                           \
            }                                                         \
            if (_ksmall_hh_ >= _ksmall_k_)                            \
            {                                                         \
                _ksmall_high_ = _ksmall_hh_ - 1U;                     \
            }                                                         \
        }                                                             \
    } while (0)

#ifndef ksort_ksmall

/**
 * @brief        Ksmall
 * @param[in]    _t_: type of data array
 * @param[out]   _ret_ return variable of macro
 * @param[in]    _p_: pointer of data array
 * @param[in]    _n_: length of data array
 * @param[in]    _fun_: function of compare
 * @param[in]    _k_   0U <= _k_ < _n_
*/
#define ksort_ksmall(_t_, _ret_, _p_, _n_, _fun_, _k_) \
                                                       \
    __KSORT_KSMALL(_t_, _ret_, _p_, _n_, _fun_, _k_)

#endif /* ksort_ksmall */

/* __KSORT_H__ ---------------------------------------------------------------*/
#endif /* __KSORT_H__ */

/************************ (C) COPYRIGHT tqfx *******************END OF FILE****/
