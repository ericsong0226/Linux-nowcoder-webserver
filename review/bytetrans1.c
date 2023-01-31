/* ************************************************************************
> File Name:     bytetrans1.c
> Author:        程序员Eric
> 微信公众号:    源水本木
> Created Time:  Tue 31 Jan 2023 09:17:32 AM CST
> Description:   
 ************************************************************************/
#include <stdio.h>
#include <arpa/inet.h>

int main() {

    unsigned short a = 0x0102;
    printf("a = %x\n", a);

    unsigned short b = htons(a);
    printf("b = %x\n", b);

    printf("===========================\n");

    return 0;
}
