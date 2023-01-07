/* ************************************************************************
> File Name:     orphan.c
> Author:        程序员Eric
> 微信公众号:    源水本木
> Created Time:  Sun 01 Jan 2023 06:07:10 PM CST
> Description:   
 ************************************************************************/
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main() {
    
    pid_t pid = fork();

    if (pid > 0) {
         
        printf("i am parent process, pid : %d, ppid : %d\n", getpid(), getppid()); 
    } else if (pid == 0) {
        sleep(1); 
        printf("i am child process, pid : %d, ppid : %d\n", getpid(), getppid());
    }

    for (int i = 0; i < 3; i++) {
        printf("i : %d, pid : %d\n", i, getpid());
    }

    return 0;
}
