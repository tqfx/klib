/**
 * *****************************************************************************
 * @file         test_ksort.c/h
 * @brief        test sort library
 * @details      
 * @author       tqfx
 * @date         20210101
 * @version      1
 * @copyright    Copyright (C) 2021
 * @code         utf-8                                                  @endcode
 * *****************************************************************************
*/

/* Includes ------------------------------------------------------------------*/
#include "ksort.h"

/* Private includes ----------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/

#define CMP(x, y) ((x) < (y))

/* Private typedef -----------------------------------------------------------*/
/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private user code ---------------------------------------------------------*/

void test_merge(size_t n)
{
    int *array = malloc(sizeof(int) * 10);

    srand((unsigned int)time(NULL));

    for (size_t i = 0; i < 10; ++i)
    {
        array[i] = rand() % 100;
    }

    printf("merge\t");

    ksort_merge(int, array, 10, CMP, NULL);

    for (size_t i = 0; i < 10; ++i)
    {
        printf("%i ", array[i]);
    }

    free(array);
    array = malloc(sizeof(int) * n);

    printf("\n%-10zu: ", n);
    fflush(stdout);

    for (size_t i = 0; i < n; ++i)
    {
        array[i] = rand();
    }

    clock_t t = clock();
    ksort_merge(int, array, n, CMP, NULL);
    printf("%.3f sec\n", (float)(clock() - t) / CLOCKS_PER_SEC);

    for (size_t i = 0U; i < n - 1U; ++i)
    {
        if (array[i] > array[i + 1])
        {
            fprintf(stderr, "Bug in merge sort!\n");
            exit(EXIT_FAILURE);
        }
    }

    free(array);
    array = NULL;
}

void test_heap(size_t n)
{
    int *array = malloc(sizeof(int) * 10);

    for (size_t i = 0; i < 10; ++i)
    {
        array[i] = rand() % 100;
    }

    printf("heap\t");

    ksort_heap_make(int, array, 10, CMP);
    ksort_heap(int, array, 10, CMP);

    for (size_t i = 0; i < 10; ++i)
    {
        printf("%i ", array[i]);
    }

    free(array);
    array = malloc(sizeof(int) * n);

    printf("\n%-10zu: ", n);
    fflush(stdout);

    for (size_t i = 0; i < n; ++i)
    {
        array[i] = rand();
    }

    clock_t t = clock();
    ksort_heap_make(int, array, n, CMP);
    ksort_heap(int, array, n, CMP);
    printf("%.3f sec\n", (float)(clock() - t) / CLOCKS_PER_SEC);

    for (size_t i = 0U; i < n - 1U; ++i)
    {
        if (array[i] > array[i + 1])
        {
            fprintf(stderr, "Bug in heap sort!\n");
            exit(EXIT_FAILURE);
        }
    }

    free(array);
    array = NULL;
}

void test_insert(size_t n)
{
    int *array = malloc(sizeof(int) * 10);

    for (size_t i = 0; i < 10; ++i)
    {
        array[i] = rand() % 100;
    }

    printf("insert\t");

    ksort_insert(int, array, 10, CMP);

    for (size_t i = 0; i < 10; ++i)
    {
        printf("%i ", array[i]);
    }

    free(array);
    array = malloc(sizeof(int) * n);

    printf("\n%-10zu: ", n);
    fflush(stdout);

    for (size_t i = 0; i < n; ++i)
    {
        array[i] = rand();
    }

    clock_t t = clock();
    ksort_insert(int, array, n, CMP);
    printf("%.3f sec\n", (float)(clock() - t) / CLOCKS_PER_SEC);

    for (size_t i = 0U; i < n - 1U; ++i)
    {
        if (array[i] > array[i + 1])
        {
            fprintf(stderr, "Bug in insert sort!\n");
            exit(EXIT_FAILURE);
        }
    }

    free(array);
    array = NULL;
}

void test_comb(size_t n)
{
    int *array = malloc(sizeof(int) * 10);

    for (size_t i = 0; i < 10; ++i)
    {
        array[i] = rand() % 100;
    }

    printf("comb\t");

    ksort_comb(int, array, 10, CMP);

    for (size_t i = 0; i < 10; ++i)
    {
        printf("%i ", array[i]);
    }

    free(array);
    array = malloc(sizeof(int) * n);

    printf("\n%-10zu: ", n);
    fflush(stdout);

    for (size_t i = 0; i < n; ++i)
    {
        array[i] = rand();
    }

    clock_t t = clock();
    ksort_comb(int, array, n, CMP);
    printf("%.3f sec\n", (float)(clock() - t) / CLOCKS_PER_SEC);

    for (size_t i = 0U; i < n - 1U; ++i)
    {
        if (array[i] > array[i + 1])
        {
            fprintf(stderr, "Bug in comb sort!\n");
            exit(EXIT_FAILURE);
        }
    }

    free(array);
    array = NULL;
}

void test_intro(size_t n)
{
    int *array = malloc(sizeof(int) * 10);

    for (size_t i = 0; i < 10; ++i)
    {
        array[i] = rand() % 100;
    }

    printf("intro\t");

    ksort_intro(int, array, 10, CMP);

    for (size_t i = 0; i < 10; ++i)
    {
        printf("%i ", array[i]);
    }

    free(array);
    array = malloc(sizeof(int) * n);

    printf("\n%-10zu: ", n);
    fflush(stdout);

    for (size_t i = 0; i < n; ++i)
    {
        array[i] = rand();
    }

    clock_t t = clock();
    ksort_intro(int, array, n, CMP);
    printf("%.3f sec\n", (float)(clock() - t) / CLOCKS_PER_SEC);

    for (size_t i = 0U; i < n - 1U; ++i)
    {
        if (array[i] > array[i + 1])
        {
            fprintf(stderr, "Bug in intro sort!\n");
            exit(EXIT_FAILURE);
        }
    }

    free(array);
    array = NULL;
}

void test_ksmall(size_t n)
{
    printf("ksmall\t");
    int *array = malloc(sizeof(int) * n);

    for (size_t i = 0; i < n; ++i)
    {
        array[i] = rand();
    }

    ksort_merge(int, array, n, CMP, NULL);

    clock_t t     = clock();
    int     x     = -1;
    size_t  index = (size_t)rand();
    ksort_ksmall(int, x, array, n, CMP, index);
    printf("[%zu] %i\n%-10zu: ", index, x, n);
    printf("%.3f sec\n", (float)(clock() - t) / CLOCKS_PER_SEC);

    free(array);
    array = NULL;
}

int main(void)
{
    size_t n = 10000000;

    unsigned int t = (unsigned int)time(NULL);

    srand(t);
    test_merge(n);

    srand(t);
    test_heap(n);

    srand(t);
    test_comb(n);

    srand(t);
    test_insert(n / 100U);

    srand(t);
    test_intro(n);

    srand(t);
    test_ksmall(n);

    return 0;
}

/************************ (C) COPYRIGHT tqfx *******************END OF FILE****/
