/* ************************************************************************
> File Name:     parent-child-ipc.c
> Author:        程序员Eric
> 微信公众号:    源水本木
> Created Time:  Mon 02 Jan 2023 06:00:45 PM CST
> Description:   
 ************************************************************************/
#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wait.h>

int main() {

    int fd[2];
    int ret = pipe(fd);

    if (ret == -1) {
        perror("pipe"); 
        exit(0);
    }

    pid_t pid = fork();
    if (pid > 0) {

        close(fd[1]);

        char buf[1024] = {0};

        int len = -1;
        while ((len = read(fd[0], buf, sizeof(buf) - 1)) > 0) {
            
            printf("%s", buf);
            memset(buf, 0, 1024);
        }

        wait(NULL);
    } else if (pid == 0) {
    
        close(fd[0]);

        dup2(fd[1], STDOUT_FILENO);

        execlp("ps", "ps", "aux", NULL);
        perror("execlp");
        exit(0);
    } else {
    
        perror("fork");
        exit(0);
    }

    return 0;
}
