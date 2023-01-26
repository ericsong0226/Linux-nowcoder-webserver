/* ************************************************************************
> File Name:     bro_server.c
> Author:        程序员Eric
> 微信公众号:    源水本木
> Created Time:  Thu 26 Jan 2023 03:45:08 PM CST
> Description:   
 ************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {

    int fd = socket(PF_INET, SOCK_DGRAM, 0);

    if (fd == -1) {
   
        perror("socket");
        exit(-1);
    }

    int op = 1;
    setsockopt(fd, SOL_SOCKET, SO_BROADCAST, &op, sizeof(op));

    struct sockaddr_in cliaddr;
    cliaddr.sin_family = AF_INET;
    cliaddr.sin_port = htons(9999);
    inet_pton(AF_INET, "192.168.179.130", &cliaddr.sin_addr.s_addr);

    int num = 0;
    while (1) {
   
        char sendBuf[128];

        sprintf(sendBuf, "hello, client...%d\n", num++);
        sendto(fd, sendBuf, strlen(sendBuf) + 1, 0, (struct sockaddr *)&cliaddr, sizeof(cliaddr));
        printf("broadcast data : %s\n", sendBuf);
        sleep(1);
    }

    close(fd);

    return 0;
}
