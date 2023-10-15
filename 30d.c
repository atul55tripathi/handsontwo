#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
int main()
{
    int shmid;
    key_t key = ftok(".", 'S'); // Create a unique key

    // Create shared memory segment
    shmid = shmget(key, 1024, 0);
      if (shmctl(shmid, IPC_RMID, NULL) == -1) {
        perror("shmctl (IPC_RMID)");
        exit(EXIT_FAILURE);
    }
printf("shared mem deleted");
return 0;
}
