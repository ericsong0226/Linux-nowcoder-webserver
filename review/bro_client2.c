/* ************************************************************************
> File Name:     bro_client2.c
> Author:        程序员Eric
> 微信公众号:    源水本木
> Created Time:  Sat 25 Mar 2023 09:19:01 PM CST
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
   
        char buf[128];
        int num = recvfrom(fd, buf, sizeof(buf), 0, NULL, NULL);
        printf("server say : %s\n", buf);
    }

    close(fd);

    return 0;
}
