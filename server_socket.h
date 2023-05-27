#ifndef SERVERSOCKET_H
#define SERVERSOCKET_H
#pragma once

#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <string>

#include "./utils/file.h"
#include "./utils/exception_hander.h"

const wchar_t BUFFER_SIZE = 1024;

class server_socket
{
    private:
        int conn_fd;
        std::string internet_address_family;
        std::string socket_type;

        std::string ip_address;
        wchar_t port;
        struct sockaddr_in serv_addr; 

        int listen_num;
        
        int recv_status;

        char recv_buff[BUFFER_SIZE];
        bool close_status;
        exception_hander excep_hander;
        

    public:
        // constructor
        explicit server_socket();
        explicit server_socket(int new_socket);
        explicit server_socket(std::string internet_address_family,std::string socket_type);
        explicit server_socket(std::string internet_address_family,std::string socket_type, std::string ip_address, wchar_t port);
        explicit server_socket(std::string internet_address_family,std::string socket_type, std::string ip_address, wchar_t port, int listen_num);

        // swap
        void swap(server_socket & lhs, server_socket & rhs);

        // get function 
        int get_conn_fd();

        // copy, copy assignment, move, move assignment  
        server_socket(const server_socket &other);
        server_socket & operator = (const server_socket &other);
        server_socket(const server_socket && other) = delete;
        server_socket & operator = (const server_socket && other) = delete;

        // socket creation.
        void socket_creation();

        // bind 
        void socket_bind(std::string ip_address, wchar_t port);

        // listen 
        void socket_listen(int listen_num);

        // accept
        int socket_accept();

        // recv 
        char * server_recv();
        void server_recv(file & recv_file);
        void recv_data_from_client();

        // recv 
        char * recv_file_name();
        char * recv_file_size();
        void recv_file_content(file & recv_file);

        // closed
        void closed();

        // destructor
        ~server_socket();
};

#endif