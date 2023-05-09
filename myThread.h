#ifndef MYTHREAD_H
#define MYTHREAD_H
#pragma once

#include "./utils/ThreadSafeQueue.h"

// #include "queue.h"

class myThread
{       
    public:

        // push into queue
        void push_into_queue(int value);
        
        // get a connection from the queue.
        int get_from_queue();

        void * connectionHandler (ThreadSafeQueue &queue);

};

#endif