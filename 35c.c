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
    server_address.sin_port = htons(12345); // Use the same port as the server
    server_address.sin_addr.s_addr = inet_addr("127.0.0.1"); // Use the server's IP address

    // Connect to the server
    if (connect(client_socket, (struct sockaddr*)&server_address, sizeof(server_address)) < 0) {
        perror("Error connecting to the server");
        exit(1);
    }

    printf("Connected to the server.\n");

    while (1) {
        char message[256];
        printf("Enter a message to send to the server: ");
        fgets(message, sizeof(message), stdin);

        // Send the message to the server
        send(client_socket, message, strlen(message), 0);

        // Receive and display the server's response
        char server_response[256];
        recv(client_socket, server_response, sizeof(server_response), 0);
        printf("Server response: %s\n", server_response);
    }

    // Close the client socket (This code is unreachable in the while loop)
    close(client_socket);

    return 0;
}
