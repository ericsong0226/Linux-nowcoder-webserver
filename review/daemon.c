/* ************************************************************************
> File Name:     daemon.c
> Author:        程序员Eric
> 微信公众号:    源水本木
> Created Time:  Sun 08 Jan 2023 05:34:24 PM CST
> Description:   
 ************************************************************************/
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/time.h>
#include <signal.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

void work(int num) {
    
    time_t tm = time(NULL);
    struct tm * loc = localtime(&tm);
    
    char * str = asctime(loc);
    int fd = open("time.txt", O_RDWR | O_CREAT | O_APPEND, 0664);
    write(fd, str, strlen(str));
    close(fd);
}

int main() {

    pid_t pid = fork();

    if (pid > 0) {
        exit(0); 
    }

    setsid();

    umask(022);

    chdir("/home/song/linux/review/");
        
    int fd = open("/dev/null", O_RDWR);
    dup2(fd, STDIN_FILENO);
    dup2(fd, STDOUT_FILENO);
    dup2(fd, STDERR_FILENO);

    struct sigaction act;
    act.sa_flags = 0;
    act.sa_handler = work;
    sigemptyset(&act.sa_mask);
    sigaction(SIGALRM, &act, NULL);

    struct itimerval val;
    val.it_value.tv_sec = 2;
    val.it_value.tv_usec = 0;
    val.it_interval.tv_sec = 2;
    val.it_interval.tv_usec = 0;

    setitimer(ITIMER_REAL, &val, NULL);

    while (1) {
        sleep(10); 
    }

    return 0;
}
