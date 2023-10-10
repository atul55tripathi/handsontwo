#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/msg.h>
#include <sys/stat.h>
#include <time.h>

int main() {
    key_t key;
    int msgid;
    struct msqid_ds msq_info;

    if ((key = ftok("message_queue_key", 'A')) == -1) {
        perror("ftok");
        exit(EXIT_FAILURE);
    }

    msgid = msgget(key, IPC_CREAT | 0744);
    if (msgid == -1) {
        perror("msgget");
        exit(EXIT_FAILURE);
    }

    // Get the attributes of the message queue
    if (msgctl(msgid, IPC_STAT, &msq_info) == -1) {
        perror("msgctl");
        exit(EXIT_FAILURE);
    }

    // Print the message queue attributes
    printf("Access Permissions: %#o\n", msq_info.msg_perm.mode);
    printf("UID: %d\n", msq_info.msg_perm.uid);
    printf("GID: %d\n", msq_info.msg_perm.gid);
    printf("Time of Last Message Sent: %s", ctime(&msq_info.msg_stime));
    printf("Time of Last Message Received: %s", ctime(&msq_info.msg_rtime));
    printf("Time of Last Change: %s", ctime(&msq_info.msg_ctime));
    printf("Size of the Queue: %lu bytes\n", (unsigned long)msq_info.msg_cbytes);
    printf("Number of Messages: %lu\n", (unsigned long)msq_info.msg_qnum);
    printf("Maximum Number of Bytes Allowed: %lu\n", (unsigned long)msq_info.msg_qbytes);
    printf("PID of the Last msgsnd: %d\n", msq_info.msg_lspid);
    printf("PID of the Last msgrcv: %d\n", msq_info.msg_lrpid);

    return 0;
}
