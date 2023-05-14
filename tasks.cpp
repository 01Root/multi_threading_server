#include "tasks.h"

void * tasks::connectionHandler (thread_safe_queue<int> &queue)
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

void tasks::doProcessing(serverSocket & ss)
{
    char * file_name;
    char * file_size;
    char * file_content;

    // recv file name 
    file_name = ss.server_recv();

    // create file 
    file recv_file(file_name);
    std::ofstream &ofs = recv_file.get_ofs();

    // recv file size
    file_size = ss.server_recv();
    recv_file.set_size(atoi(file_size));

    // recv file content
    ss.server_recv(recv_file);
}