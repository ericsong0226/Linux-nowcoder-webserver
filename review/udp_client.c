/* ************************************************************************
> File Name:     udp_client.c
> Author:        程序员Eric
> 微信公众号:    源水本木
> Created Time:  Sun 19 Mar 2023 08:52:34 PM CST
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

    struct sockaddr_in saddr;
    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(9999);
    inet_pton(AF_INET, "127.0.0.1", &saddr.sin_addr.s_addr);

    int num = 0;
    while (1) {
   
        char sendBuf[128];
        sprintf(sendBuf, "hello, i am client %d\n", num++);
        sendto(fd, sendBuf, strlen(sendBuf) + 1, 0, (struct sockaddr *)&saddr, sizeof(saddr));
        int num = recvfrom(fd, sendBuf, sizeof(sendBuf), 0, NULL, NULL);
        if (num == -1) {
       
            perror("recvfrom");
            exit(-1);
        }

        printf("server say : %s\n", sendBuf);

        sleep(1);
    }

    close(fd);

    return 0;
}
