#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/wait.h>

int main()
{
int fd1[2],fd2[2];
pipe(fd1);
pipe(fd2);
if(!fork()){
dup2(fd1[1],1);
close(fd1[0]);
close(fd2[0]);
close(fd2[1]);
execlp("ls","ls","-l",(char*)NULL);// execlp replaces all remaining of child hence it will not go further
}
else{
if(!fork()){
dup2(fd2[1],1);
dup2(fd1[0],0);
close(fd1[1]);
close(fd2[0]);
execlp("grep","grep","^d",(char*)NULL);// termination of another child after placing the output in pipe
}
else{
dup2(fd2[0],0);
close(fd2[1]);
close(fd1[0]);
close(fd1[1]);
execlp("wc","wc",(char*)NULL);
}
}
return 0;
}

