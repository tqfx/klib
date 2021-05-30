/*!
 @file           test_klist.c
 @brief          test klist library
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

#include "klist.h"

#include <stdio.h>

#define test_free(x) printf("%i ", x->data)

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
        *x = i;
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

/* END OF FILE */
