/* ************************************************************************
> File Name:     ipc_client2.c
> Author:        程序员Eric
> 微信公众号:    源水本木
> Created Time:  Thu 30 Mar 2023 08:52:31 PM CST
> Description:   
 ************************************************************************/
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/un.h>

int main() {

    unlink("client.sock");

    int cfd = socket(AF_LOCAL, SOCK_STREAM, 0);
    if (cfd == -1) {
   
        perror("socket");
        exit(-1);
    }

    struct sockaddr_un addr;
    addr.sun_family = AF_LOCAL;
    strcpy(addr.sun_path, "client.sock");
    int ret = bind(cfd, (struct sockaddr *)&addr, sizeof(addr));
    if (ret == -1) {
   
        perror("bind");
        exit(-1);
    }

    struct sockaddr_un seraddr;
    seraddr.sun_family = AF_LOCAL;
    strcpy(seraddr.sun_path, "server.sock");
    ret = connect(cfd, (struct sockaddr *)&seraddr, sizeof(seraddr));
    if (ret == -1) {
   
        perror("connect");
        exit(-1);
    }

    int num = 0;
    while (1) {
   
        char buf[128];
        sprintf(buf, "hello, i am client %d\n", num++);
        send(cfd, buf, strlen(buf) + 1, 0);
        printf("client say : %s\n", buf);

        int len = recv(cfd, buf, sizeof(buf), 0);

        if (len == -1) {
       
            perror("recv");
            exit(-1);
        } else if (len == 0) {
       
            printf("server closed...");
            break;
        } else if (len > 0) {
       
            printf("server say : %s\n", buf);
        }

        sleep(1);
    }

    close(cfd);

    return 0;
}

