#include "ThreadSafeQueue.h"

// constructor 
template <typename T>
ThreadSafeQueue<T>::ThreadSafeQueue()
{}

template <typename T>
ThreadSafeQueue<T>::ThreadSafeQueue(ThreadSafeQueue const & other)
{
    std::lock_guard<std::mutex> lock(other.mtx);
    queue = other.queue;
}

template <typename T>
void ThreadSafeQueue<T>::push (T value)
{
    // lock 
    std::lock_guard<std::mutex> lock(mtx);

    this->queue.push(value);

    // notify_one 
    this->cv.notify_one();
}

template <typename T>
bool ThreadSafeQueue<T>::empty()
{
    std::lock_guard<std::mutex> lock (mtx);
    return this->queue.empty();
}

// get a connection from queue.
template <typename T>
T ThreadSafeQueue<T>::wait_and_pop()
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