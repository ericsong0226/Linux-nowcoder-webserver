/* ************************************************************************
> File Name:     alarm1.c
> Author:        程序员Eric
> 微信公众号:    源水本木
> Created Time:  Sat 07 Jan 2023 04:21:16 PM CST
> Description:   
 ************************************************************************/
#include <unistd.h>
#include <stdio.h>

int main() {

    alarm(1);

    int i = 0;
    while (1) {
   
        printf("%i\n", i++);
    }

    return 0;
}
