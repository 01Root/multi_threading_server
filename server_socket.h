#ifndef SERVERSOCKET_H
#define SERVERSOCKET_H
#pragma once

#include <iostream>

#include "./utils/file.h"

#define BUFFER_SIZE 1024

class serverSocket
{
    private:
        int conn_fd;
        int recv_status;
        char recv_buff[BUFFER_SIZE];

    public:
        serverSocket();
        // constructor
        serverSocket(int new_socket);

        // destructor
        ~serverSocket();

        char * server_recv();
        void server_recv(file & recv_file);
};

#endif