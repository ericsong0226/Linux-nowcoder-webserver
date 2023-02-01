/* ************************************************************************
> File Name:     byteorder1.c
> Author:        程序员Eric
> 微信公众号:    源水本木
> Created Time:  Mon 30 Jan 2023 09:29:08 AM CST
> Description:   
 ************************************************************************/
#include <stdio.h>

int main () {

    union {
   
        short num;
        char bytes[sizeof(short)];
    } test;

    test.num = 0x0102;

    if ((test.bytes[0] == 1) && (test.bytes[1] == 2)) {
   
        printf("big\n");
    } else if ((test.bytes[0] == 2) && (test.bytes[1] == 1)) {
  
        printf("smalll\n");
    } else {
   
        printf("unknown\n");
    }

    return 0;
}
