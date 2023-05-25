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
    // creation and bind and listen.
    server_socket server("ipv4", "tcp", "any", 8080, 10);

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

    // accept and push the new socket into the conn_queue.
    while (1)
    {
        std::cout << "Using main thread to receive connection and push into conn_queue."  << std::endl;

        int new_socket = server.socket_accept();
        
        std::cout << "Recv new connection, push the new connection " << new_socket << " into queue." << std::endl;
        conn_queue.push(new_socket);
        std::cout << "check the front value of conn_queue: " << conn_queue.front() << std::endl;
    }

    return 0;
}