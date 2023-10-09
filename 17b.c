#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    int pipe_fd[2];
    pid_t child_pid;

   
    if (pipe(pipe_fd) == -1) {
        perror("Pipe creation failed");
        exit(EXIT_FAILURE);
    }

    if ((child_pid = fork()) == -1) {
        perror("Fork failed");
        exit(EXIT_FAILURE);
    }

    if (child_pid == 0) {
        // entering child process
        // closing read side of pipe
        close(pipe_fd[0]);
        

        // setting write side of pipe to 1 meaning stdout/write/1
        dup2(pipe_fd[1], STDOUT_FILENO);

        

        // Execute "ls -l" command
        execlp("ls", "ls", "-l", NULL);
        perror("execlp");
        exit(EXIT_FAILURE);
    } else {
        // Parent process
        // Close write-end of the pipe
        close(pipe_fd[1]);
        

        // Redirect stdin to the read-end of the pipe
        dup2(pipe_fd[0], STDIN_FILENO);

        

        // Execute "wc" command
        execlp("wc", "wc", NULL);
        perror("execlp");
        exit(EXIT_FAILURE);
    }

    return 0;
}

