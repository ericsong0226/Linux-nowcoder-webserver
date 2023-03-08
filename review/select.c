/* ************************************************************************
> File Name:     select.c
> Author:        程序员Eric
> 微信公众号:    源水本木
> Created Time:  Wed 08 Mar 2023 09:13:46 AM CST
> Description:   
 ************************************************************************/
#include <stdio.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/select.h>

int main() {

    int lfd = socket(PF_INET, SOCK_STREAM, 0);
    struct sockaddr_in saddr;
    saddr.sin_port = htons(9999);
    saddr.sin_family = AF_INET;
    saddr.sin_addr.s_addr = INADDR_ANY;

    bind(lfd, (struct sockaddr *)&saddr, sizeof(saddr));

    listen(lfd, 8);

    fd_set rdset, tmp;
    FD_ZERO(&rdset);
    FD_SET(lfd, &rdset);
    int maxfd = lfd;

    while(1) {
   
        tmp = rdset;

        int ret = select(maxfd + 1, &tmp, NULL, NULL, NULL);
        if (ret == -1) {
       
            perror("select");
            exit(-1);
        } else if (ret == 0) {
       
            continue;
        } else if (ret > 0) {
       
            if (FD_ISSET(lfd, &tmp)) {
           
                struct sockaddr_in cliaddr;
                int len = sizeof(cliaddr);
                int cfd = accept(lfd, (struct sockaddr *)&cliaddr, &len);

                FD_SET(cfd, &rdset);

                maxfd = maxfd > cfd ? maxfd : cfd;
            }

            for (int i = lfd + 1; i <= maxfd; ++i) {
           
                if (FD_ISSET(i, &tmp)) {
               
                    char buf[1024] = {0};
                    int len = read(i, buf, sizeof(buf));
                    if (len == -1) {
                   
                        perror("read");
                        exit(-1);
                    } else if (len == 0) {
                   
                        printf("client closed...\n");
                        close(i);
                        FD_CLR(i, &rdset);
                    } else if (len > 0) {
                   
                        printf("read buf = %s\n", buf);
                        write(i, buf, strlen(buf) + 1);
                    }
                }
            }
        }
    }

    close(lfd);

    return 0;
}
