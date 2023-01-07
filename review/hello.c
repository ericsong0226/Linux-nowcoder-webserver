/* ************************************************************************
> File Name:     hello.c
> Author:        程序员Eric
> 微信公众号:    源水本木
> Created Time:  Sun 01 Jan 2023 05:21:17 PM CST
> Description:   
 ************************************************************************/
#include <stdio.h>
#include <unistd.h>

int main() {
    
    printf("begin\n");

    if (fork() > 0) {
        printf("i am parent : pid = %d, ppid = %d\n", getpid(), getppid()); 

        int i;
        for (i = 0; i < 10; i++) {
            printf("i = %d\n", i); 
            sleep(1);
        }
    } else {
        
        printf("i am child : pid = %d, ppid = %d\n", getpid(), getppid()); 

        int j;
        for (j = 0; j < 10; j++) {
            printf("j = %d\n", j); 
            sleep(1);
        }
    }

    return 0;
}
