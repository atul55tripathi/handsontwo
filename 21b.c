#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
int main()
{
int fd1,fd2;
fd1=open("fifo1",O_WRONLY);
fd2=open("fifo2",O_RDONLY);
char buf1[20],buf2[20];
printf("the information from prog 1:");
read(fd2,buf2,20);
printf("%s",buf2);
printf("\nenter the info to send to prog 1:");
scanf("%[^\n]",buf1);
write(fd1,buf1,20);
close(fd1);
close(fd2);
return 0;
}
