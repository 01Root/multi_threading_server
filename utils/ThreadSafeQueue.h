#ifndef THREAD_SAFE_QUEUE_H
#define THREAD_SAFE_QUEUE_H
#pragma once

#include <mutex>
#include <condition_variable>
#include <queue>

class ThreadSafeQueue
{
    private:
        mutable std::mutex mtx;
        std::condition_variable cv;
        std::queue<int> queue;
        
    public:
        // constructor 
        ThreadSafeQueue();
        ThreadSafeQueue(ThreadSafeQueue const & other);

        void push(int value);
        bool empty();
        int wait_and_pop();
};



#endif