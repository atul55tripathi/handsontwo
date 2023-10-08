#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
int main()
{
int pipefd[2];	//0 for read and 1 for write file descriptors
pid_t child;

if(pipe(pipefd)==-1)	//pipe return 0 on success and -1 on failure
{
perror("pipe not created");
exit(EXIT_FAILURE);
}
if((child=fork())==-1)	// fork returnn -1 on failure
{
perror("enable to create child proc");
exit(EXIT_FAILURE);
}
if(child==0)
{
close(pipefd[0]);	//closing the read end from child as we want to write to pipe
char buf[]="to the pipe";
write(pipefd[1],buf,sizeof(buf));
close(pipefd[1]);
exit(EXIT_SUCCESS);
}
else{
close(pipefd[1]);	//closing write of parent to receive from pipe
char buf[256];
int rd=read(pipefd[0],buf,sizeof(buf));
if(rd==-1)	// read return -1 on no read
{		
perror("reading error");
exit(EXIT_FAILURE);
}
write(1,buf,rd);
close(pipefd[0]);
}
return 0;
}

