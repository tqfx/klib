/*!
 @file           test_kstring.c
 @brief          test kstring library
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

#include "kstring.h"

#include <stdio.h>
#include <string.h>

int main(void)
{
    kstring_t *ks = ks_init();

    ksprintf(ks, "asdfghjklasdfghjklasdfghjkl");
    printf("%s\t\t\t%s%zu\n", ks_str(ks), "count is ", ks_cnt(ks, "s"));

    ks_ins(ks, 0, "test_kstring ");
    printf("%s\t%s%zu\n", ks_str(ks), "insert \"test_kstring \", count is ", ks_cnt(ks, "s"));

    ks_mod1(ks, "s", "_");
    printf("%s\t%s\n", ks_str(ks), "replace the first \"_\" to \"s\"");

    ks_mod(ks, "s", "_");
    printf("%s\t%s\n", ks_str(ks), "replace all of the \"_\" to \"s\"");

    ks_del1(ks, "_");
    printf("%s\t\t%s\n", ks_str(ks), "delete the first \"_\"");

    ks_del(ks, "_");
    printf("%s\t\t%s\n", ks_str(ks), "delete all of \"_\"");

    ks_free(ks);

    return 0;
}

/* END OF FILE */
