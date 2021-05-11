/**
 * *****************************************************************************
 * @file         test_kstring.c
 * @brief        test kstring library
 * @details      
 * @author       tqfx
 * @date         20210421
 * @version      1
 * @copyright    Copyright (C) 2021
 * @code         utf-8                                                  @endcode
 * *****************************************************************************
*/

/* Includes ------------------------------------------------------------------*/
#include "kstring.h"

/* Private includes ----------------------------------------------------------*/
#include <stdio.h>
#include <string.h>

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private user code ---------------------------------------------------------*/

int main(void)
{
    kstring_t *ks = ks_init();

    ksprintf(ks, "asdfghjklasdfghjklasdfghjkl");

    ks_ins(ks, 0, "test_kstring ");

    printf("%s\t%zu\n", ks_str(ks), ks_cnt(ks, "s"));

    ks_mod(ks, "s", "_");

    puts(ks_str(ks));

    ks_del(ks, "_");

    puts(ks_str(ks));

    ks_free(ks);

    return 0;
}

/************************ (C) COPYRIGHT tqfx *******************END OF FILE****/
