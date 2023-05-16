#ifndef SERVERSOCKET_H
#define SERVERSOCKET_H
#pragma once

#include <iostream>

#include "./utils/file.h"

const wchar_t BUFFER_SIZE = 1024;

class serverSocket
{
    private:
        int conn_fd;
        int recv_status;
        char recv_buff[BUFFER_SIZE];

    public:
        explicit serverSocket();
        // constructor
        explicit serverSocket(int new_socket);

        // destructor
        ~serverSocket();

        char * server_recv();
        void server_recv(file & recv_file);
};

#endif