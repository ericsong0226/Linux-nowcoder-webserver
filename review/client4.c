/* ************************************************************************
> File Name:     client4.c
> Author:        程序员Eric
> 微信公众号:    源水本木
> Created Time:  Thu 16 Feb 2023 09:26:29 PM CST
> Description:   
 ************************************************************************/
#include <stdio.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main() {

    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd == -1) {
   
        perror("socket");
        exit(-1);
    }

    struct sockaddr_in serveraddr;
    serveraddr.sin_family = AF_INET;
    inet_pton(AF_INET, "192.168.179.130", &serveraddr.sin_addr.s_addr);
    serveraddr.sin_port = htons(9999);
    int ret = connect(fd, (struct sockaddr *)&serveraddr, sizeof(serveraddr));

    if (ret == -1) {
   
        perror("connect");
        exit(-1);
    }

    char recvBuf[1024] = {0};
    while(1) {
   
        char * data = "hello, i am client";
        write(fd, data, strlen(data));

        sleep(1);

        memset(recvBuf, 0, 1024);
        int len = read(fd, recvBuf, sizeof(recvBuf));
        if (len == -1) {
       
            perror("read");
            exit(-1);
        } else if (len > 0) {
       
            printf("recv server data : %s\n", recvBuf);
        } else if (len == 0) {
       
            printf("server closed...\n");
            break;
        }
    }

    close(fd);

    return 0;
}
