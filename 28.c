#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

int main() {
    key_t key;
    int msgid;
    struct msqid_ds msq_info;

    // Generate a unique key for the message queue
    if ((key = ftok("message_queue_key", 'A')) == -1) {
        perror("ftok");
        exit(EXIT_FAILURE);
    }

    // Get the message queue ID
    msgid = msgget(key, IPC_CREAT | 0666);
    if (msgid == -1) {
        perror("msgget");
        exit(EXIT_FAILURE);
    }

    // Get the current attributes of the message queue
    if (msgctl(msgid, IPC_STAT, &msq_info) == -1) {
        perror("msgctl (IPC_STAT)");
        exit(EXIT_FAILURE);
    }

    // Change the permissions (mode) of the message queue
    msq_info.msg_perm.mode = 0644; // Set the desired permission (e.g., read and write for owner and read for others)

    // Apply the changes to the message queue
    if (msgctl(msgid, IPC_SET, &msq_info) == -1) {
        perror("msgctl (IPC_SET)");
        exit(EXIT_FAILURE);
    }

    printf("Message queue permissions changed successfully.\n");

    return 0;
}
