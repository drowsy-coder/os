#include <stdio.h>

int main() {
    int n, bt[20], p[20], wt[20], tat[20], i, j, pos, temp;
    float avg_wt, avg_tat, total = 0;

    printf("Enter number of processes:");
    scanf("%d", &n);

    printf("Enter Burst Time:\n");
    for (i = 0; i < n; i++) {
        printf("P[%d]:", i + 1);
        scanf("%d", &bt[i]);
        p[i] = i + 1;
    }

    for (i = 0; i < n; i++) {
        pos = i;
        for (j = i + 1; j < n; j++) {
            if (bt[j] < bt[pos])
                pos = j;
        }

        temp = bt[i];
        bt[i] = bt[pos];
        bt[pos] = temp;

        temp = p[i];
        p[i] = p[pos];
        p[pos] = temp;
    }

    wt[0] = 0;

    for (i = 1; i < n; i++) {
        wt[i] = 0;
        for (j = 0; j < i; j++)
            wt[i] += bt[j];

        total += wt[i];
    }

    avg_wt = total / n;
    total = 0;

    printf("\nProcess\t    Burst Time    \tWaiting Time\tTurnaround Time");
    for (i = 0; i < n; i++) {
        tat[i] = bt[i] + wt[i];
        total += tat[i];
        printf("\nP[%d]\t\t  %d\t\t    %d\t\t\t%d", p[i], bt[i], wt[i], tat[i]);
    }

    avg_tat = total / n;
    printf("\n\nAverage Waiting Time=%.2f", avg_wt);
    printf("\nAverage Turnaround Time=%.2f\n", avg_tat);

    return 0;
}
