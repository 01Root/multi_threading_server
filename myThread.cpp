#include <iostream>
#include <thread>
#include <mutex>
#include <pthread.h>
#include <queue>
#include <unistd.h> /* must include this file */
#include <sys/syscall.h>

#include "myThread.h"
#include "serverSocket.h"

// push the connection into queue.
void myThread::push_into_queue(int value)
{
    // lock 
    std::unique_lock<std::mutex> lock(mtx);

    std::cout << "Received one connection, push it into queue." << std::endl;
    this->q.push(value);

    std::cout << "Wake up sub-threads to process data" << std::endl;
    // notify_one 
    this->cv.notify_one();

}

// get a connection from queue.
int myThread::get_from_queue()
{
    // lock 
    std::unique_lock<std::mutex> lock(mtx);

    // wait for element to become avaiable.
    while (this->q.empty())
    {
        std::cout << "Queue is empty, sub-threads are waiting." << std::endl;
        this->cv.wait(lock);
    }

    // get an element.
    int val = this->q.front();
    this->q.pop();

    return val;    
}

void * myThread::connectionHandler ()
{
    // int connfd = 0;
    
    while (1)
    {
        // connfd = this->get_from_queue();
        serverSocket ss(this->get_from_queue());
        std::cout << "The subThread " << syscall(SYS_gettid) << "is ";
        std::cout << "processing : " << std::endl;
        ss.doProcessing();
    }
}