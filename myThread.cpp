#include <iostream>
#include <unistd.h>
#include <sys/syscall.h>

#include "myThread.h"
#include "serverSocket.h"
#include "./utils/ThreadSafeQueue.h"

void * myThread::connectionHandler (ThreadSafeQueue &queue)
{    
    while (1)
    {
        // serverSocket ss(this->get_from_queue());
        serverSocket ss(queue.wait_and_pop());
        std::cout << "The subThread " << syscall(SYS_gettid) << "is ";
        std::cout << "processing : " << std::endl;
        ss.doProcessing();
    }
}