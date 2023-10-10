#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

int main() {
    key_t key;
    int msgid;

    if ((key = ftok("message_queue_key", 'A')) == -1) 
    {
        perror("ftok");
        exit(EXIT_FAILURE);
    }
        msgid = msgget(key, IPC_CREAT | 0666);
    if (msgid == -1) {
        perror("msgget");
        exit(EXIT_FAILURE);
    }
	
    if (msgctl(msgid, IPC_RMID, NULL) == -1) 
    {
        perror("msgctl (IPC_RMID)");
        exit(EXIT_FAILURE);
    }

    printf("Message queue removed successfully.\n");

    return 0;
}
