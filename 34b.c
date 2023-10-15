#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>

void *handle_client(void *arg) {
    int client_socket = *(int *)arg;
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
    free(arg);
    return NULL;
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
        int *client_socket = malloc(sizeof(int)); // Allocate memory for client socket
        *client_socket = accept(server_socket, NULL, NULL);
        if (*client_socket < 0) {
            perror("Error accepting connection");
            free(client_socket);
            continue;
        }

        // Create a new thread to handle the client
        pthread_t client_thread;
        if (pthread_create(&client_thread, NULL, handle_client, (void *)client_socket) != 0) {
            perror("Error creating thread");
            free(client_socket);
        } else {
            pthread_detach(client_thread); // Detach the thread to auto-reclaim resources
        }
    }

    // Close the server socket (This code is unreachable in the while loop)
    close(server_socket);

    return 0;
}
