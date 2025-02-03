#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 5

int mutex = 1;  // Mutex to control access to the buffer
int empty = BUFFER_SIZE;  // Number of empty slots in the buffer
int full = 0;  // Number of filled slots in the buffer
int buffer[BUFFER_SIZE];  // Buffer to store items
int in = 0;  // Index for the next item to be produced
int out = 0;  // Index for the next item to be consumed

void wait(int *s) {
    while (*s <= 0);  // Busy wait until the semaphore is positive
    (*s)--;
}

void signal(int *s) {
    (*s)++;
}

void producer() {
    int item;
    if (empty == 0) {
        printf("Buffer is full! Cannot produce.\n");
        return;
    }

    printf("Enter an item: ");
    scanf("%d", &item);

    wait(&empty);  // Wait if the buffer is full
    wait(&mutex);  // Enter critical section

    buffer[in] = item;  // Add item to the buffer
    in = (in + 1) % BUFFER_SIZE;  // Move the producer index

    signal(&mutex);  // Exit critical section
    signal(&full);  // Increment the count of full slots

    printf("Produced item: %d\n", item);
}

void consumer() {
    if (full == 0) {
        printf("Buffer is empty! Cannot consume.\n");
        return;
    }

    wait(&full);  // Wait if the buffer is empty
    wait(&mutex);  // Enter critical section

    int item = buffer[out];  // Consume item from the buffer
    out = (out + 1) % BUFFER_SIZE;  // Move the consumer index

    signal(&mutex);  // Exit critical section
    signal(&empty);  // Increment the count of empty slots

    printf("Consumed item: %d\n", item);
}

int main() {
    int choice;
    printf("1. Producer\n2. Consumer\n3. Exit\n");
    while (1) {
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                producer();
                break;
            case 2:
                consumer();
                break;
            case 3:
                exit(0);
            default:
                printf("Invalid choice!\n");
        }
    }

    return 0;
}
