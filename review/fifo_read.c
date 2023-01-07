/* ************************************************************************
> File Name:     fifo_read.c
> Author:        程序员Eric
> 微信公众号:    源水本木
> Created Time:  Mon 02 Jan 2023 08:27:37 PM CST
> Description:   
 ************************************************************************/
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main() {

    int fd = open("test", O_RDONLY);
    if (fd == -1) {
   
        perror("open");
        exit(0);
    }

    while (1) {
   
        char buf[1024] = {0};
        int len = read(fd, buf, sizeof(buf));
        if (len == 0) {
       
            printf("write closed...\n");
            break;
        }
        printf("recv buf : %s\n", buf);
    }

    close(fd);

    return 0;
}
