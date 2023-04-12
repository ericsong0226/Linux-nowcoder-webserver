/* ************************************************************************
> File Name:     main.cpp
> Author:        程序员Eric
> 微信公众号:    源水本木
> Created Time:  Sat 08 Apr 2023 08:53:06 PM CST
> Description:   
 ************************************************************************/
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/epoll.h>
#include "locker.h"
#include "threadpool.h"
#include "http_conn.h"

#define MAX_FD 65536
#define MAX_EVENT_NUMBER 10000

void addsig(int sig, void(handler)(int)) {
    struct sigaction sa;
    memset(&sa, '\0', sizeof(sa));
    sa.sa_handler = handler;
    sigfillset (&sa.sa_mask);
    assert(sigaction(sig, &sa, NULL) != -1);
}

int main(int argc, char* argv[]) {
    if (argc <= 1) {
        printf("usage : %s port_number\n", basename(argv[0]));
        return 1;
    }

    int port = atoi(argv[1]);
    addsig(SIGPIPE, SIG_IGN);

    threadpool<http_conn>* pool = NULL;
    try {
        pool = new threadpool<http_conn>;
    } catch(...) {
        return 1;
    }

    http_conn* users = new http_conn[MAX_FD];

    int listenfd = socket(PF_INET, SOCK_STREAM, 0);

    int ret = 0;
    struct sockaddr_in address;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_family = AF_INET;
    address.sin_port = htons(port);

    int reuse = 1;
    setsocket(listenfd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));
    ret = bind(listenfd, (struct sockaddr*)&address, sizeof(address));
    ret = listen(listenfd, 5);

    epoll_event events[MAX_EVENT_NUMBER];
    int epollfd = epoll_create(5);

    addfd(epollfd, listen, false);
    http_conn::m_epollfd = epollfd;

    while (true) {
        int number = epoll_wait(epollfd, events, MAX_EVENT_NUMBER, -1);

        if ((number < 0) && (errno != EINTR)) {
            printf("epoll failure\n");
            break;
        }
    }
}
