/* ************************************************************************
> File Name:     sigset.c
> Author:        程序员Eric
> 微信公众号:    源水本木
> Created Time:  Sun 08 Jan 2023 10:55:57 AM CST
> Description:   
 ************************************************************************/
#include <stdio.h>
#include <signal.h>

int main() {

    sigset_t set;

    sigemptyset(&set);

    int ret = sigismember(&set, SIGINT);
    if (ret == 0) {
        printf("SIGINT nonblock\n"); 
    } else if (ret == 1) {
        printf("SIGINT block\n"); 
    }

    sigaddset(&set, SIGINT);
    sigaddset(&set, SIGQUIT);

    ret = sigismember(&set, SIGINT);
    if (ret == 0) {
        printf("SIGINT nonblock\n"); 
    } else if (ret == 1) {
        printf("SIGINT block\n"); 
    }

    ret = sigismember(&set, SIGQUIT);
    if (ret == 0) {
        printf("SIGQUIT nonblock\n"); 
    } else if (ret == 1) {
        printf("SIGQUIT block\n"); 
    }

    sigdelset(&set, SIGQUIT);

    ret = sigismember(&set, SIGQUIT);
    if (ret == 0) {
        printf("SIGQUIT nonblock\n");
    } else if (ret == 1) {
        printf("SIGQUIT block\n"); 
    }

    return 0;
}
