// just use echo hi> myfifo and prog will recieve like cat <echo
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
int main(){
int fd;
fd=open("myfifo",O_RDONLY);
    fd_set readSet;
    struct timeval timeout;

    // Initialize the read file descriptor set
    FD_ZERO(&readSet);
    FD_SET(fd, &readSet);

    // 10 seconds is the wait time
    timeout.tv_sec = 10;
    timeout.tv_usec = 0;

    // Use select to wait for data or timeout
    int selectResult = select(fd + 1, &readSet, NULL, NULL, &timeout);

    if (selectResult == 0) 			//select returns -1 on error and 0 on no data recieve withing given time
    {      
      printf("Timeout: No data received within 10 seconds.\n");
    } 
    else 
    {
        char buffer[256];
        ssize_t bytesRead = read(fd, buffer, sizeof(buffer));
        if (bytesRead == -1) {
            perror("read");
            close(fd);
            exit(EXIT_FAILURE);
        }
        buffer[bytesRead] = '\0';
        printf("Received data from FIFO: %s\n", buffer);
    }

    close(fd);

    return 0;
}

