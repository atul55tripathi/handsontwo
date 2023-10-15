#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>


int main() {
    int shmid;
    key_t key = ftok(".", 'S'); // Create a unique key

    shmid = shmget(key, 1024, IPC_CREAT | 0666); // Create a shared memory segment
    if (shmid == -1) {
        perror("shmget");
        exit(EXIT_FAILURE);
    }

    // Attach the shared memory segment for writing
    char *tomem = (char *)shmat(shmid, NULL, SHM_RDONLY);
    if (tomem == (char *)(-1)) {
        perror("shmat");
        exit(EXIT_FAILURE);
    }

    char buf[20];
    printf("Enter the text to shared memory: ");
    scanf(" %[^\n]", buf); // Allow spaces in the input

    // Copy the input to the shared memory
    strcpy(tomem, buf);

    // Detach the shared memory
    if (shmdt(tomem) == -1) {
        perror("shmdt");
        exit(EXIT_FAILURE);
    }

    return 0;
}

