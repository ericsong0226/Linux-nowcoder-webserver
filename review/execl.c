/* ************************************************************************
> File Name:     execl.c
> Author:        程序员Eric
> 微信公众号:    源水本木
> Created Time:  Sun 01 Jan 2023 05:41:10 PM CST
> Description:   
 ************************************************************************/
#include <unistd.h>
#include <stdio.h>

int main() {
    pid_t pid = fork();
    
    if (pid > 0) {
        printf("i am parent process, pid : %d\n", getpid()); 
        sleep(1);
    } else if (pid == 0) {
        
        execl("/bin/ps", "ps", "aux", NULL);

        printf("i am child process, pid : %d\n", getpid());
    }

    for (int i = 0; i < 3; i++) {
        printf("i = %d, pid = %d\n", i, getpid()); 
    }

    return 0;
}
