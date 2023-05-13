#ifndef TASK_H
#define TASK_H
#pragma once

#include <iostream>
#include <unistd.h>
#include <sys/syscall.h>

#include "server_socket.h"
#include "./utils/File.h"
#include "./utils/thread_safe_queue.h"
#include "./utils/thread_safe_queue.cpp"
#include "server_socket.h"

// #include "queue.h"

class tasks
{       
    public:
        void * connectionHandler (thread_safe_queue<int> &queue);
        void doProcessing(serverSocket &ss);
};

#endif