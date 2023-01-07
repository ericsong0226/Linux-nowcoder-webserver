/* ************************************************************************
> File Name:     fifo_write.c
> Author:        程序员Eric
> 微信公众号:    源水本木
> Created Time:  Mon 02 Jan 2023 08:19:56 PM CST
> Description:   
 ************************************************************************/
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main() {

    int ret = access("test", F_OK);
    if (ret == -1) {
  
        printf("create test fifo\n");

        ret = mkfifo("test", 0664);

        if (ret == -1) {
       
            perror("mkfifo");
            exit(0);
        }
    }

    int fd = open("test", O_WRONLY);
    if (fd == -1) {
   
        perror("open");
        exit(0);
    }

    for (int i = 0; i < 100; ++i) {
   
        char buf[1024];
        sprintf(buf, "hello, %d\n", i);
        printf("write data : %s\n", buf);
        write(fd, buf, strlen(buf));
        sleep(1);
    }

    close(fd);

    return 0;
}
