#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/wait.h>
int main()
{
system("mknod myfifo1 p");
return 0;
}

