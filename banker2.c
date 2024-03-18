#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define P 5
#define R 3

void checkSafety(int processes[], int avail[], int max[][R], int alloc[][R], FILE *fptr) {
    int need[P][R];
    for (int i = 0; i < P; i++) {
        for (int j = 0; j < R; j++) {
            need[i][j] = max[i][j] - alloc[i][j];
        }
    }
    bool finish[P];
    int safeSeq[P];
    for (int i = 0; i < P; i++) {
        finish[i] = false;
    }
    int work[R];
    for (int i = 0; i < R; i++) {
        work[i] = avail[i];
    }
    int count = 0;
    while (count < P) {
        bool found = false;
        for (int p = 0; p < P; p++) {
            if (!finish[p]) {
                int j;
                for (j = 0; j < R; j++)
                    if (need[p][j] > work[j])
                        break;
                if (j == R) {
                    for (int k = 0; k < R; k++)
                        work[k] += alloc[p][k];
                    safeSeq[count++] = p;
                    finish[p] = true;
                    found = true;
                }
            }
        }
        if (!found) {
            fprintf(fptr, "System is not in a safe state\n");
            return;
        }
    }
    fprintf(fptr, "System is in a safe state.\nSafe sequence is: ");
    for (int i = 0; i < P; i++) {
        fprintf(fptr, "%d ", safeSeq[i]);
    }
    fprintf(fptr, "\n");
}

int main() {
    FILE *fptr;
    fptr = fopen("bankers_log.txt", "w");
    if(fptr == NULL) {
        printf("Error!");
        exit(1);
    }

    int processes[] = {0, 1, 2, 3, 4};
    int avail[] = {3, 3, 2};
    int max[P][R] = {
        {7, 5, 3},
        {3, 2, 2},
        {9, 0, 2},
        {2, 2, 2},
        {4, 3, 3}
    };
    int alloc[P][R] = {
        {0, 1, 0},
        {2, 0, 0},
        {3, 0, 2},
        {2, 1, 1},
        {0, 0, 2}
    };
    checkSafety(processes, avail, max, alloc, fptr);
    fclose(fptr);
    return 0;
}
