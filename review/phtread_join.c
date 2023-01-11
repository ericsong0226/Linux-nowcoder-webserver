/* ************************************************************************
> File Name:     phtread_join.c
> Author:        程序员Eric
> 微信公众号:    源水本木
> Created Time:  Wed 11 Jan 2023 09:14:53 AM CST
> Description:   
 ************************************************************************/
#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>

int value = 10;

void * callback(void * arg) {
    
    printf("child thread id : %ld\n", pthread_self());
    pthread_exit((void *)&value);
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

    int * thread_retval;
    ret = pthread_join(tid, (void **)&thread_retval);
    if (ret != 0) {
        char * errstr = strerror(ret); 
        printf("error : %s\n", errstr);
    }

    printf("exit data : %d\n", *thread_retval);

    printf("huishou son pthread success!");

    pthread_exit(NULL);

    return 0;
}
