#include "thread_safe_queue.h"

// constructor 
template <typename T>
thread_safe_queue<T>::thread_safe_queue()
{}

template <typename T>
thread_safe_queue<T>::thread_safe_queue(thread_safe_queue const & other)
{
    std::lock_guard<std::mutex> lock(other.mtx);
    queue = other.queue;
}

template <typename T>
void thread_safe_queue<T>::push (T value)
{
    // lock 
    std::lock_guard<std::mutex> lock(mtx);

    this->queue.push(value);

    // notify_one 
    this->cv.notify_one();
}

template <typename T>
bool thread_safe_queue<T>::empty()
{
    std::lock_guard<std::mutex> lock (mtx);
    return this->queue.empty();
}

// get a connection from queue.
template <typename T>
T thread_safe_queue<T>::wait_and_pop()
{
    // lock 
    std::unique_lock<std::mutex> lock(mtx);

    // wait for element to become avaiable.
    while (this->queue.empty())
    {
        this->cv.wait(lock, [this]{return !this->queue.empty(); });
    }

    // get an element.
    T val = this->queue.front();
    this->queue.pop();

    return val;    
}