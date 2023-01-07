/* ************************************************************************
> File Name:     charA.c
> Author:        程序员Eric
> 微信公众号:    源水本木
> Created Time:  Wed 04 Jan 2023 08:47:18 AM CST
> Description:   
 ************************************************************************/
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>

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

    ret = access("fifo2", F_OK);
    if (ret == -1) {
   
        printf("create fifo2\n");
        ret = mkfifo("fifo2", 0664);
        if (ret == -1) {
            perror("mkfifo"); 
            exit(0);
        }
    }

    int fdw = open("fifo1", O_WRONLY);
    if (fdw == -1) {
        perror("open"); 
        exit(0);
    }
    printf("open fifo1 success, writing...\n");

    int fdr = open("fifo2", O_RDONLY);
    if (fdr == -1) {
        perror("open"); 
        exit(0);
    }
    printf("oepn fifo2 success, reading...\n");

    char buf[128];
    while (1) {
   
        memset(buf, 0, 128);
        fgets(buf, 128, stdin);
        ret = write(fdw, buf, strlen(buf));
        if (ret == -1) {
            perror("write"); 
            exit(0);
        }

        memset(buf, 0, 128);
        ret = read(fdr, buf, 128);
        if (ret <= 0) {
            perror("read"); 
            break;
        }
        printf("buf : %s\n", buf);
    }

    close(fdr);
    close(fdw);

    return 0;
}
