#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
int main()
{
int fd[2];
pipe(fd);
if (!fork()) {
close(1); // closing standard write
close(fd[0]);	//closing standard read of fd of child
dup(fd[1]); // command to assign lowest possible fd to child, which we freed as stdout as 1
execlp("ls", "ls", "-l", (char*) NULL);	//exec or execlp replaces the process complete with new one
// execlp() write output of "ls -l" to fd-- which actually was to write to stdout
//(write-end of pipe)
}
else {
close(0); // close STDIN
close(fd[1]);	// closing writing end of descriptor
dup(fd[0]); // Duplicate fd[0] to lowest fd value available which is 0
execlp("wc", "wc", (char*) NULL);
// execlp() will read input from fd with value = 0 (read-end of
//pipe) as input to “wc” command and show output to fd with value = 1 =>
//STDOUT
}
return 0;
}
