#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#include <atomic>
#include <thread>

#include "../utils/thread_safe_queue.h"
#include "join_threads.h"

class thread_pool
{
    private:
        std::atomic_bool done;
        thread_safe_queue<int> queue;
        std::vector<std::thread> threads;
        join_threads joiner;

        


    public:
};

#endif