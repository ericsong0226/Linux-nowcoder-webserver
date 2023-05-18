/* ************************************************************************
> File Name:     http_conn.cpp
> Author:        程序员Eric
> 微信公众号:    源水本木
> Created Time:  Thu 13 Apr 2023 09:09:56 AM CST
> Description:   
 ************************************************************************/
#include "http_conn.h"

const char* ok_200_title = "OK";
const char* error_400_title = "Bad Request";
const char* error_400_form = "Your request has bad syntax or is inherently impossible to satisfy.\n";
const char* error_403_title = "Forbidden";
const char* error_403_form = "You do not have permission to get file from this server.\n";
const char* error_404_title = "Not Found";
const char* error_404_form = "The requested file was not found on this server.\n";
const char* error_500_title = "Internal Error";
const char* error_500_form = "There was an unusual problem serving the requested file.\n";

const char* doc_root = "/home/song/linux/webserver/resources/";

int setnonblocking(int fd) {
    int old_flag = fcntl(fd, F_GETFL);
    int new_flag = old_flag | O_NONBLOCK;
    fcntl(fd, F_SETFL, new_flag);
    return old_flag;
}

void addfd(int epollfd, int fd, bool one_shot) {
    epoll_event event;
    event.data.fd = fd;
    event.events = EPOLLIN | EPOLLRDHUP;

    if (one_shot) {
        event.events |= EPOLLONESHOT;
    }
    epoll_ctl(epollfd, EPOLL_CTL_ADD, fd, &event);

    setnonblocking(fd);
}

void removefd(int epollfd, int fd) {
    epoll_ctl(epollfd, EPOLL_CTL_ADD, fd, 0);
    close(fd);
}

void modfd(int epollfd, int fd, int ev) {
    epoll_event event;
    event.data.fd = fd;
    event.events = ev | EPOLLET | EPOLLONESHOT | EPOLLRDHUP;
    epoll_ctl(epollfd, EPOLL_CTL_MOD, fd, &event);
}

int http_conn::m_user_count = 0;

int http_conn::m_epollfd = 1;

void http_conn::close_conn() {
    if (m_sockfd != -1) {
        removefd(m_epollfd, m_sockfd);
        m_sockfd = -1;
        m_user_count--;
    }
}

void http_conn::init(int sockfd, const sockaddr_in &addr) {
    m_sockfd = sockfd;
    m_address = addr;

    int reuse = 1;
    setsockopt(m_sockfd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));

    addfd(m_epollfd, sockfd, true);
    m_user_count++;

    init();
}

void http_conn::init() {
    m_check_state = CHECK_STATE_REQUESTLINE;
    m_linger = false;

    m_method = GET;
    m_url = 0;
    m_version = 0;
    m_content_length = 0;
    m_host = 0;
    m_start_line = 0;
    m_checked_idx = 0;
    m_read_idx = 0;
    m_write_idx = 0;
    bzero(m_read_buf, READ_BUFFER_SIZE);
    bzero(m_write_buf, READ_BUFFER_SIZE);
    bzero(m_read_file, FILENAME_LEN);
}

bool http_conn::read() {
//    printf("read data\n");

    if (m_read_idx >= READ_BUFFER_SIZE) {
        return false;
    }

    int bytes_read = 0;
    while (true) {
        bytes_read = recv(m_sockfd, m_read_buf + m_read_idx, READ_BUFFER_SIZE - m_read_idx, 0);
        if (bytes_read == -1) {
            if (errno == EAGAIN || errno == EWOULDBLOCK) {
                break;
            }
            return false;
        } else if (bytes_read == 0) {
            return false;
        }
        m_read_idx += bytes_read;
    }
    
    return true;
}

http_conn::LINE_STATUS http_conn::parse_line() {

    return LINE_OPEN;
}

http_conn::HTTP_CODE http_conn::parse_request_line(char * text) {
    return NO_REQUEST;
}

http_conn::HTTP_CODE http_conn::parse_headers(char * text) {
    return NO_REQUEST;
}

http_conn::HTTP_CODE http_conn::process_read() {
    return NO_REQUEST;
}

http_conn::HTTP_CODE http_conn::do_request() {
    return FILE_REQUEST;
}

bool http_conn::write() {
    printf("write data\n");

    return true;
}

void http_conn::process() {
//    printf("parse request, create response\n");
    HTTP_CODE read_ret = process_read();
    if (read_ret = NO_REQUEST) {
        modfd(m_epollfd, m_sockfd, EPOLLIN);
        return;
    }
}
