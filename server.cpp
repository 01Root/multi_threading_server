#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <string.h>
#include <thread>
#include <pthread.h>

#include "server_socket.h"
#include "tasks.h"

#define PORT 8080

tasks task;
thread_safe_queue<int> conn_queue;

int main(int argc, char * argv[])
{
    int server_fd = 0;
    struct sockaddr_in serv_addr; 
    int address = sizeof(serv_addr);
    int recv = 0;
    
    server_socket server;

    // socket creation 
    server_fd = server.socket_creation();

    // bind 
    memset(&serv_addr, '0', sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(PORT); 
    
    recv = bind(server_fd, (struct sockaddr *) &serv_addr, sizeof(serv_addr));
    if (recv < 0)
    {
        perror("bind fail.");
        exit(1);
    }

    // make Thread pool.
    std::thread thread_pool[2];
    for (int i = 0; i < 2; ++i)
    {
        thread_pool[i] = std::thread(&tasks::connectionHandler, &task, std::ref(conn_queue));
        
    }
    for (int i = 0; i < 2; ++i)
    {
        thread_pool[i].detach();
    }

    // listen
    if ((listen(server_fd, 10)) < 0)
    {
        perror("Listen error !!!");
        exit(EXIT_FAILURE);
    }

    // accept and push the new socket into the conn_queue.
    while (1)
    {
        std::cout << "Using main thread to receive connection and push into conn_queue."  << std::endl;
        int new_socket = accept(server_fd, (struct sockaddr *) & serv_addr, (socklen_t*) &address);
        if (new_socket < 0)
        {
            perror("accept error!!!!");
            exit(EXIT_FAILURE);
        }
        
        std::cout << "new connection is :" << new_socket << std::endl;
        std::cout << "Recv new connection push into conn_queue" << std::endl;
        conn_queue.push(new_socket);
    }

    return 0;
}