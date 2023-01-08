/* ************************************************************************
> File Name:     sigchld.c
> Author:        程序员Eric
> 微信公众号:    源水本木
> Created Time:  Sun 08 Jan 2023 03:12:14 PM CST
> Description:   
 ************************************************************************/
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <signal.h>
#include <sys/wait.h>

void myFun(int num) {

    printf("catch signal : %d\n", num);

    while (1) {
   
        int ret = waitpid(-1, NULL, WNOHANG);
        if (ret > 0) {
       
            printf("child die, pid = %d\n", ret);
        } else if (ret == 0) {
       
            break;
        } else if (ret == -1) {
      
            break;
        }
    }
}

int main() {

    sigset_t set;
    sigemptyset(&set);
    sigaddset(&set, SIGCHLD);
    sigprocmask(SIG_BLOCK, &set, NULL);

    pid_t pid;
    for (int i = 0; i < 20; ++i) {
   
        pid = fork();
        if (pid == 0) {
       
            break;
        }
    }

    if (pid > 0) {
   
        struct sigaction act;
        act.sa_flags = 0;
        act.sa_handler = myFun;
        sigemptyset(&act.sa_mask);
        sigaction(SIGCHLD, &act, NULL);

        sigprocmask(SIG_UNBLOCK, &set, NULL);

        while (1) {
       
            printf("parent process pid : %d\n", getpid());
            sleep(2);
        }
    } else if (pid == 0) {
   
        printf("child process pid : %d\n", getpid());
    }

    return 0;
}
