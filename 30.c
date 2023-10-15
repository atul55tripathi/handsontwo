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

    shmid = shmget(key, 1024, IPC_CREAT | 0666);// creating shared mem segment
    if (shmid == -1) {
        perror("shmget");
        exit(EXIT_FAILURE);
    }
    char *tomem= (char*)shmat(shmid,NULL,0);
    char buf[20];
    printf("enter the text to shared mem:%s",buf);
    scanf("%s",buf);
    strcpy(tomem,buf);
    
    
    return 0; 
}
    
