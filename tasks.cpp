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

        // std::cout << "The subThread " << syscall(SYS_gettid) << " is ";
        // std::cout << "processing : " << std::endl;
        this->doProcessing(ss);
    }
}

void tasks::doProcessing(server_socket & ss)
{
    char * file_name = nullptr;
    char * file_size = nullptr;
    char * file_content = nullptr;

    // recv file name 
    // file_name = ss.server_recv();
    // std::cout << "recv file name is " <<file_name << std::endl;

    // // create file 
    // file recv_file(file_name);
    // std::ofstream &ofs = recv_file.get_ofs();

    // // recv file size
    // std::cout << "recving file size." << std::endl;
    // file_size = ss.server_recv();
    // std::cout << "recv file size is " << file_size  << std::endl;
    // // recv_file.set_size(atoi(file_size));

    // // recv file content
    // ss.server_recv(recv_file);

    // ss.recv_data_from_client();

    file_name = ss.recv_file_name();
    std::cout << "recv file name is " <<file_name << std::endl;

    // create file 
    file recv_file(file_name);
    std::ofstream &ofs = recv_file.get_ofs();

    // recv file size
    std::cout << "recving file size." << std::endl;
    file_size = ss.recv_file_size();
    std::cout << "recv file size is " << file_size  << std::endl;
    // recv_file.set_size(atoi(file_size));
}
