#include <iostream>
#include <unistd.h>
#include <sys/syscall.h>

#include "Task.h"
#include "serverSocket.h"
#include "./utils/ThreadSafeQueue.h"
#include "./utils/File.h"

void * Task::connectionHandler (ThreadSafeQueue &queue)
{    
    while (1)
    {
        // serverSocket ss(this->get_from_queue());
        serverSocket ss(queue.wait_and_pop());
        std::cout << "The subThread " << syscall(SYS_gettid) << "is ";
        std::cout << "processing : " << std::endl;
        this->doProcessing(ss);
    }
}

void Task::doProcessing(serverSocket & ss)
{
    char * file_name;
    char * file_size;
    char * file_content;

    // recv file name 
    file_name = ss.server_recv();

    // create file 
    File file(file_name);
    // std::ofstream &recv_file = file.file_creation(file_name);
    std::ofstream &ofs = file.get_ofs();

    // recv file size
    file_size = ss.server_recv();

    // recv file content
    file_content = ss.server_recv();
    ofs << file_content;
    // recv_file << file_content;
}