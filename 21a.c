#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
int main()
{
int fd1,fd2;
fd1=open("fifo1",O_RDONLY);
fd2=open("fifo2",O_WRONLY);
char buf1[20],buf2[20];
printf("send to other program: ");
scanf(" %[^\n]", buf1);
write(fd2,buf1,20);
printf("\nnow waiting for text from program 2\n");
read(fd1,buf2,20);
printf("the text from prgo 2 is:%s\n",buf2);
close(fd1);
close(fd2);
return 0;
}
