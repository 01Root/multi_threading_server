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
        exception_hander::print_and_exit("please write right address family and socket type.");
    }
}
server_socket::server_socket(std::string internet_address_family,std::string socket_type, std::string ip_address, wchar_t port)
                :server_socket("ipv4", "tcp")
{
    if ("any" == ip_address)
    {
        this->socket_bind(ip_address, port);
    }
    else
    {
        exception_hander::print_and_exit("please write correct ip address.");
    }
}
server_socket::server_socket(std::string internet_address_family,std::string socket_type, std::string ip_address, wchar_t port, int listen_num)
                :server_socket("ipv4", "tcp", "any", 8080)
{
    this->socket_listen(listen_num);
}

// swap
void server_socket::swap(server_socket & lhs, server_socket & rhs)
{
    std::swap(lhs.conn_fd, rhs.conn_fd);
    std::swap(lhs.internet_address_family, rhs.internet_address_family);
    std::swap(lhs.socket_type, rhs.socket_type);
    std::swap(lhs.ip_address, rhs.ip_address);
    std::swap(lhs.port, rhs.port);
    std::swap(lhs.serv_addr, rhs.serv_addr);
    std::swap(lhs.listen_num, rhs.listen_num);
    std::swap(lhs.recv_status, rhs.recv_status);
    std::swap(lhs.recv_buff, rhs.recv_buff);
    std::swap(lhs.close_status, rhs.close_status);
    std::swap(lhs.excep_hander, rhs.excep_hander);
}

// get function 
int server_socket::get_conn_fd()
{
    return this->conn_fd;
}

// copy, copy assignment, move, move assignment.
server_socket::server_socket(const server_socket &other)
{
    server_socket temp(other);
    this->swap(*this, temp); 
}
server_socket & server_socket::operator = (const server_socket &other)
{
    server_socket temp(other);
    this->swap(*this, temp);
    return *this;
}

// socket creation 
void server_socket::socket_creation()
{
    this->conn_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (this->conn_fd < 0)
    {
        exception_hander::print_and_exit("Error in socket creation.");
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
        exception_hander::print_and_exit("please write right ip address.");
    }
    serv_addr.sin_port = htons(port); 
    
    recv_status = bind(conn_fd, (struct sockaddr *) &serv_addr, sizeof(serv_addr));
    if (recv < 0)
    {
        exception_hander::print_and_exit("bind fail.");
    }
}

// listen 
void server_socket::socket_listen(int listen_num)
{
    if ((listen(conn_fd, listen_num)) < 0)
    {
        exception_hander::print_and_exit("listen fail.");
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
char * server_socket::recv_file_name()
{
    memset(recv_buff, '0', BUFFER_SIZE);
    recv_status = recv(conn_fd, recv_buff, BUFFER_SIZE, 0);
    if (recv_status == -1)
    {
        exception_hander::print_and_exit("recv fail.");
    }

    std::cout << "The received buffer is " << recv_buff << std::endl;

    // std::cout << "The Whole received buffer of file name is :";
    // for (int i = 0; i < BUFFER_SIZE; ++i)
    // {
    //     std::cout << recv_buff[i];
    // }

    return recv_buff;
}
bool server_socket::recv_file_size(file & recv_file)
{
    memset(recv_buff, '0', BUFFER_SIZE);
    recv_status = recv(conn_fd, recv_buff, BUFFER_SIZE, 0);
    if (recv_status == -1)
    {
        exception_hander::print_and_exit("recv fail.");
        return false;
    }

    // std::cout << "The Whole received buffer of file size is :";
    // for (int i = 0; i < BUFFER_SIZE; ++i)
    // {
    //     std::cout << recv_buff[i];
    // }

    recv_file.set_size(atoi(recv_buff));
    return true;    
}
bool server_socket::recv_file_content(file & recv_file)
{
    int file_size = recv_file.get_size();
    int recved_size = 0;
    std::ofstream &ofs = recv_file.get_ofs();

    while (recved_size < file_size)
    {
        memset(recv_buff, '0', BUFFER_SIZE);

        recv_status = recv(conn_fd, recv_buff, BUFFER_SIZE, 0);
        // std::cout << "the recv buffer is " << recv_buff << std::endl;
        if (recv_status == -1)
        {
            exception_hander::print_and_exit("recv fail.");
        }
        recv_buff[recv_status] = '\0';
        ofs << recv_buff;

        // std::cout << "recved size is " << recved_size << std::endl;
        recved_size += recv_status;
    }
    std::cout << "recved size is " << recved_size << std::endl;
    std::cout << "file size is " << file_size << std::endl;


    return true;
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
            exception_hander::print_and_exit("close connection fail!");
        }
    }
}