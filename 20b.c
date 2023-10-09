#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>

int main() {
    int fd = open("fifo", O_WRONLY);// descriptor of fifo
    char buffer[100];
    printf("Enter a message for the pass to pipe: ");
    scanf(" %[^\n]", buffer);
    write(fd, buffer, sizeof(buffer));// writing to the pipe
    return 0;
}
