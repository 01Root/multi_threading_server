#ifndef TASK_H
#define TASK_H
#pragma once

#include <iostream>
#include <unistd.h>
#include <sys/syscall.h>

#include "server_socket.h"
#include "./utils/file.h"
#include "./utils/thread_safe_queue.h"
#include "./utils/thread_safe_queue.cpp"
#include "server_socket.h"
#include "./utils/exception_hander.h"

// #include "queue.h"

class tasks
{   
    private:
        exception_hander excep_hander;
        bool recv_status;

    public:
        void * connectionHandler (thread_safe_queue<int> &queue);
        void doProcessing(server_socket &ss);
};

#endif