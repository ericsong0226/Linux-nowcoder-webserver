/* ************************************************************************
> File Name:     iptrans.c
> Author:        程序员Eric
> 微信公众号:    源水本木
> Created Time:  Sun 22 Jan 2023 10:07:18 AM CST
> Description:   
 ************************************************************************/
#include <arpa/inet.h>
#include <stdio.h>

int main() {

    char buf[] = "192.168.1.4";
    unsigned int num = 0;

    inet_pton(AF_INET, buf, &num);
    unsigned char * p = (unsigned char *)&num;
    printf("%d %d %d %d\n", *p, *(p + 1), *(p + 2), *(p + 3));

    char ip[16] = "";

    const char *str = inet_ntop(AF_INET, &num, ip, 16);
    printf("str : %s\n", str);
    printf("ip : %s\n", str);
    printf("%d\n", ip == str);

    return 0;
}
