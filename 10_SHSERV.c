//shared memory writer
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>

#define SHM_SIZE 27
#define SHM_KEY 2013

int main() {
    int shmid;
    char *shm, *s;

    // Create shared memory
    if ((shmid = shmget(SHM_KEY, SHM_SIZE, IPC_CREAT | 0666)) < 0) {
        perror("shmget");
        exit(1);
    }
    printf("Shared memory ID: %d\n", shmid);

    // Attach shared memory
    if ((shm = shmat(shmid, NULL, 0)) == (char *)-1) {
        perror("shmat");
        exit(1);
    }
    
    memset(shm, 0, SHM_SIZE);  // Initialize memory
    s = shm;

    // Write 'a' to 'z' into shared memory
    printf("Writing (a-z) onto shared memory...\n");
    for (char c = 'a'; c <= 'z'; c++) {
        *s++ = c;
    }
    *s = '\0';  // Null-terminate string

    // Wait for client acknowledgment
    while (*shm != '*');

    printf("Client finished reading.\n");

    // Detach and remove shared memory
    if (shmdt(shm) != 0)
        fprintf(stderr, "Could not detach memory segment.\n");

    shmctl(shmid, IPC_RMID, NULL);
    
    return 0;
}

