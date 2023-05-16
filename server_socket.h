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

        void swap(serverSocket & other);

    public:
        // constructor
        explicit serverSocket();
        explicit serverSocket(int new_socket);

        // copy, copy assignment, move, move assignment  
        serverSocket(const serverSocket &other);
        serverSocket & operator = (serverSocket &other);
        serverSocket(const serverSocket && other) = delete;
        serverSocket & operator = (const serverSocket && other) = delete;

        // destructor
        ~serverSocket();

        char * server_recv();
        void server_recv(file & recv_file);
};

#endif