#ifndef TASK_H
#define TASK_H
#pragma once

#include "./utils/ThreadSafeQueue.h"
#include "serverSocket.h"

// #include "queue.h"

class Task
{       
    public:
        void * connectionHandler (ThreadSafeQueue &queue);
        void doProcessing(serverSocket &ss);
};

#endif