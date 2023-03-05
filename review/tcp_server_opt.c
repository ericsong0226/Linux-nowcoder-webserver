/* ************************************************************************
> File Name:     tcp_server_opt.c
> Author:        程序员Eric
> 微信公众号:    源水本木
> Created Time:  Sun 05 Mar 2023 03:41:28 PM CST
> Description:   
 ************************************************************************/
#include <stdio.h>
#include <ctype.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {

    int lfd = socket(PF_INET, SOCK_STREAM, 0);
    if (lfd == -1) {
   
        perror("socket");
        return -1;
    }

    struct sockaddr_in saddr;
    saddr.sin_family = AF_INET;
    saddr.sin_addr.s_addr = INADDR_ANY;
    saddr.sin_port = htons(9999);

    int optval = 1;
    setsockopt(lfd, SOL_SOCKET, SO_REUSEPORT, &optval, sizeof(optval));

    int ret = bind(lfd, (struct sockaddr *)&saddr, sizeof(saddr));
    if (ret == -1) {
   
        perror("bind");
        return -1;
    }

    ret = listen(lfd, 8);
    if (ret == -1) {
   
        perror("listen");
        return -1;
    }

    struct sockaddr_in cliaddr;
    socklen_t len = sizeof(cliaddr);
    int cfd = accept(lfd, (struct sockaddr *)&cliaddr, &len);
    if (cfd == -1) {
   
        perror("accept");
        return -1;
    }

    char cliIp[16];
    inet_ntop(AF_INET, &cliaddr.sin_addr.s_addr, cliIp, sizeof(cliIp));
    unsigned short cliPort = ntohs(cliaddr.sin_port);

    printf("client's ip is %s, and port is %d\n", cliIp, cliPort);

    char recvBuf[1024] = {0};
    while(1) {
   
        int len = recv(cfd, recvBuf, sizeof(recvBuf), 0);
        if (len == -1) {
       
            perror("recv");
            return -1;
        } else if (len == 0) {
       
            printf("client is closed...\n");
            break;
        } else if (len > 0) {
       
            printf("read buf = %s\n", recvBuf);
        }

        for (int i = 0; i < len; ++i) {
       
            recvBuf[i] = toupper(recvBuf[i]);
        }

        printf("after buf = %s\n", recvBuf);

        ret = send(cfd, recvBuf, strlen(recvBuf) + 1, 0);
        if (ret == -1) {
       
            perror("send");
            return -1;
        }
    }

    close(cfd);
    close(lfd);

    return 0;
}
