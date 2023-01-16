/* ************************************************************************
> File Name:     test_1.c
> Author:        程序员Eric
> 微信公众号:    源水本木
> Created Time:  Mon 16 Jan 2023 10:01:29 PM CST
> Description:   
 ************************************************************************/
#include <stdio.h>

int main() {
    int a = 10;
#ifdef DEBUG
    printf("i am a coding monkey...\n");
#endif
    for (int i = 0; i < 3; ++i) {
   
        printf("Hello gcc\n");

    }

    return 0;
}
