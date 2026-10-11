

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 30008
#define SIZE 1024

int main(int argc, char *argv[])
{
    int s;
    char b[SIZE], reply[SIZE], msg[SIZE];
    struct sockaddr_in server;
    socklen_t len = sizeof(server);

   
    if (argc != 3) {
        printf("Usage: %s <server_ip> <roll>\n", argv[0]);
        return 1;
    }

    
    s = socket(AF_INET, SOCK_DGRAM, 0);

    if (s < 0) {
        perror("Socket error");
        return 1;
    }

    
    memset(&server, 0, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);

    if (inet_pton(AF_INET, argv[1],
                  &server.sin_addr) != 1) {
        printf("Invalid server IP\n");
        close(s);
        return 1;
    }

    while (1) {
        printf("Enter text (or EXIT): ");

        if (fgets(b, SIZE, stdin) == NULL) {
            strcpy(b, "EXIT");
        } else {
            b[strcspn(b, "\n")] = '\0';
        }

        
        snprintf(msg, sizeof(msg), "%s#%s", argv[2], b);

        
        sendto(s, msg, strlen(msg), 0,
               (struct sockaddr *)&server, len);

        
        int n = recvfrom(s, reply, SIZE - 1, 0,
                         (struct sockaddr *)&server, &len);

        if (n < 0) {
            perror("Receive error");
            break;
        }

        reply[n] = '\0';
        printf("Server response: %s\n", reply);

        if (strcmp(b, "EXIT") == 0)
            break;
    }

    close(s);
    return 0;
}