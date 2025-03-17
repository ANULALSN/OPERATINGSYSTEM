//shared memory reader
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SHM_SIZE 27
#define SHM_KEY 2013

int main() {
    int shmid;
    char *shm, *s;

    // Access shared memory
    if ((shmid = shmget(SHM_KEY, SHM_SIZE, 0666)) < 0) {
        printf("Server not started\n");
        exit(1);
    }
    printf("Accessing shared memory ID: %d\n", shmid);

    // Attach shared memory
    if ((shm = shmat(shmid, NULL, 0)) == (char *)-1) {
        perror("shmat");
        exit(1);
    }

    // Read and print contents
    printf("Shared memory contents:\n");
    for (s = shm; *s != '\0'; s++)
        putchar(*s);
    
    putchar('\n');

    // Signal server that reading is done
    *shm = '*';

    return 0;
}

