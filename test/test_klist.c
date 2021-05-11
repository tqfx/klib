/**
 * *****************************************************************************
 * @file         test_klist.c
 * @brief        test klist library
 * @details
 * @author       tqfx
 * @date         20210212
 * @version      1
 * @copyright    Copyright (C) 2021
 * @code         utf-8                                                  @endcode
 * *****************************************************************************
*/

/* Includes ------------------------------------------------------------------*/
#include "klist.h"

/* Private includes ----------------------------------------------------------*/
#include <stdio.h>

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/

#define test_free(x) printf("%i ", x->data)

/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private user code ---------------------------------------------------------*/

__KLIST_INIT(i32, int, test_free)

void test1(void)
{
    klist_s(i32) kl;

    kl_init(i32, kl);

    for (int i = -5; i < 0; i++)
    {
        kl_push(i32, kl, i);
    }

    for (int i = 5; i < 10; i++)
    {
        int *px = NULL;
        kl_pushp(i32, kl, px);
        *px = i;
    }

    for (int i = 0; i < 5; i++)
    {
        int x = 0;
        kl_shift(i32, kl, x);
        printf("%i ", x);
    }

    while (kl_begin(kl) != kl_end(kl))
    {
        int *px = NULL;
        kl_shiftp(i32, kl, px);
        printf("%i ", *px);
    }

    printf("\nalloc\t= %zu\nfree\t= %zu\nreal\t= %zu\n",
           kl.kmp->cnt,
           kl.kmp->n,
           kl.kmp->m);

    printf("clear: ");
    kl_clear(i32, test_free, kl);
    printf("\n");
}

void test2(void)
{
    klist_t(i32) *pkl = NULL;

    kl_pinit(i32, pkl);

    for (int i = -5; i < 0; i++)
    {
        kl_ppush(i32, pkl, i);
    }

    for (int i = 5; i < 10; i++)
    {
        int *px = NULL;
        kl_ppushp(i32, pkl, px);
        *px = i;
    }

    for (int i = 0; i < 5; i++)
    {
        int x = 0;
        kl_pshift(i32, pkl, x);
        printf("%i ", x);
    }

    while (kl_pbegin(pkl) != kl_pend(pkl))
    {
        int *px = NULL;
        kl_pshiftp(i32, pkl, px);
        printf("%i ", *px);
    }

    printf("\nalloc\t= %zu\nfree\t= %zu\nreal\t= %zu\n",
           pkl->kmp->cnt,
           pkl->kmp->n,
           pkl->kmp->m);

    printf("clear: ");
    kl_pclear(i32, test_free, pkl);
    printf("\n");
}

void test3(void)
{
    klist_t(i32) *kl = NULL;

    kl_i32_pinit(&kl);

    for (int i = -5; i < 0; i++)
    {
        kl_i32_push(kl, i);
    }

    for (int i = 5; i < 10; i++)
    {
        int *x = kl_i32_pushp(kl);
        *x     = i;
    }

    for (int i = 0; i < 5; i++)
    {
        int x = 0;

        kl_i32_shift(kl, &x);

        printf("%i ", x);
    }

    for (;;)
    {
        int x = 0;

        if (kl_i32_shift(kl, &x))
        {
            break;
        }

        printf("%i ", x);
    }

    printf("\nalloc\t= %zu\nfree\t= %zu\nreal\t= %zu\n",
           kl->kmp->cnt,
           kl->kmp->n,
           kl->kmp->m);

    printf("clear: ");
    kl_i32_pclear(&kl);
    printf("\n");
}

int main(void)
{
    test1(); /* test klist_s */

    test2(); /* test klist macros */

    test3(); /* test klist function */

    return 0;
}

/************************ (C) COPYRIGHT tqfx *******************END OF FILE****/
