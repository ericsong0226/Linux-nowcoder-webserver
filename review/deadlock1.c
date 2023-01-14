/* ************************************************************************
> File Name:     deadlock1.c
> Author:        程序员Eric
> 微信公众号:    源水本木
> Created Time:  Sat 14 Jan 2023 10:05:33 PM CST
> Description:   
 ************************************************************************/
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t mutex1, mutex2;

void * workA(void * arg) {

    pthread_mutex_lock(&mutex1);
    sleep(1);
    pthread_mutex_lock(&mutex2);

    printf("workA...\n");

    pthread_mutex_unlock(&mutex2);
    pthread_mutex_unlock(&mutex1);

    return NULL;
}

void * workB(void * arg) {

    pthread_mutex_lock(&mutex2);
    sleep(1);
    pthread_mutex_lock(&mutex1);

    printf("workB...\n");

    pthread_mutex_unlock(&mutex1);
    pthread_mutex_unlock(&mutex2);

    return NULL;
}

int main() {

    pthread_mutex_init(&mutex1, NULL);
    pthread_mutex_init(&mutex2, NULL);


    pthread_t tid1, tid2;
    pthread_create(&tid1, NULL, workA, NULL);
    pthread_create(&tid1, NULL, workB, NULL);

    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);

    pthread_mutex_destroy(&mutex1);
    pthread_mutex_destroy(&mutex2);
    
    return 0; 
}
