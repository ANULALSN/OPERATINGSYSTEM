#include <stdio.h>
#include <string.h>

int num = 0, len[10], str[10]; 
char fid[10][4], a[20][4];  // a[20][4] stores file names or empty strings

void directory() {
    printf("\nFile\tStart\tLength\n");
    for (int i = 0; i < num; i++)
        printf("%-4s\t%3d\t%6d\n", fid[i], str[i], len[i]);
}

void display() {
    printf("\nDisk Space:\n");
    for (int i = 0; i < 20; i++) printf("%4d", i);
    printf("\n");
    for (int i = 0; i < 20; i++) printf("%4s", (a[i][0] == '\0') ? "." : a[i]); 
    printf("\n");
}

int main() {
    char id[4];
    int st, nb, ch;

    // Initialize disk space array with empty strings
    for (int i = 0; i < 20; i++) strcpy(a[i], "");

    printf("Disk space before allocation:\n");
    display();

    do {
        printf("\nEnter file name (max 3 characters): ");
        scanf("%3s", id); // Prevent buffer overflow
        printf("Enter the start block: ");
        scanf("%d", &st);
        printf("Enter number of blocks: ");
        scanf("%d", &nb);

        if (st < 0 || st + nb > 20) {
            printf("Requirement exceeds range.\n");
            continue;
        }

        int flag = 1;
        for (int i = st; i < st + nb; i++) {
            if (a[i][0] != '\0') { // Check if the block is occupied
                flag = 0;
                break;
            }
        }

        if (!flag) {
            printf("Contiguous allocation not possible.\n");
            continue;
        }

        strcpy(fid[num], id);
        len[num] = nb;
        str[num] = st;

        for (int i = st; i < st + nb; i++) strcpy(a[i], id);
        printf("Allocation done.\n");
        num++;

        printf("Any more allocation? (1. Yes, 2. No): ");
        scanf("%d", &ch);
    } while (ch == 1);

    printf("\nContiguous Allocation:\n");
    directory();
    printf("\nDisk space after allocation:\n");
    display();

    return 0;
}

