/* ************************************************************************
> File Name:     mmap-ipc-write.c
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

    strcpy((char *)ptr, "123456");

    return 0;
}
