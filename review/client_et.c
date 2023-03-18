/* ************************************************************************
> File Name:     client_et.c
> Author:        程序员Eric
> 微信公众号:    源水本木
> Created Time:  Thu 16 Mar 2023 09:25:07 AM CST
> Description:   
 ************************************************************************/
#include <stdio.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main() {

    int fd = socket(PF_INET, SOCK_STREAM, 0);
    if (fd == -1) {
   
        perror("socket");
        return -1;
    }

    struct sockaddr_in seraddr;
    inet_pton(AF_INET, "127.0.0.1", &seraddr.sin_addr.s_addr);
    seraddr.sin_family = AF_INET;
    seraddr.sin_port = htons(9999);

    int ret = connect(fd, (struct sockaddr *)&seraddr, sizeof(seraddr));
    
    return 0;
}
