#include<stdio.h>

void main() {
    int burstTime[20], process[20], waitingTime[20], turnaroundTime[20], priority[20];
    int i, j, numberOfProcesses, total = 0, position, temp;
    float averageWaitTime, averageTurnaroundTime;

    printf("Enter Total Number of Processes:");
    scanf("%d", &numberOfProcesses);

    printf("\nEnter Burst Time and Priority\n");
    for(i = 0; i < numberOfProcesses; i++) {
        printf("\nP[%d]\n", i + 1);
        printf("Burst Time:");
        scanf("%d", &burstTime[i]);
        printf("Priority:");
        scanf("%d", &priority[i]);
        process[i] = i + 1;
    }

    // Sorting burst time, priority and process number in ascending order using selection sort
    for(i = 0; i < numberOfProcesses; i++) {
        position = i;
        for(j = i + 1; j < numberOfProcesses; j++) {
            if(priority[j] < priority[position]) {
                position = j;
            }
        }

        temp = priority[i];
        priority[i] = priority[position];
        priority[position] = temp;

        temp = burstTime[i];
        burstTime[i] = burstTime[position];
        burstTime[position] = temp;

        temp = process[i];
        process[i] = process[position];
        process[position] = temp;
    }

    waitingTime[0] = 0; //waiting time for first process is zero

    //calculate waiting time
    for(i = 1; i < numberOfProcesses; i++) {
        waitingTime[i] = 0;
        for(j = 0; j < i; j++)
            waitingTime[i] += burstTime[j];

        total += waitingTime[i];
    }

    averageWaitTime = (float)total / numberOfProcesses;
    total = 0;

    printf("\nProcess\t    Burst Time    \tWaiting Time\tTurnaround Time");
    for(i = 0; i < numberOfProcesses; i++) {
        turnaroundTime[i] = burstTime[i] + waitingTime[i];
        total += turnaroundTime[i];
        printf("\nP[%d]\t\t  %d\t\t    %d\t\t\t%d", process[i], burstTime[i], waitingTime[i], turnaroundTime[i]);
    }

    averageTurnaroundTime = (float)total / numberOfProcesses;
    printf("\n\nAverage Waiting Time=%.2f", averageWaitTime);
    printf("\nAverage Turnaround Time=%.2f\n", averageTurnaroundTime);
}
