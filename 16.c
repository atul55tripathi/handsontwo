#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    int fd1[2], fd2[2];
    char buff1[20], buff2[20];

    if (pipe(fd1) == -1 || pipe(fd2) == -1) {
        perror("Pipe creation failed");
        exit(EXIT_FAILURE);
    }

    if (!fork()) {
        close(fd1[0]); // Close read-end of fd1 for child
        close(fd2[1]); // Close write-end of fd2 for child

        printf("Enter message to parent: ");
        scanf(" %[^\n]", buff1);

        write(fd1[1], buff1, sizeof(buff1));
        read(fd2[0], buff2, sizeof(buff2));

        printf("Message from parent: %s\n", buff2);
    } else {
        close(fd1[1]); // Close write-end of fd1 for parent
        close(fd2[0]); // Close read-end of fd2 for parent

        read(fd1[0], buff1, sizeof(buff1));
        printf("Message from child: %s\n", buff1);

        printf("Enter message to child: ");
        scanf(" %[^\n]", buff2);

        write(fd2[1], buff2, sizeof(buff2));
    }

    return 0;
}

