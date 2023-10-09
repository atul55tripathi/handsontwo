#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
int main()
{
mknod("mkfifo3",S_IFIFO| 0666,0);
return 0;
}
