/* ************************************************************************
> File Name:     mmap-anon.c
> Author:        程序员Eric
> 微信公众号:    源水本木
> Created Time:  Sat 07 Jan 2023 11:56:36 AM CST
> Description:   
 ************************************************************************/
#include <stdio.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>

int main() {

    int len = 4096;
    void * ptr = mmap(NULL, len, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    if (ptr == MAP_FAILED) {
   
        perror("mmap");
        exit(0);
    }

    pid_t pid = fork();

    if (pid > 0) {
    
        strcpy((char *)ptr, "hello world!");
        wait(NULL);
    } else if (pid == 0) {
   
        sleep(1);
        printf("%s\n", (char *)ptr);
    }

    int ret = munmap(ptr, len);

    if (ret == -1) {
    
        perror("munmap");
        exit(0);
    }

    return 0;
}
