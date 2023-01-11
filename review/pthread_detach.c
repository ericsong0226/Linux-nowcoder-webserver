/* ************************************************************************
> File Name:     pthread_detach.c
> Author:        程序员Eric
> 微信公众号:    源水本木
> Created Time:  Wed 11 Jan 2023 09:40:09 AM CST
> Description:   
 ************************************************************************/
#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>

void * callback(void * arg) {

    printf("child thread id : %ld\n", pthread_self());
    return NULL;
}

int main() {

    pthread_t tid;

    int ret = pthread_create(&tid, NULL, callback, NULL);
    if (ret != 0) {
   
        char * errstr = strerror(ret);
        printf("error1 : %s\n", errstr);
    }

    printf("tid : %ld, main thread id : %ld\n", tid, pthread_self());

    ret = pthread_detach(tid);
    if (ret != 0) {
   
        char * errstr = strerror(ret);
        printf("error2 : %s\n", errstr);
    }

    /* ret = pthread_join(tid, NULL); */
    /* if (ret != 0) { */
   
        /* char * errstr = strerror(ret); */
        /* printf("error3 : %s\n", errstr); */
    /* } */

    pthread_exit(NULL);

    return 0;
}
