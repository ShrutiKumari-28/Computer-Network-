#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8081
#define BUFFER_SIZE 1024

int main()
{
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[BUFFER_SIZE] = {0};

    // 1. Create socket
    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    if (server_fd < 0) //here we use the if condition because if connction is fail it will return the -1 and if it is successfully execute then it will return 0,3,4,
    {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // 2. Configure address : It will hold the networking detail
    address.sin_family = AF_INET; //network protocol : it tells the operating system socket will communicate using 32 bit IPv4 addresses (ex. 127.0.0.1)
    address.sin_addr.s_addr = INADDR_ANY;//sets the ip address in which the server will listen(multiple networks or ip) allows the server to acce[t connections
    address.sin_port = htons(PORT); //set the port number to the server

    // 3. Bind socket  //without bind we can't classify the port number and ip address
    if (bind(server_fd,
             (struct sockaddr *)&address,
             sizeof(address)) < 0)
    {
        perror("Bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // 4. Listen for connections  //accept the incoming connection requests from clients
    if (listen(server_fd, 3) < 0)
    {
        perror("Listen failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    printf("Server is listening on port %d...\n", PORT);

    // 5. Accept connection
    new_socket = accept(server_fd,
                        (struct sockaddr *)&address,
                        (socklen_t *)&addrlen);

    if (new_socket < 0)
    {
        perror("Accept failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    printf("Client connected.\n");

    // 6. Communication
    read(new_socket, buffer, BUFFER_SIZE - 1);
    printf("Message from client: %s\n", buffer);

    char *message = "Hello from server";
    send(new_socket, message, strlen(message), 0);

    printf("Reply sent to client.\n");

    // 7. Close sockets
    close(new_socket);
    close(server_fd);

    return 0;
}
