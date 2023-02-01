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

<<<<<<< HEAD
    char buf[4] = {192, 168, 1, 100};
    int num = *(int *)buf;
    int sum = htonl(num);

    unsigned char *p = (char *)&sum;

    printf("%d %d %d %d\n", *p, *(p + 1), *(p + 2), *(p + 3));

    printf("=============================\n");
    
=======
>>>>>>> c9c21422f127d71f667e0892df15bf52b10c5ba3
    return 0;
}
