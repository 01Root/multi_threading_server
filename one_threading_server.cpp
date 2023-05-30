#include "server_socket.h"
#include "tasks.h"

#define PORT 8080

int main(int argc, char * argv[])
{
    // creation and bind and listen.
    server_socket server("ipv4", "tcp", "any", 8080, 10);

    while (1)
    {
        int new_socket = server.socket_accept();

        server_socket ss(new_socket);

        tasks task;

        task.doProcessing(ss);
    }

    return 0;
}