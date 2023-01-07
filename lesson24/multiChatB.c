#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>

int main() {

    // 1.判断有名管道文件是否存在
    int ret = access("fifo1", F_OK);
    if (ret == -1) {
        // 文件不存在
        printf("管道不存在，创建对应的有名管道\n");
        ret = mkfifo("fifo1", 0664);
        if (ret == -1) {
            perror("mkfifo");
            exit(0);
        }
    }

    ret = access("fifo2", F_OK);
    if (ret == -1) {
        // 文件不存在
        printf("管道不存在，创建对应的有名管道\n");
        ret = mkfifo("fifo2", 0664);
        if (ret == -1) {
            perror("mkfifo");
            exit(0);
        }
    }

    // 2.以只读的方式打开管道fifo1
    int fdr = open("fifo1", O_RDONLY);
    if (fdr == -1) {
        perror("open");
        exit(0);
    }
    printf("打开管道fifo1成功, 等待读取...\n");

    // 3.以只写的方式打开管道fifo2
    int fdw = open("fifo2", O_WRONLY);
    if (fdw == -1) {
        perror("open");
        exit(0);
    }
    printf("打开管道fifo2成功, 等待写入...\n");

    pid_t pid = fork();
    // 父进程，读fifo1
    if (pid > 0) {
        char bufr[128];
        while(1) {
            memset(bufr, 0, 128);
            int ret3 = read(fdr, bufr, 128);
            if (ret3 <= 0) {
                perror("read");
                break;
            }
            printf("buf: %s\n", bufr);
        }

        // 6.关闭文件描述符
        close(fdr);
    }
    // 子进程，写fifo2
    else if (pid == 0) {
        char bufw[128];
        while(1) {
            memset(bufw, 0, 128);
            // 获取标准输入数据
            fgets(bufw, 128, stdin);
            // 数据
            int ret2 = write(fdw, bufw, strlen(bufw));
            if (ret2 == -1) {
                perror("write");
                exit(0);
            }
        }
        
        close(fdw);
    }

    return 0;
}