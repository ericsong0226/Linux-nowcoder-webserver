/* ************************************************************************
> File Name:     rwlock.c
> Author:        程序员Eric
> 微信公众号:    源水本木
> Created Time:  Sun 15 Jan 2023 10:35:52 AM CST
> Description:   
 ************************************************************************/
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

int num = 1;
pthread_rwlock_t rwlock;

void * writeNum(void * arg) {

    while(1) {
   
        pthread_rwlock_wrlock(&rwlock);
        num++;
        printf("++write, tid : %ld, num : %d\n", pthread_self(), num);
        pthread_rwlock_unlock(&rwlock);
        usleep(100);
    }

    return NULL;
}

void * readNum(void * arg) {

    while(1) {
   
        pthread_rwlock_rdlock(&rwlock);
        printf("==read, tid : %ld, num : %d\n", pthread_self(), num);
        pthread_rwlock_unlock(&rwlock);
        usleep(100);
    }

    return NULL;
}

int main() {

    pthread_rwlock_init(&rwlock, NULL);

    pthread_t wtids[3], rtids[5];
    for (int i = 0; i < 3; ++i) {
   
        pthread_create(&wtids[i], NULL, writeNum, NULL);
    }

    for (int i = 0; i < 5; ++i) {
   
        pthread_create(&rtids[i], NULL, readNum, NULL);
    }
    
    for (int i = 0; i < 3; ++i) {
  
        pthread_detach(wtids[i]);
    }

    for (int i = 0; i < 5; ++i) {
  
        pthread_detach(rtids[i]);
    }

    pthread_exit(NULL);

    pthread_rwlock_destroy(&rwlock);

    return 0;
}

