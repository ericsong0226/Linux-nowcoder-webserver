/* ************************************************************************
> File Name:     mmap-parent-child-ipc.c
> Author:        程序员Eric
> 微信公众号:    源水本木
> Created Time:  Fri 06 Jan 2023 09:05:32 AM CST
> Description:   
 ************************************************************************/
#include <stdio.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <wait.h>
#include <stdlib.h>

int main() {

    int fd = open("test.txt", O_RDWR);
    int size = lseek(fd, 0, SEEK_END);

    void *ptr = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (ptr == MAP_FAILED) {
   
        perror("mmap");
        exit(0);
    }
        pid_t pid = fork();
        if (pid > 0) {
           
            wait(NULL);
            char buf[64];
            strcpy(buf, (char *)ptr);
            printf("read data : %s\n", buf);
        } else if (pid == 0) {
       
            strcpy((char *)ptr, "ni hao a son!!!");
        }
   
        munmap(ptr, size);

        return 0;
}
