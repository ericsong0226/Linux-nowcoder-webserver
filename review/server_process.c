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

}
