#ifndef MYTHREAD_H
#define MYTHREAD_H
#pragma once

#include <mutex>
#include <condition_variable>
#include <pthread.h>
#include <queue>

// #include "queue.h"

class myThread
{
    private:
        // queue *q;
        std::mutex mtx;
        std::condition_variable cv;
        std::queue<int> q;
        
    public:
        // constructor and destructor 
        // myThread(int queue_capasity);
        // ~myThread();

        // push into queue
        void push_into_queue(int value);
        
        // get a connection from the queue.
        int get_from_queue();

        void * connectionHandler ();

};

#endif