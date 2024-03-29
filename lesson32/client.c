// TCP 通信的客户端
#include <stdio.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main() {

    // 1.创建套接字
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd == -1) {
        perror("socket");
        exit(-1);
    }

    // 2.连接服务器端
    struct sockaddr_in serveraddr;
    serveraddr.sin_family = AF_INET;
    inet_pton(AF_INET, "192.168.179.130", &serveraddr.sin_addr.s_addr);
    serveraddr.sin_port = htons(9999);
    int ret = connect(fd, (struct sockaddr *)&serveraddr, sizeof(serveraddr));

    if (ret == -1) {
        perror("connect");
        exit(-1);
    }

    char recvBuf[1024] = {0};
    // 3.通信
    while (1) {
        char * data = "hello, i am client";
        // 给服务器端发送数据
        write(fd, data, strlen(data));

        sleep(1);

        memset(recvBuf, 0, 1024);
        int len = read(fd, recvBuf, sizeof(recvBuf));
        if (len == -1) {
            perror("read");
            exit(-1);
        } else if (len > 0) {
            printf("recv server data :%s\n", recvBuf);
        } else if (len == 0) {
            // 表示服务器端断开连接
            printf("server closed...\n");
            break;
        }
    }

    // 关闭连接
    close(fd);

    return 0;
}