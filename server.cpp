#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <string.h>
#include <thread>
#include <pthread.h>

#include "server_socket.h"
#include "Task.h"

#define PORT 8080

Task task;
thread_safe_queue<int> queue;

int main(int argc, char * argv[])
{
    int server_fd = 0, connfd = 0;
    struct sockaddr_in serv_addr; 
    int address = sizeof(serv_addr);
    int recv;
    
    // get param form command line 
    // if (argc != 4)
    // {
    //     std::cout << "Please input these parameters: port, number_of_threads, size_of_connections_array" << std::endl;
    //     return 1;
    // }

    // socket creation 
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0)
    {
        perror("Error in socket creation.");
        exit(1);
    }

    // bind 
    memset(&serv_addr, '0', sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    // serv_addr.sin_port = htons(atoi(argv[1])); 
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
        thread_pool[i] = std::thread(&Task::connectionHandler, &task, std::ref(queue));
        
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

    // accept and push the new socket into the queue.
    while (1)
    {
        std::cout << "Using main thread to receive connection and push into queue."  << std::endl;
        int new_socket = accept(server_fd, (struct sockaddr *) & serv_addr, (socklen_t*) &address);
        if (new_socket < 0)
        {
            perror("accept error!!!!");
            exit(EXIT_FAILURE);
        }
        
        std::cout << "new connection is :" << new_socket << std::endl;
        std::cout << "Recv new connection push into queue" << std::endl;
        queue.push(new_socket);
    }

    return 0;
}