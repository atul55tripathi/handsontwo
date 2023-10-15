#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    // Create a socket
    int client_socket = socket(AF_INET, SOCK_STREAM, 0);
    
    // Define the server address
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(12345); // Port number
    server_address.sin_addr.s_addr = INADDR_ANY;

    // Connect to the server
    connect(client_socket, (struct sockaddr*)&server_address, sizeof(server_address));

    // Send and receive data in a loop
    char client_message[256];
    char server_response[256];
    while (1) {
        // Send data to the server
        printf("Enter a message to send to the server: ");
        fgets(client_message, sizeof(client_message), stdin);
        send(client_socket, client_message, sizeof(client_message), 0);

        // Receive data from the server
        recv(client_socket, server_response, sizeof(server_response), 0);
        printf("Server says: %s\n", server_response);
    }

    // Close the socket
    close(client_socket);

    return 0;
}
