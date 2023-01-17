/* ************************************************************************
> File Name:     byteorder.c
> Author:        程序员Eric
> 微信公众号:    源水本木
> Created Time:  Tue 17 Jan 2023 08:43:34 PM CST
> Description:   
 ************************************************************************/
#include <stdio.h>

int main() {

    union {
   
        short value;
        char bytes[sizeof(short)];
    } test; 

    test.value = 0x0102;

    if (test.bytes[0] == 1 && (test.bytes[1] == 2)) {
   
        printf("big byteorder\n");
    } else if (test.bytes[0] == 2 && (test.bytes[1] == 1)) {
   
        printf("small byteorder\n");
    } else {
   
        printf("unknow\n");
    }

    return 0;
}
