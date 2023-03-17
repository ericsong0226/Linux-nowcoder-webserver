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
    
    return 0;
}
