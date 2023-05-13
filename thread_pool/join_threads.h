#ifndef JOIN_THREADS
#define JOIN_THREADS
#pragma once

#include <vector>
#include <thread>

class join_threads
{
    private:
        std::vector<std::thread> threads_;
    public:
        join_threads(std::vector<std::thread>& threads);
        ~join_threads();
};

#endif