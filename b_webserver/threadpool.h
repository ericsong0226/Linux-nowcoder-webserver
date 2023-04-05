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
}
