/* ************************************************************************
> File Name:     multichatA.c
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

    int ret = access("mfifo1", F_OK);
    if (ret == -1) {
   
        printf("create mfifo1\n");
        ret = mkfifo("mfifo1", 0664);
        if (ret == -1) {
            perror("mkfifo");
            exit(0);
        }
    }

    ret = access("mfifo2", F_OK);
    if (ret == -1) {
   
        printf("create mfifo2\n");
        ret = mkfifo("mfifo2", 0664);
        if (ret == -1) {
            perror("mkfifo"); 
            exit(0);
        }
    }

    int fdw = open("mfifo1", O_WRONLY);
    if (fdw == -1) {
        perror("open"); 
        exit(0);
    }
    printf("open mfifo1 success, writing...\n");

    int fdr = open("mfifo2", O_RDONLY);
    if (fdr == -1) {
        perror("open"); 
        exit(0);
    }
    printf("oepn mfifo2 success, reading...\n");

    char buf[128];

    pid_t pid = fork();
    if (pid > 0) {
        char bufw[128]; 
        while (1) {
            memset(bufw, 0, 128); 
            fgets(bufw, 128, stdin);
            int ret2 = write(fdw, bufw, strlen(bufw));
            if (ret2 == -1) {
                perror("write"); 
                exit(0);
            }
        }

        close(fdw);
    } else if (pid == 0) {
   
        char bufr[128];
        while (1) {
       
            memset(bufr, 0, 128);
            int ret3 = read(fdr, bufr, 128);
            if (ret3 <= 0) {
           
                perror("read");
                break;
            }
            printf("buf : %s\n", bufr);
        }

        close(fdr);
    }
    
    return 0;
}
