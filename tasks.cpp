#include "tasks.h"

void * tasks::connectionHandler (thread_safe_queue<int> &conn_queue)
{    
    while (1)
    {
        // server_socket ss(this->get_from_queue());
        server_socket ss(conn_queue.wait_and_pop());

        int result = ss.get_conn_fd();
        std::cout << "The subThread " << syscall(SYS_gettid);
        std::cout << " is processing with the connect named " << result << std::endl;

        this->doProcessing(ss);
    }
}

void tasks::doProcessing(server_socket & ss)
{
    char * file_name = nullptr;
    char * file_size = nullptr;
    char * file_content = nullptr;

    file_name = ss.recv_file_name();
    std::cout << "recv file name is " <<file_name << std::endl;

    // create file 
    file recv_file(file_name);
    std::ofstream &ofs = recv_file.get_ofs();

    // recv file size
    if (ss.recv_file_size(recv_file))
    {
        std::cout << "received file size." << std::endl;
    }
}
