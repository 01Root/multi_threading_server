#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#include "server_socket.h"
#include "./utils/File.h"

// constructor
serverSocket::serverSocket(int new_socket)
{
    this->conn_fd = new_socket;
}

// destructor
serverSocket::~serverSocket()
{
    close(conn_fd);
}

char * serverSocket::server_recv()
{
    // recv data from client 
    memset(recv_buff, '0', sizeof(recv_buff));
    recv_status = recv(conn_fd, recv_buff, sizeof(recv_buff)-1, 0);
    if (recv_status == -1)
    {
        perror("recv fail.");
        exit(1);
    }
    recv_buff[recv_status] = '\0';

    std::cout << "The received buffer is " << recv_buff << std::endl;
    return recv_buff;
}

void serverSocket::server_recv(File & file)
{
    int file_size = file.get_size();
    int recved_size = 0;
    std::ofstream &ofs = file.get_ofs();

    while (recved_size < file_size)
    {
        memset(recv_buff, '0', sizeof(recv_buff));
        // recv_status = recv(conn_fd, recv_buff, sizeof(recv_buff)-1, 0);
        recv_status = recv(conn_fd, recv_buff, 1024, 0);
        if (recv_status == -1)
        {
            perror("recv fail.");
            exit(1);
        }
        recv_buff[recv_status] = '\0';
        ofs << recv_buff;
        // std::cout << "The received buffer is " << recv_buff << std::endl;
        recved_size += recv_status;
    }
    std::cout << "recved_done." <<std::endl;
}