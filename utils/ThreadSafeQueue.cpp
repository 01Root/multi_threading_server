#include "ThreadSafeQueue.h"

void ThreadSafeQueue::push (int value)
{
    // lock 
    std::lock_guard<std::mutex> lock(mtx);

    this->queue.push(value);

    // notify_one 
    this->cv.notify_one();
}

bool ThreadSafeQueue::empty()
{
    std::lock_guard<std::mutex> lock (mtx);
    return this->queue.empty();
}

// get a connection from queue.
int ThreadSafeQueue::wait_and_pop()
{
    // lock 
    std::unique_lock<std::mutex> lock(mtx);

    // wait for element to become avaiable.
    while (this->queue.empty())
    {
        this->cv.wait(lock, [this]{return !this->queue.empty(); });
    }

    // get an element.
    int val = this->queue.front();
    this->queue.pop();

    return val;    
}