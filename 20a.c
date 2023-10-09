#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>

int main() {
    int fd = open("fifo", O_RDONLY);	//descriptor of fifo
    char buffer[100];
    	
    int size = read(fd, buffer, 100);
    printf("text from FIFO: ");
    printf("%s\n", buffer);
    return 0;
}
