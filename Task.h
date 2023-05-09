#ifndef TASK_H
#define TASK_H
#pragma once

#include "./utils/ThreadSafeQueue.h"

// #include "queue.h"

class Task
{       
    public:
        void * connectionHandler (ThreadSafeQueue &queue);
};

#endif