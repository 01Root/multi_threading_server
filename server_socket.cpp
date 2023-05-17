#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#include "server_socket.h"
#include "./utils/file.h"

//init 
server_socket::server_socket():conn_fd(0),
                                internet_address_family(""), 
                                socket_type(""), 
                                ip_address(""),
                                port(0),
                                listen_num(0),
                                recv_status(0), 
                                recv_buff(""), 
                                close_status(true){}

// constructor
server_socket::server_socket(int new_socket)
{
    this->conn_fd = new_socket;
}
server_socket::server_socket(std::string internet_address_family,std::string socket_type)
{
    if(("ipv4" == internet_address_family) && ("tcp" == socket_type))
    {
        this->socket_creation();
    }
    else
    {
        excep_hander.print_and_exit("please write right address family and socket type.");
    }
}
server_socket::server_socket(std::string internet_address_family,std::string socket_type, std::string ip_address, wchar_t port)
{
    if(("ipv4" == internet_address_family) && ("tcp" == socket_type) && ("any" == ip_address))
    {
        this->socket_creation();
        this->socket_bind(ip_address, port);
    }
    else
    {
        excep_hander.print_and_exit("please write correctly.");
    }
}
server_socket::server_socket(std::string internet_address_family,std::string socket_type, std::string ip_address, wchar_t port, int listen_num)
{
    if(("ipv4" == internet_address_family) && ("tcp" == socket_type) && ("any" == ip_address))
    {
        this->socket_creation();
        this->socket_bind(ip_address, port);
        this->socket_listen(listen_num);
    }
    else
    {
        excep_hander.print_and_exit("please write correctly.");
    }
}


// copy, copy assignment, move, move assignment.
server_socket::server_socket(const server_socket &other)
{
    this->conn_fd = other.conn_fd;
    this->recv_status = other.recv_status;
    strncpy(this->recv_buff, other.recv_buff, BUFFER_SIZE);  
}
server_socket & server_socket::operator = (const server_socket &other)
{
    this->conn_fd = other.conn_fd;
    this->recv_status = other.recv_status;
    strncpy(this->recv_buff, other.recv_buff, BUFFER_SIZE); 
}

// socket creation 
void server_socket::socket_creation()
{
    this->conn_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (this->conn_fd < 0)
    {
        excep_hander.print_and_exit("Error in socket creation.");
    }
}

// socket bind 
void server_socket::socket_bind(std::string ip_address, wchar_t port)
{
    memset(&serv_addr, '0', sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    if ("any" == ip_address)
    {
        serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    }
    else
    {
        excep_hander.print_and_exit("please write right ip address.");
    }
    serv_addr.sin_port = htons(port); 
    
    recv_status = bind(conn_fd, (struct sockaddr *) &serv_addr, sizeof(serv_addr));
    if (recv < 0)
    {
        excep_hander.print_and_exit("bind fail.");
    }
}

// listen 
void server_socket::socket_listen(int listen_num)
{
    if ((listen(conn_fd, listen_num)) < 0)
    {
        excep_hander.print_and_exit("listen fail.");
    }
}

// accept 
int server_socket::socket_accept()
{
    int address = sizeof(serv_addr);
    int new_socket = accept(conn_fd, (struct sockaddr *) & serv_addr, (socklen_t*) &address);
    if (new_socket < 0)
    {
        perror("accept error!!!!");
        exit(EXIT_FAILURE);
    }
    return new_socket;
}

// recv 
char * server_socket::server_recv()
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
void server_socket::server_recv(file & recv_file)
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

// closed
void server_socket::closed()
{
    close(this->conn_fd);
    this->close_status = true;
}

// destructor
server_socket::~server_socket()
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