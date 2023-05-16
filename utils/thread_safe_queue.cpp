#include "thread_safe_queue.h"

// constructor 
template <typename T>
thread_safe_queue<T>::thread_safe_queue()
{}

// copy, copy assign, move, move assign 
template <typename T>
thread_safe_queue<T>::thread_safe_queue(thread_safe_queue<T> const & other)
{
    std::lock_guard<std::mutex> lock(other.mtx);
    this->conn_queue = other.conn_queue;
}

template <typename T>
thread_safe_queue<T> & thread_safe_queue<T>::operator = (const thread_safe_queue<T> &other)
{
    std::lock_guard<std::mutex> lock(other.mtx);
    this->conn_queue = other.conn_queue;
}

// push 
template <typename T>
void thread_safe_queue<T>::push (T value)
{
    // lock 
    std::lock_guard<std::mutex> lock(mtx);

    this->conn_queue.push(value);

    // notify_one 
    this->cv.notify_one();
}

template <typename T>
bool thread_safe_queue<T>::empty()
{
    std::lock_guard<std::mutex> lock (mtx);
    return this->conn_queue.empty();
}

// get a connection from conn_queue.
template <typename T>
T thread_safe_queue<T>::wait_and_pop()
{
    // lock 
    std::unique_lock<std::mutex> lock(mtx);

    // wait for element to become avaiable.
    while (this->conn_queue.empty())
    {
        this->cv.wait(lock, [this]{return !this->conn_queue.empty(); });
    }

    // get an element.
    T val = this->conn_queue.front();
    this->conn_queue.pop();

    return val;    
}