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

    // recv file name 
    file_name = ss.recv_file_name();
    std::cout << "recv file name is " <<file_name << std::endl;

    // create file 
    file recv_file(file_name);
    std::ofstream &ofs = recv_file.get_ofs();

    // recv file size
    std::cout << "Start recv file size." << std::endl;
    recv_status = ss.recv_file_size(recv_file);
    exception_hander::judge_success_or_not(recv_status, "Received file size success.", "Received file size fail.");

    // recv file content.
    std::cout << "Start recv file content." << std::endl;
    recv_status = ss.recv_file_content(recv_file);
    exception_hander::judge_success_or_not(recv_status, "Received file content success.", "Received file content fail.");
}
