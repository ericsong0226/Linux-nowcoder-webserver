/* ************************************************************************
> File Name:     multi_client.c
> Author:        程序员Eric
> 微信公众号:    源水本木
> Created Time:  Sun 26 Mar 2023 03:43:51 PM CST
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

    struct in_addr in;
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(9999);
    addr.sin_addr.s_addr = INADDR_ANY;

    int ret = bind(fd, (struct sockaddr *)&addr, sizeof(addr));
    if (ret == -1) {
   
        perror("bind");
        exit(-1);
    }

    struct ip_mreq op;
    inet_pton(AF_INET, "239.0.0.10", &op.imr_multiaddr.s_addr);
    op.imr_interface.s_addr = INADDR_ANY;

    setsockopt(fd, IPPROTO_IP, IP_ADD_MEMBERSHIP, &op, sizeof(op));

    while (1) {
   
        char buf[128];
        int num = recvfrom(fd, buf, sizeof(buf), 0, NULL, NULL);
        printf("server say : %s\n", buf);
    }

    close(fd);

    return 0;
}
