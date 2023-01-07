/* ************************************************************************
> File Name:     alarm.c
> Author:        程序员Eric
> 微信公众号:    源水本木
> Created Time:  Sat 07 Jan 2023 04:14:53 PM CST
> Description:   
 ************************************************************************/
#include <unistd.h>
#include <stdio.h>

int main() {

    int seconds = alarm(5);
    printf("seconds = %d\n", seconds);

    sleep(2);
    seconds = alarm(2);
    printf("seconds = %d\n", seconds);

    while (1) {
    
    }

    return 0;
}
