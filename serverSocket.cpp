#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#include "serverSocket.h"
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
