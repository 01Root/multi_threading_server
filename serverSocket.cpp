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

void serverSocket::doProcessing ()
{
    char * file_name;
    char * file_size;
    char * file_content;

    // recv file name 
    file_name = server_recv();

    // create file 
    File file;
    std::ofstream &recv_file = file.file_creation(file_name);

    // recv file size
    file_size = server_recv();

    // recv file content
    file_content = server_recv();
    recv_file << file_content;

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
