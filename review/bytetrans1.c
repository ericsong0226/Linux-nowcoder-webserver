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

    char buf[4] = {192, 168, 1, 100};
    int num = *(int *)buf;
    int sum = htonl(num);

    unsigned char *p = (char *)&sum;

    printf("%d %d %d %d\n", *p, *(p + 1), *(p + 2), *(p + 3));

    printf("=============================\n");
    
    // ntonl
    unsigned char buf1[4] = {1, 1, 168, 192};
    int num1 = *(int *)buf1;
    int sum1 = ntohl(num1);
    unsigned char * p1 = (unsigned char *)&sum1;
    printf("%d %d %d %d\n", *p1, *(p1 + 1), *(p1 + 2), *(p1 + 3));

    printf("=============================\n");

    // ntohs
    unsigned short a1 = 0x0403;
    printf("a1 = %x\n", a1);

    unsigned short b1 = ntohs(a1);
    printf("b1 = %x\n", b1);
    
    return 0;
}
