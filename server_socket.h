#ifndef SERVERSOCKET_H
#define SERVERSOCKET_H
#pragma once

#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>

#include "./utils/file.h"
#include "./utils/exception_hander.h"

const wchar_t BUFFER_SIZE = 1024;

class server_socket
{
    private:
        int conn_fd;
        
        int recv_status;

        char recv_buff[BUFFER_SIZE];
        bool close_status;
        exception_hander excep_hander;
        

    public:
        // constructor
        explicit server_socket();
        explicit server_socket(int new_socket);

        // copy, copy assignment, move, move assignment  
        server_socket(const server_socket &other);
        server_socket & operator = (const server_socket &other);
        server_socket(const server_socket && other) = delete;
        server_socket & operator = (const server_socket && other) = delete;

        // socket creation.
        int socket_creation();

        // bind 
        int socket_bind();

        // listen 
        

        // destructor
        ~server_socket();

        // closed
        void closed();


        char * server_recv();
        void server_recv(file & recv_file);
};

#endif