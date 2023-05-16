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
        std::queue<T> conn_queue;
        
    public:
        // constructor 
        explicit thread_safe_queue();

        // copy, copy assign, move, move assign 
        thread_safe_queue (const thread_safe_queue<T> &other);
        thread_safe_queue<T> & operator = (const thread_safe_queue<T> &other);
        thread_safe_queue (const thread_safe_queue<T> && other) = delete;
        thread_safe_queue<T> & operator = (const thread_safe_queue<T> && other) = delete;

        void push(T value);
        bool empty();
        T wait_and_pop();
};

#endif