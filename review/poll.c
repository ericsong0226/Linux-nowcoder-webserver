/* ************************************************************************
> File Name:     poll.c
> Author:        程序员Eric
> 微信公众号:    源水本木
> Created Time:  Fri 10 Mar 2023 09:19:44 AM CST
> Description:   
 ************************************************************************/
#include <stdio.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/select.h>
#include <poll.h>

int main() {

    int lfd = socket(PF_INET, SOCK_STREAM, 0);
    struct sockaddr_in saddr;
    saddr.sin_port = htons(9999);
    saddr.sin_family = AF_INET;
    saddr.sin_addr.s_addr = INADDR_ANY;

    bind(lfd, (struct sockaddr *)&saddr, sizeof(saddr));

    listen(lfd, 8);

    struct pollfd fds[1024];
    for (int i = 0; i < 1024; ++i) {
   
        fds[i].fd = -1;
        fds[i].events = POLLIN;
    }
    fds[0].fd = lfd;

    int nfds = 0;

    while (1) {
   
        int ret = poll(fds, nfds + 1, -1);

        if (ret == -1) {
       
            perror("poll");
            exit(-1);
        } else if (ret == 0) {
       
            continue;
        } else if (ret > 0) {
       
            if (fds[0].revents & POLLIN) {
           
                struct sockaddr_in cliaddr;
                int len = sizeof(cliaddr);
                int cfd = accept(lfd, (struct sockaddr *)&cliaddr, &len);

                for (int i = 1; i < 1024; i++) {
               
                    if (fds[i].fd == -1) {
                   
                        fds[i].fd = cfd;
                        fds[i].events = POLLIN;
                        break;
                    }
                }

                nfds = nfds > cfd ? nfds : cfd;
            }

            for (int i = 1; i <= nfds; i++) {
           
                if (fds[i].revents & POLLIN) {
               
                    char buf[1024] = {0};
                    int len = read(fds[i].fd, buf, sizeof(buf));
                    if (len == -1) {
                   
                        perror("read");
                        exit(-1);
                    } else if (len == 0) {
                   
                        printf("client closed...\n");
                        close(fds[i].fd);
                        fds[i].fd = -1;
                    } else if (len > 0) {
                   
                        printf("read buf = %s\n", buf);
                        write(fds[i].fd, buf, strlen(buf) + 1);
                    }
                }
            }
        }
    }

    close(lfd);

    return 0;
}
