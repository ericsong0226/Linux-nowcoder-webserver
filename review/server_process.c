/* ************************************************************************
> File Name:     server_process.c
> Author:        程序员Eric
> 微信公众号:    源水本木
> Created Time:  Sun 26 Feb 2023 09:41:04 PM CST
> Description:   
 ************************************************************************/
#include <stdio.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <wait.h>
#include <errno.h>

void recyleChild(int arg) {

    while (1) {
   
        int ret = waitpid(-1, NULL, WHOHANG);
        if (ret == -1) {
       
            break;
        } else if (ret == 0) {
       
            break;
        } else if (ret > 0) {
       
            printf("child %d be recyle", ret);
        }
    }
}

int main() {

    struct sigaction act;
    act.sa_flags = 0;
    sigemptyset(&act.sa_mask);
    act.sa_handler = recyleChild;
    sigaction(SIGCHILD, &act, NULL);

    int lfd = socket(AF_INET, SOCK_STREAM, 0);
    if (lfd == -1) {
   
        perror("socket");
        exit(-1);
    }

    struct sockaddr_in saddr;
    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(9999);
    saddr.sin_addr.s_addr = INADDR_ANY;

    int ret = bind(lfd, (struct sockaddr *)&saddr, sizeof(saddr));
    if (ret == -1) {
   
        perror("bind");
        exit(-1);
    }

    ret = listen(lfd, 128);
    if (ret == -1) {
   
        perror("listen");
        exit(-1);
    }

    while (1) {
   
        struct sockaddr_in cliaddr;
        int len = sizeof(cliaddr);

        int cfd = accept(lfd, (struct sockaddr *)&cliaddr, sizeof(cliaddr));
        if (cfd == -1) {
       
            if (errno == EINTR) {
           
                continue;
            }

            perror("accept");
            exit(-1);
        }

        pid_t pid = fork();
        if (pid == 0) {
       
            char cliIp[16];
            inet_ntop(AF_INET, &cliaddr.sin_addr.s_addr,cliIp, sizeof(cliIp));
            unsigned short cliPort = ntohs(cliaddr.sin_port);
            printf("client ip is %s, port is %d\n", cliIp, cliPort);

            char recvBuf[1024];
            while (1) {
           
                int len = read(cfd, &recvBuf, sizeof(recvBuf));

                if (len == -1) {
               
                    perror("read");
                    exit(-1);
                } else if (len > 0) {
               
                    printf("recv client : %s\n", recvBuf);
                } else if (len == 0) {
               
                    printf("client closed...\n");
                    break;
                }

                write(cfd, recvBuf, strlen(recvBuf));
            }

            close(cfd);
            exit(0);
        }
    }

    close(lfd);

    return 0;
}
