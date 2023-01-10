/* ************************************************************************
> File Name:     pthread_exit.c
> Author:        程序员Eric
> 微信公众号:    源水本木
> Created Time:  Tue 10 Jan 2023 09:16:29 AM CST
> Description:   
 ************************************************************************/
#include <stdio.h>
#include <pthread.h>
#include <string.h>

void * callback(void * arg) {
    printf("child thread id : %ld\n", pthread_self());
    return NULL;
}

int main() {

    pthread_t tid;
    int ret = pthread_create(&tid, NULL, callback, NULL);
    if (ret != 0) {
        char * errstr = strerror(ret); 
        printf("error : %s\n", errstr);
    }

    for (int i = 0; i < 5; i++) {
        printf("%d\n", i); 
    }

    printf("tid : %ld, main thread id : %ld\n", tid, pthread_self());

    pthread_exit(NULL);

    printf("main thread exit\n");

    return 0;
}
