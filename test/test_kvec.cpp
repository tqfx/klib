/*!
 @file           test_kvec.c
 @brief          test kvector library
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

#include "kvec.h"

#include <cstdio>
#include <cstring>
#include <ctime>
#include <vector>

/*!
 @brief          test kver_s
*/
void test1(void)
{
    kvec_s(unsigned int) kv;

    kv_init(kv);

    for (unsigned int i = 0; i != 5; ++i)
    {
        kv_push(unsigned int, kv, i);
    }

    for (unsigned int i = 5; i != 7; ++i)
    {
        unsigned int *n = kv_pushp(unsigned int, kv);

        *n = i;
    }

    for (unsigned int i = 7; i != 10; ++i)
    {
        kv_vi(unsigned int, kv, i) = i;
    }

    kvec_s(unsigned int) kv2;
    kv_init(kv2);
    kv_copy(unsigned int, kv2, kv);
    kv_clear(kv);

    for (unsigned int i = 0; i != 5; ++i)
    {
        unsigned int n = kv_pop(kv2);
        printf("%u ", n);
    }

    for (unsigned int i = 0; i != kv_size(kv2); ++i)
    {
        printf("%u ", kv_v(kv2, i));
    }

    printf("\nmemory = %zu\n", kv_max(kv2));

    kv_clear(kv2);
}

/* impl type and functon */
__KVEC_INIT(u32, unsigned int)

/*!
 @brief          test kver_t macros
*/
void test2(void)
{
    kvec_t(u32) * kv;

    kv_pinit(u32, kv);

    for (unsigned int i = 0; i != 5; ++i)
    {
        kv_ppush(unsigned int, kv, i);
    }

    for (unsigned int i = 5; i != 7; ++i)
    {
        unsigned int *n = kv_ppushp(unsigned int, kv);

        *n = i;
    }

    for (unsigned int i = 7; i != 10; ++i)
    {
        kv_pvi(unsigned int, kv, i) = i;
    }

    kvec_t(u32) *pkv = NULL;
    kv_pcopy(u32, unsigned int, pkv, kv);
    kv_pclear(kv);

    for (unsigned int i = 0; i != 5; ++i)
    {
        unsigned int n = kv_ppop(pkv);
        printf("%u ", n);
    }

    for (unsigned int i = 0; i != kv_psize(pkv); ++i)
    {
        printf("%u ", kv_pv(pkv, i));
    }

    printf("\nmemory = %zu\n", kv_pmax(pkv));

    kv_pclear(pkv);
}

/*!
 @brief          test kver_t function
*/
void test3(void)
{
    kvec_t(u32) * kv;

    kv_u32_pinit(&kv);

    for (unsigned int i = 0; i != 5; ++i)
    {
        kv_u32_push(kv, i);
    }

    for (unsigned int i = 5; i != 10; ++i)
    {
        kv_u32_vi(kv, i, i);
    }

    kvec_t(u32) kv2;
    kv_u32_init(&kv2);
    kv_u32_copy(&kv2, kv);
    kv_u32_pclear(&kv);

    for (unsigned int i = 0; i != 5; ++i)
    {
        unsigned int n = 0;
        kv_u32_pop(&n, &kv2);
        printf("%u ", n);
    }

    for (unsigned int i = 0; i != kv_u32_size(&kv2); ++i)
    {
        unsigned int n = 0;
        kv_u32_v(&n, &kv2, i);
        printf("%u ", n);
    }

    printf("\nmemory = %zu\n", kv_u32_max(&kv2));

    kv_u32_clear(&kv2);
}

/*!
 @brief          test c and c++
*/
void test4(void)
{
    unsigned int M = 10U;
    unsigned int N = 20000000U;
    unsigned int i = 0;
    unsigned int j = 0;

    clock_t t = clock();
    for (i = 0; i != M; ++i)
    {
        unsigned int *array = (unsigned int *)malloc(sizeof(int) * N);
        for (j = 0; j != N; ++j)
        {
            array[j] = j;
        }
        free(array);
    }
    printf("C array, preallocated: %.3f sec\n",
           (double)(clock() - t) / CLOCKS_PER_SEC);

    t = clock();
    for (i = 0; i != M; ++i)
    {
        unsigned int *array = 0;
        unsigned int max = 0;
        for (j = 0; j != N; ++j)
        {
            if (j == max)
            {
                max = max ? max << 1U : 2U;

                array = (unsigned int *)
                    realloc(array, sizeof(int) * (size_t)max);
            }
            array[j] = j;
        }
        free(array);
    }
    printf("C array, dynamic: %.3f sec\n",
           (double)(clock() - t) / CLOCKS_PER_SEC);

    t = clock();
    for (i = 0; i != M; ++i)
    {
        kvec_s(unsigned int) array;
        kv_init(array);
        kv_resize(unsigned int, array, N);
        for (j = 0; j != N; ++j)
        {
            kv_v(array, j) = j;
        }
        kv_clear(array);
    }
    printf("C vector, dynamic(kv_v): %.3f sec\n",
           (double)(clock() - t) / CLOCKS_PER_SEC);

    t = clock();
    for (i = 0; i != M; ++i)
    {
        kvec_s(unsigned int) array;
        kv_init(array);
        for (j = 0; j != N; ++j)
        {
            kv_push(unsigned int, array, j);
        }
        kv_clear(array);
    }
    printf("C vector, dynamic(kv_push): %.3f sec\n",
           (double)(clock() - t) / CLOCKS_PER_SEC);

    t = clock();
    for (i = 0; i != M; ++i)
    {
        std::vector<unsigned int> array;
        array.reserve(N);
        for (j = 0; j != N; ++j)
        {
            array[j] = j;
        }
    }
    printf("C++ vector, preallocated: %.3f sec\n",
           (double)(clock() - t) / CLOCKS_PER_SEC);

    t = clock();
    for (i = 0; i != M; ++i)
    {
        std::vector<unsigned int> array;
        for (j = 0; j != N; ++j)
        {
            array.push_back(j);
        }
    }
    printf("C++ vector, dynamic: %.3f sec\n",
           (double)(clock() - t) / CLOCKS_PER_SEC);
}

int main(void)
{
    test1();

    test2();

    test3();

    test4();

    return 0;
}

/* END OF FILE */
