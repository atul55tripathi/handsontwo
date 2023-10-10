#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
int main()
{
key_t key=ftok(".",'a');
int msgid=msgget(key,IPC_CREAT|IPC_EXCL|0744);
printf("key= 0x%x\t msgid= %d",key,msgid);
}

//not stored as regular files through msgget but can be seen though
// ipcs for all or ipcs -q for only message queue
