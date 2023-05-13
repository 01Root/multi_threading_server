#ifndef THREAD_SAFE_QUEUE_H
#define THREAD_SAFE_QUEUE_H
#pragma once

#include <mutex>
#include <condition_variable>
#include <queue>

template <typename T>

class thread_safe_queue
{
    private:
        mutable std::mutex mtx;
        std::condition_variable cv;
        std::queue<T> queue;
        
    public:
        // constructor 
        thread_safe_queue();
        thread_safe_queue(thread_safe_queue const & other);

        void push(T value);
        bool empty();
        T wait_and_pop();
};

#endif