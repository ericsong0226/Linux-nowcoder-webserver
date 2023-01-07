/* ************************************************************************
> File Name:     fork.c
> Author:        程序员Eric
> 微信公众号:    源水本木
> Created Time:  Sun 01 Jan 2023 05:00:03 PM CST
> Description:   
 ************************************************************************/
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main() {
    
    int num = 10;
    pid_t pid = fork();

    if (pid > 0) {
        printf("pid : %d\n", pid);
        printf("i am parent process, pid : %d, ppid : %d\n", getpid(), getppid());

        printf("parent num : %d\n", num);
        num += 10;
        printf("parent num += 10 : %d\n", num);
    } else if (pid == 0) {
        printf("i am child process, pid : %d, ppid : %d\n", getpid(), getppid());
         
        printf("child num : %d\n", num);
        num += 100;
        printf("child num += 100 : %d\n", num);
    }

    for (int i = 0; i < 3; i++) {
        printf("i : %d, pid : %d\n", i, getpid()); 
        sleep(1);
    }

    return 0;
}
