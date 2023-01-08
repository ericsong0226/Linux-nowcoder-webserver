/* ************************************************************************
> File Name:     signal.c
> Author:        程序员Eric
> 微信公众号:    源水本木
> Created Time:  Sun 08 Jan 2023 10:22:53 AM CST
> Description:   
 ************************************************************************/
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void myalarm(int num) {

    printf("catch signal number : %d\n", num);
    printf("xxxxxxxxxxxxxxx\n");
}

int main() {

    signal(SIGALRM, myalarm);

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
