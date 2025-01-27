#include <stdio.h>
#include <stdbool.h>

struct process {
    int id, wait, burst, tottime, comp, arrival;
    bool completed; // To mark whether the process is completed
} p[20];

void main() {
    int n, i, j, completed = 0, time = 0, minBurst;
    float totwait = 0, totturnaround = 0, avwait, avturn;

    // Input number of processes
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    // Input details for each process
    for (i = 0; i < n; i++) {
        printf("\nEnter process ID: ");
        scanf("%d", &p[i].id);
        printf("Enter process arrival time: ");
        scanf("%d", &p[i].arrival);
        printf("Enter process burst time: ");
        scanf("%d", &p[i].burst);
        p[i].wait = 0; // Initialize wait time
        p[i].comp = 0; // Initialize completion time
        p[i].tottime = 0; // Initialize turnaround time
        p[i].completed = false; // Mark process as not completed
    }

    // SJF Scheduling Logic
    while (completed < n) {
        int shortest = -1; // Index of the process with the shortest burst time
        minBurst = 9999;   // Start with a very high burst time

        // Find the process with the shortest burst time that has arrived and is not completed
        for (i = 0; i < n; i++) {
            if (p[i].arrival <= time && !p[i].completed && p[i].burst < minBurst) {
                minBurst = p[i].burst;
                shortest = i;
            }
        }

        if (shortest != -1) {
            // Process the selected shortest job
            time += p[shortest].burst; // Advance time by the burst time of the selected process
            p[shortest].comp = time;  // Completion time
            p[shortest].tottime = p[shortest].comp - p[shortest].arrival; // Turnaround time
            p[shortest].wait = p[shortest].tottime - p[shortest].burst;   // Wait time
            p[shortest].completed = true; // Mark the process as completed

            // Update totals
            totwait += p[shortest].wait;
            totturnaround += p[shortest].tottime;
            completed++;
        } else {
            // If no process is ready to execute, advance time
            time++;
        }
    }

    // Calculate averages
    avwait = totwait / n;
    avturn = totturnaround / n;

    // Print process details
    printf("\nID\tBurst Time\tArrival Time\tWait Time\tTurnaround Time\tCompletion Time");
    for (i = 0; i < n; i++) {
        printf("\n%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d", 
               p[i].id, p[i].burst, p[i].arrival, p[i].wait, p[i].tottime, p[i].comp);
    }

    // Print averages with 1 decimal point
    printf("\nAverage Waiting Time: %.1f", avwait);
    printf("\nAverage Turnaround Time: %.1f\n", avturn);
}

