#include "Task.h"

void * Task::connectionHandler (ThreadSafeQueue<int> &queue)
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
    std::ofstream &ofs = file.get_ofs();

    // recv file size
    file_size = ss.server_recv();
    file.set_size(atoi(file_size));

    // recv file content
    ss.server_recv(file);
    // ss.server_recv();
    // int times = 2;
    // while (times)
    // {
    //     file_content = ss.server_recv();
    //     ofs << file_content;    
    //     --times;
    // }
    
}