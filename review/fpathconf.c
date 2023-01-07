/* ************************************************************************
> File Name:     fpathconf.c
> Author:        程序员Eric
> 微信公众号:    源水本木
> Created Time:  Mon 02 Jan 2023 04:57:20 PM CST
> Description:   
 ************************************************************************/
#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <string.h>

int main() {
    
    int pipefd[2];

    int ret = pipe(pipefd);

    long size = fpathconf(pipefd[0], _PC_PIPE_BUF);

    printf("pipe size : %ld\n", size);

    return 0;
}
