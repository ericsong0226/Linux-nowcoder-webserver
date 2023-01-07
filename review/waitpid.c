/* ************************************************************************
> File Name:     wait.c
> Author:        程序员Eric
> 微信公众号:    源水本木
> Created Time:  Mon 02 Jan 2023 12:33:22 PM CST
> Description:   
 ************************************************************************/
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() {

    pid_t pid;

    for (int i = 0; i < 5; ++i) {
        pid = fork(); 
        if (pid == 0) {
            break; 
        }
    }

    if (pid > 0) {
        while (1) {
            printf("parent, pid = %d\n", getpid()); 
            sleep(1);

            int st;
            int ret = waitpid(-1, &st, WNOHANG);
            if (ret == -1) {
                break; 
            } else if (ret == 0) {
                continue; 
            } else if (ret > 0) {
                if (WIFEXITED(st)) {
                     printf("退出的状态码：%d\n", WEXITSTATUS(st)); 
                }
                if (WIFSIGNALED(st)) {
                     printf("被哪个信号干掉了：%d\n", WTERMSIG(st)); 
                }

                printf("child die, pid = %d\n", ret);                
            }         
        }
     } else if (pid == 0) {
            while (1) {
                printf("child, pid = %d\n", getpid()); 
                sleep(1);
            } 

            exit(0);
        }

    return 0;
}
