/* ************************************************************************
> File Name:     udp_server.c
> Author:        程序员Eric
> 微信公众号:    源水本木
> Created Time:  Sun 19 Mar 2023 08:52:11 PM CST
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

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(9999);
    addr.sin_addr.s_addr = INADDR_ANY;

    int ret = bind(fd, (struct sockaddr *)&addr, sizeof(addr));
    if (ret == -1) {
   
        perror("bind");
        exit(-1);
    }

    while (1) {
   
        char recvbuf[128];
        char ipbuf[16];

        struct sockaddr_in cliaddr;
        int len = sizeof(cliaddr);

        int num = recvfrom(fd, recvbuf, sizeof(recvbuf), 0, (struct sockaddr *)&cliaddr, &len);
        if (num == -1) {
       
            perror("recvfrom");
            exit(-1);
        }

        printf("client IP : %s, Port : %d\n",
                inet_ntop(AF_INET, &cliaddr.sin_addr.s_addr, ipbuf, sizeof(ipbuf)),
                ntohs(cliaddr.sin_port));

        printf("client say : %s\n", recvbuf);

        sendto(fd, recvbuf, strlen(recvbuf) + 1, 0, (struct sockaddr *)&cliaddr, sizeof(cliaddr));

        close(fd);

        return 0;
    }
}
