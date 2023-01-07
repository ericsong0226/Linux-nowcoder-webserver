/* ************************************************************************
> File Name:     mkfifo.c
> Author:        程序员Eric
> 微信公众号:    源水本木
> Created Time:  Mon 02 Jan 2023 08:09:05 PM CST
> Description:   
 ************************************************************************/
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    
    int ret = access("fifo1", F_OK);
    if (ret == -1) {
   
        printf("create fifo1\n");

        ret = mkfifo("fifo1", 0664);
        if (ret == -1) {
            perror("mkfifo"); 
            exit(0);
        }
    }

    return 0;
}
