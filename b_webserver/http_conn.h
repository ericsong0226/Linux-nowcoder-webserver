/* ************************************************************************
> File Name:     http_conn.h
> Author:        程序员Eric
> 微信公众号:    源水本木
> Created Time:  Thu 13 Apr 2023 09:13:11 AM CST
> Description:   
 ************************************************************************/
#ifndef HTTPCONNECTION_H
#define HTTPCONNECTION_H

#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/epoll.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <assert.h>
#include <sys/stat.h>
#include <string.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <stdarg.h>
#include <errno.h>
#include "locker.h"
#include <sys/uio.h>

class http_conn {
public:
    static int m_epollfd;
    static int m_user_count;
    static const int READ_BUFFER_SIZE = 2048;
    static const int WRITE_BUFFER_SIZE = 1024;

    http_conn() {}
    ~http_conn() {}

    void init(int sockfd, const sockaddr_in& addr);
    bool read();
    bool write();
    void process();
    void close_conn();

    
private:
    int m_sockfd;
    sockaddr_in m_address;

private:
    void init();

    char m_read_buf[READ_BUFFER_SIZE];
    int m_read_idx;
};


#endif
