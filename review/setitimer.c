/* ************************************************************************
> File Name:     setitimer.c
> Author:        程序员Eric
> 微信公众号:    源水本木
> Created Time:  Sat 07 Jan 2023 04:27:10 PM CST
> Description:   
 ************************************************************************/
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>

int main() {

    struct itimerval new_value;

    new_value.it_interval.tv_sec = 2;
    new_value.it_interval.tv_usec = 0;

    new_value.it_value.tv_sec = 3;
    new_value.it_value.tv_usec = 0;

    int ret = setitimer(ITIMER_REAL, &new_value, NULL);
    printf("alarm start...\n");

    if (ret == -1) {
        perror("setitimer"); 
        exit(0);
    }

    getchar();

    return 0;
}
