/* ************************************************************************
> File Name:     mutex.c
> Author:        程序员Eric
> 微信公众号:    源水本木
> Created Time:  Thu 12 Jan 2023 09:22:54 PM CST
> Description:   
 ************************************************************************/
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

int tickets = 1000;

pthread_mutex_t mutex;

void * sellticket(void * arg) {

    while (1) {
   
        pthread_mutex_lock(&mutex);

        if (tickets > 0) {
       
            usleep(6000);
            printf("%ld sell %d ticket\n", pthread_self(), tickets);
            tickets--;
        } else {
       
            pthread_mutex_unlock(&mutex);
            break;
        }

        pthread_mutex_unlock(&mutex);
    }

    return NULL;
}

int main() {

    pthread_mutex_init(&mutex, NULL);

    pthread_t tid1, tid2, tid3;
    pthread_create(&tid1, NULL, sellticket, NULL);
    pthread_create(&tid2, NULL, sellticket, NULL);
    pthread_create(&tid3, NULL, sellticket, NULL);

    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    pthread_join(tid3, NULL);

    pthread_exit(NULL);

    pthread_mutex_destroy(&mutex);

    return 0;
}
