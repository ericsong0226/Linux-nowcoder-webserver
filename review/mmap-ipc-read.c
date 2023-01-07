/* ************************************************************************
> File Name:     mmap-ipc-read.c
> Author:        程序员Eric
> 微信公众号:    源水本木
> Created Time:  Fri 06 Jan 2023 09:33:56 AM CST
> Description:   
 ************************************************************************/
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int main() {

    int fd = open("test1.txt", O_RDWR);
    int size = lseek(fd, 0, SEEK_END);

    void *ptr = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (ptr == MAP_FAILED) {
   
        perror("mmap");
        exit(0);
    }

    char buf[7];
    strcpy(buf, (char *)ptr);
    printf("read data : %s\n", buf);

    munmap(ptr, size);
    
    return 0;
}
