/* ************************************************************************
> File Name:     cond.c
> Author:        程序员Eric
> 微信公众号:    源水本木
> Created Time:  Sun 15 Jan 2023 12:00:22 PM CST
> Description:   
 ************************************************************************/
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

pthread_mutex_t mutex;
pthread_cond_t cond;

struct Node {

    int num;
    struct Node * next;
};

struct Node * head = NULL;

void * producer(void * arg) {

    while (1) {
   
        pthread_mutex_lock(&mutex);
        struct Node * newNode = (struct Node *)malloc(sizeof(struct Node));
        newNode->next = head;
        head = newNode;
        newNode->num = rand() % 1000;
        printf("add node, num : %d, tid : %ld\n", newNode->num, pthread_self());

        pthread_cond_signal(&cond);

        pthread_mutex_unlock(&mutex);
        usleep(100);
    }

    return NULL;
}

void * customer(void * arg) {

    while (1) {
  
        pthread_mutex_lock(&mutex);

        struct Node * tmp = head;

        if (head != NULL) {
       
            head = head->next;
            printf("del node, num : %d, tid : %ld\n", tmp->num, pthread_self());
            free(tmp);
            pthread_mutex_unlock(&mutex);
            usleep(100);
        } else {
       
            pthread_cond_wait(&cond, &mutex);
            pthread_mutex_unlock(&mutex);
        }
    }

    return NULL;
}

int main() {

    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&cond, NULL);

    pthread_t ptids[5], ctids[5];

    for (int i = 0; i < 5; ++i) {
   
        pthread_create(&ptids[i], NULL, producer, NULL);
        pthread_create(&ctids[i], NULL, customer, NULL);
    }

    for (int i = 0; i < 5; ++i) {
   
        pthread_detach(ptids[i]);
        pthread_detach(ctids[i]);
    }

    while (1) {
   
        sleep(10);
    }

    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond);

    pthread_exit(NULL);

    return 0;
}
