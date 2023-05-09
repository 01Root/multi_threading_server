#ifndef MYTHREAD_H
#define MYTHREAD_H
#pragma once

#include "./utils/ThreadSafeQueue.h"

// #include "queue.h"

class myThread
{       
    public:
        void * connectionHandler (ThreadSafeQueue &queue);
};

#endif