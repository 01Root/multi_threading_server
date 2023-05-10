#ifndef SERVERSOCKET_H
#define SERVERSOCKET_H
#pragma once

#include <iostream>

#define BUFFER_SIZE 1024

class serverSocket
{
    private:
        int conn_fd;
        int recv_status;
        char recv_buff[BUFFER_SIZE];

    public:
        // constructor
        serverSocket(int new_socket);

        // destructor
        ~serverSocket();

        char * server_recv();
};

#endif