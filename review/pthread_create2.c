/* ************************************************************************
> File Name:     pthread_create2.c
> Author:        程序员Eric
> 微信公众号:    源水本木
> Created Time:  Fri 31 Mar 2023 09:13:03 AM CST
> Description:   
 ************************************************************************/
#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>

void * callback(void * arg) {

    printf("child thread...\n");
    printf("arg value : %d\n", *(int *)arg);
    return NULL;
}

int main() {

    pthread_t tid;

    int num = 10;

    int ret = pthread_create(&tid, NULL, callback, (void *)&num);

    if (ret != 0) {
   
        char * errstr = strerror(ret);
        printf("error : %s\n", errstr);

    }

    for (int i = 0; i < 5; i++) {
   
        printf("%d\n", i);
    }

    sleep(1);

    return 0;
}
