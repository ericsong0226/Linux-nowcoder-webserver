/* ************************************************************************
> File Name:     threadpool.h
> Author:        程序员Eric
> 微信公众号:    源水本木
> Created Time:  Wed 05 Apr 2023 01:57:25 PM CST
> Description:   
 ************************************************************************/
#ifndef THREADPOOL_H
#define THREADPOOL_H

#include <pthread.h>
#include <list>
#include <exception>
#include <cstdio>
#include "locker.h"

template<typename T>
clase threadpool {
public:
    threadpool(int thread_number = 8, int max_requests = 10000);
    ~threadpool();
    bool append(T* request);

private:
    static void* worker(void * arg);
    void run();

private:
    // thread number
    int m_thread_number;

    pthread_t * m_threads;

    int m_max_requests;

    std::list<T*> m_workqueue;

    locker m_queuelocker;
    
    sem m_queuestat;

    bool m_stop;
};

template<typename T>
threadpool<T>::threadpool(int thread_number, int max_requests) : 
    m_thread_number(thread_number), m_max_requests(max_requests),
    m_stop(false), m_threads(NULL) {
        
        if ((thread_number <= 0) || (max_requests <= 0)) {
            throw std::exception();
        }

        m_threads = new pthread_t[m_thread_number];
        if (!m_threads) {
            throw std::exception();
        }

        for (int i = 0; i < thread_number; ++i) {
            printf("create the %dth thread\n", i);

            if (pthread_create(m_threads + i, NULL, worker, this) != 0) {
                delete[] m_threads;
                throw std::exception();
            }

            if (pthread_detach(m_threads[i])) {
                delete[] m_threads;
                throw std::exception();
            }
        }
    } 

template<typename T>
threadpool<T>::~threadpool() {
    delete[] m_threads;
    m_stop = true;
}
