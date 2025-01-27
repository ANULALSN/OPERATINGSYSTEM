#include <stdio.h>

struct process {
    int id, wait, burst, tottime, comp, arrival;
} p[20];

void main() {
    int i, n;
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
    }

    // Calculate waiting time, turnaround time, and completion time
    p[0].wait = 0;  // First process always has wait time 0
    p[0].comp = p[0].arrival + p[0].burst;  // Completion time = arrival time + burst time for the first process
    
    for (i = 1; i < n; i++) {
        // Wait time for process i is the time spent waiting before it starts execution
        if (p[i].arrival > p[i-1].comp) {
            // If the arrival time of the current process is greater than the completion time of the previous process
            p[i].wait = 0; // It will not wait
        } else {
            // Otherwise, it waits until the previous process finishes
            p[i].wait = p[i-1].comp - p[i].arrival;
        }
        
        p[i].comp = p[i].arrival + p[i].wait + p[i].burst;  // Completion time = arrival time + wait time + burst time
    }

    // Calculate total wait time and total turnaround time
    for (i = 0; i < n; i++) {
        p[i].tottime = p[i].comp - p[i].arrival;  // Turnaround time = completion time - arrival time
        totwait += p[i].wait;
        totturnaround += p[i].tottime;
    }

    // Calculate average waiting time and average turnaround time
    avwait = totwait / n;  // Calculate average wait time
    avturn = totturnaround / n;   // Calculate average turnaround time

    // Print process details including Completion Time, Burst Time, and Turnaround Time
    printf("\nID\tBurst Time\tArrival Time\tWait Time\tTurnaround Time\tCompletion Time");
    for (i = 0; i < n; i++) {
        printf("\n%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d", 
               p[i].id, p[i].burst, p[i].arrival, p[i].wait, p[i].tottime, p[i].comp);
    }

    // Print averages with 1 decimal point
    printf("\nAverage Waiting Time: %.1f", avwait);
    printf("\nAverage Turnaround Time: %.1f\n", avturn);
}

