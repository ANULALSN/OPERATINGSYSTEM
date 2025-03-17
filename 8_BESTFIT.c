#include <stdio.h>

struct Process { int size, flag, holeId; } p[10];
struct Hole { int id, size, actual; } h[10];

void sortHoles(struct Hole h[], int n) { // Sort holes by size (ascending)
    for (int i = 0; i < n - 1; i++)
        for (int j = i + 1; j < n; j++)
            if (h[i].size > h[j].size) {
                struct Hole temp = h[i]; 
                h[i] = h[j]; 
                h[j] = temp;
            }
}

int main() {
    int np, nh;
    printf("Enter number of Holes: "); scanf("%d", &nh);
    for (int i = 0; i < nh; i++) { 
        printf("Size of hole H%d: ", i);
        scanf("%d", &h[i].size);
        h[i].actual = h[i].size; h[i].id = i;
    }
    
    printf("\nEnter number of Processes: "); scanf("%d", &np);
    for (int i = 0; i < np; i++) { 
        printf("Size of process P%d: ", i);
        scanf("%d", &p[i].size);
        p[i].flag = 0;
    }

    for (int i = 0; i < np; i++) {
        sortHoles(h, nh); // Sort before each allocation
        for (int j = 0; j < nh && !p[i].flag; j++)
            if (p[i].size <= h[j].size) {
                p[i].flag = 1; p[i].holeId = h[j].id;
                h[j].size -= p[i].size;
            }
    }

    printf("\n\tBest Fit Allocation\n");
    printf("---------------------------------\n");
    printf("Process\tSize\tAllocated Hole\n");
    printf("---------------------------------\n");
    for (int i = 0; i < np; i++) {
        if (p[i].flag)
            printf("P%d\t%d\tH%d\n", i, p[i].size, p[i].holeId);
        else
            printf("P%d\t%d\tNot allocated\n", i, p[i].size);
    }

    printf("\n---------------------------------\n");
    printf("Hole\tActual\tAvailable\n");
    printf("---------------------------------\n");
    for (int i = 0; i < nh; i++)
        printf("H%d\t%d\t%d\n", h[i].id, h[i].actual, h[i].size);
    
    return 0;
}

