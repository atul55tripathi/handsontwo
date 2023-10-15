#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    // Create a socket
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    
    // Define the server address
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(12345); // Port number
    server_address.sin_addr.s_addr = INADDR_ANY;

    // Bind the socket to the IP address and port
    bind(server_socket, (struct sockaddr*)&server_address, sizeof(server_address));

    // Listen for incoming connections
    listen(server_socket, 5);

    // Accept a connection
    int client_socket = accept(server_socket, NULL, NULL);

    // Send and receive data in a loop
    char server_message[256];
    char client_message[256];
    while (1) {
        // Receive data from the client
        recv(client_socket, &client_message, sizeof(client_message), 0);
        printf("Client says: %s\n", client_message);

        // Send data to the client
        printf("Enter a message to send to the client: ");
        fgets(server_message, sizeof(server_message), stdin);
        send(client_socket, server_message, sizeof(server_message), 0);
    }

    // Close the sockets
    close(client_socket);
    close(server_socket);

    return 0;
}
