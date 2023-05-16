#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#include "server_socket.h"
#include "./utils/file.h"

//init 
serverSocket::serverSocket():conn_fd(0), recv_status(0), recv_buff(""), close_status(true){}

// constructor
serverSocket::serverSocket(int new_socket)
{
    this->conn_fd = new_socket;
}

// copy, copy assignment, move, move assignment.
serverSocket::serverSocket(const serverSocket &other)
{
    this->conn_fd = other.conn_fd;
    this->recv_status = other.recv_status;
    strncpy(this->recv_buff, other.recv_buff, BUFFER_SIZE);  
}
serverSocket & serverSocket::operator = (const serverSocket &other)
{
    this->conn_fd = other.conn_fd;
    this->recv_status = other.recv_status;
    strncpy(this->recv_buff, other.recv_buff, BUFFER_SIZE); 
}

// closed
void serverSocket::closed()
{
    close(this->conn_fd);
    this->close_status = true;
}

// destructor
serverSocket::~serverSocket()
{
    if (!this->close_status)
    {
        try
        {
            this->closed();
        }
        catch(...)
        {
            excep_hander.print_and_exit("close connection fail!");
        }
    }
}

char * serverSocket::server_recv()
{
    // recv data from client 
    memset(recv_buff, '0', sizeof(recv_buff));
    recv_status = recv(conn_fd, recv_buff, sizeof(recv_buff)-1, 0);
    if (recv_status == -1)
    {
        excep_hander.print_and_exit("recv fail.");
    }
    recv_buff[recv_status] = '\0';

    std::cout << "The received buffer is " << recv_buff << std::endl;
    return recv_buff;
}

void serverSocket::server_recv(file & recv_file)
{
    int file_size = recv_file.get_size();
    int recved_size = 0;
    std::ofstream &ofs = recv_file.get_ofs();

    while (recved_size < file_size)
    {
        memset(recv_buff, '0', sizeof(recv_buff));
        // recv_status = recv(conn_fd, recv_buff, sizeof(recv_buff)-1, 0);
        recv_status = recv(conn_fd, recv_buff, 1024, 0);
        if (recv_status == -1)
        {
            excep_hander.print_and_exit("recv fail.");
        }
        recv_buff[recv_status] = '\0';
        ofs << recv_buff;
        // std::cout << "The received buffer is " << recv_buff << std::endl;
        recved_size += recv_status;
    }
    std::cout << "recved_done." <<std::endl;
}