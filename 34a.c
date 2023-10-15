#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

void handle_client(int client_socket) {
    char client_message[256];
    while (1) {
        // Receive data from the client
        int bytes_received = recv(client_socket, client_message, sizeof(client_message), 0);
        if (bytes_received <= 0) {
            break; // Client disconnected
        }
        client_message[bytes_received] = '\0';
        printf("Client says: %s", client_message);

        // Send a response to the client
        send(client_socket, "Message received by the server\n", 31, 0);
    }
    close(client_socket);
    exit(0);
}

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

    printf("Server is listening for incoming connections...\n");

    while (1) {
        // Accept a connection
        int client_socket = accept(server_socket, NULL, NULL);
        if (client_socket < 0) {
            perror("Error accepting connection");
            continue;
        }

        // Fork a new process to handle the client
        int pid = fork();
        if (pid == 0) {
            // Child process handles the client
            close(server_socket); // Close the server socket in the child process
            handle_client(client_socket);
        } else {
            close(client_socket); // Parent process closes the client socket
        }
    }

    // Close the server socket (This code is unreachable in the while loop)
    close(server_socket);

    return 0;
}
