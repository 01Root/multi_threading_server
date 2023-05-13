#include "join_threads.h"

join_threads::join_threads(std::vector<std::thread>& threads)
{
    this->threads_ = std::move(threads);
}

join_threads::~join_threads()
{
    for (unsigned int i = 0; i < this->threads_.size(); ++i)
    {
        if(this->threads_[i].joinable())
        {
            this->threads_[i].join();
        }
    }
}