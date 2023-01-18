/* ************************************************************************
> File Name:     bytetrans.c
> Author:        程序员Eric
> 微信公众号:    源水本木
> Created Time:  Wed 18 Jan 2023 09:44:13 PM CST
> Description:   
 ************************************************************************/
#include <stdio.h>
#include <arpa/inet.h>

int main () {

    unsigned short a = 0x0102;
    printf("a = %x\n", a);

    unsigned short b = htons(a);
    printf("b = %x\n", b);

    return 0;
}
