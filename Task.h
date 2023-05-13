#ifndef TASK_H
#define TASK_H
#pragma once

#include <iostream>
#include <unistd.h>
#include <sys/syscall.h>

#include "serverSocket.h"
#include "./utils/File.h"
#include "./utils/ThreadSafeQueue.h"
#include "./utils/ThreadSafeQueue.cpp"
#include "serverSocket.h"

// #include "queue.h"

class Task
{       
    public:
        void * connectionHandler (ThreadSafeQueue<int> &queue);
        void doProcessing(serverSocket &ss);
};

#endif