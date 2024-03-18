#include <stdio.h>

int main() {
    int n, bt[20], wt[20], tat[20], i, j;
    float avg_wt, avg_tat, total = 0;

    printf("Enter total number of processes(maximum 20):");
    scanf("%d", &n);

    printf("\nEnter Process Burst Time\n");
    for (i = 0; i < n; i++) {
        printf("P[%d]:", i + 1);
        scanf("%d", &bt[i]);
    }

    wt[0] = 0;    

    for (i = 1; i < n; i++) {
        wt[i] = 0;
        for (j = 0; j < i; j++)
            wt[i] += bt[j];
    }

    printf("\nProcess\t\tBurst Time\tWaiting Time\tTurnaround Time");

    for (i = 0; i < n; i++) {
        tat[i] = bt[i] + wt[i];
        total += wt[i];
        printf("\nP[%d]\t\t%d\t\t%d\t\t%d", i + 1, bt[i], wt[i], tat[i]);
    }

    avg_wt = total / n;      
    total = 0;

    for (i = 0; i < n; i++)
        total += tat[i];
    avg_tat = total / n;    
    printf("\n\nAverage Waiting Time=%f", avg_wt);
    printf("\nAverage Turnaround Time=%f\n", avg_tat);

    return 0;
}
