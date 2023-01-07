/* ************************************************************************
> File Name:     pipe.c
> Author:        程序员Eric
> 微信公众号:    源水本木
> Created Time:  Mon 02 Jan 2023 04:46:53 PM CST
> Description:   
 ************************************************************************/
#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    
    int pipefd[2];

    int ret = pipe(pipefd);
    if (ret == -1) {
        perror("pipe"); 
        exit(0);
    }

    pid_t pid = fork();
    if (pid > 0) {
        printf("i am parent process, pid : %d\n", getpid()); 

        close(pipefd[1]);

        char buf[1024] = {0};
        while (1) {
            int len = read(pipefd[0], buf, sizeof(buf)); 
            printf("parent recv : %s, pid : %d\n", buf, getpid());
        }
    } else if (pid == 0) {
        printf("i am child process, pid : %d\n", getpid());

        close(pipefd[0]);

        char buf[1024] = {0};
        while (1) {
            char * str = "hello, i am child"; 
            write(pipefd[1], str, strlen(str));
        }
    }

    return 0;
}
