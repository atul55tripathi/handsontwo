#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

int main() {
    int pipe_fd[2];
    pid_t child_pid;

    // Create a pipe
    if (pipe(pipe_fd) == -1) {
        perror("Pipe creation failed");
        exit(EXIT_FAILURE);
    }

    if ((child_pid = fork()) == -1) {
        perror("Fork failed");
        exit(EXIT_FAILURE);
    }

    if (child_pid == 0) {
        // Child process
        // Close read-end of the pipe
        close(pipe_fd[0]);

        // Redirect stdout to the write-end of the pipe
        if (fcntl(pipe_fd[1], F_DUPFD, STDOUT_FILENO) == -1) {
            perror("fcntl");
            exit(EXIT_FAILURE);
        }

        // Close the original write-end of the pipe
        close(pipe_fd[1]);

        // Execute "ls -l" command
        execlp("ls", "ls", "-l", NULL);
        perror("execlp");
        // Ensure the child process exits after execution
    } else {
        // Parent process
        // Close write-end of the pipe
        close(pipe_fd[1]);

        // Redirect stdin to the read-end of the pipe
        if (fcntl(pipe_fd[0], F_DUPFD, STDIN_FILENO) == -1) {
            perror("fcntl");
            exit(EXIT_FAILURE);
        }

        // Close the original read-end of the pipe
        close(pipe_fd[0]);

        // Wait for the child process to finish
        wait(0);

        // Execute "wc" command
        execlp("wc", "wc", NULL);
        perror("execlp");
        exit(EXIT_FAILURE);
    }

    return 0;
}
