/* ************************************************************************
> File Name:     sigaction.c
> Author:        程序员Eric
> 微信公众号:    源水本木
> Created Time:  Sun 08 Jan 2023 02:45:40 PM CST
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

    struct sigaction act;
    act.sa_flags = 0;
    act.sa_handler = myalarm;
    sigemptyset(&act.sa_mask);

    sigaction(SIGALRM, &act, NULL);

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

    while(1);

    return 0;
}
