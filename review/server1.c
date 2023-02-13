/* ************************************************************************
> File Name:     server1.c
> Author:        程序员Eric
> 微信公众号:    源水本木
> Created Time:  Tue 07 Feb 2023 09:44:32 PM CST
> Description:   
 ************************************************************************/
#include <stdio.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main() {

    int lfd = socket(AF_INET, SOCK_STREAM, 0);
    if (lfd == -1) {
   
        perror("socket");
        exit(-1);
    }

    struct sockaddr_in saddr;
    saddr.sin_family = AF_INET;
    saddr.sin_addr.s_addr = INADDR_ANY;
    saddr.sin_port = htons(9999);
    int ret = bind(lfd, (struct sockaddr *)&saddr, sizeof(saddr));

    if (ret == -1) {
   
        perror("bind");
        exit(-1);
    }

    ret = listen(lfd, 8);
    if (ret == -1) {
   
        perror("listen");
        exit(-1);
    }

    struct sockaddr_in clientaddr;
    int len = sizeof(clientaddr);
    int cfd = accept(lfd, (struct sockaddr *)&clientaddr, &len);

    if (cfd == -1) {
   
        perror("accept");
        exit(-1);
    }

    char clientIP[16];
    inet_ntop(AF_INET, &clientaddr.sin_addr, clientIP, sizeof(clientIP));
    unsigned short clientPort = ntohs(clientaddr.sin_port);
    printf("client ip is %s, port is %d\n", clientIP, clientPort);

    char recvBuf[1024] = {0};
    while (1) {
   
        memset(recvBuf, 0, 1024);
        int num = read(cfd, recvBuf, sizeof(recvBuf));
        if (num == -1) {
       
            perror("read");
            exit(-1);
        } else if (num > 0) {
       
            printf("recv client data : %s\n", recvBuf);
        } else if (num = 0) {
       
            printf("client closed...\n");
        }

        char data[1024];
        memset(data, 0, 1024);
        printf("please enter send data: \n");
        scanf("%s", data);

        write(cfd, data, strlen(data));
    }

    close(cfd);
    close(lfd);

    return 0;
}
