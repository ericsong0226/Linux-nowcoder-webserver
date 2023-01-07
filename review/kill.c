/* ************************************************************************
> File Name:     kill.c
> Author:        程序员Eric
> 微信公众号:    源水本木
> Created Time:  Sat 07 Jan 2023 03:47:42 PM CST
> Description:   
 ************************************************************************/
#include <stdio.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>

int main() {
    
    pid_t pid = fork();

    if (pid == 0) {
   
        int i = 0;
        for (int i = 0; i < 5; ++i) {
       
            printf("child process\n");
            sleep(1);
        }
    } else if (pid > 0) {
  
        printf("parent process\n");
        sleep(2);
        printf("kill child process now\n");
        kill(pid, SIGINT);
    }

    return 0;
}
