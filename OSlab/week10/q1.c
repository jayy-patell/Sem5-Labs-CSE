//Bankers Algo
#include <stdio.h>

int main() {
    int n, m; // Number of processes and resources
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    printf("Enter the number of resources: ");
    scanf("%d", &m);

    int available[3]={3,3,2}; // Available resources
    int maximum[5][3]={7,5,3,
                       3,2,2,
                       9,0,2,
                       2,2,2,
                       4,3,3}; // Maximum demand matrix
    int allocation[5][3]={0,1,0,
                          2,0,0,
                          3,0,2,
                          2,1,1,
                          0,0,2}; // Allocation matrix
    int need[5][3]; // Need matrix

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            need[i][j] = maximum[i][j] - allocation[i][j];
        }
    }

    // Initialize work and finish arrays
    int work[m];
    int finish[n];
    for (int i = 0; i < m; i++) {
        work[i] = available[i];
    }
    for (int i = 0; i < n; i++) {
        finish[i] = 0;
    }

    int safeSequence[n];
    int count = 0;

    // Find a safe sequence
    while (count < n) {
        int found = 0;
        for (int i = 0; i < n; i++) {
            if (finish[i] == 0) {
                int j;
                for (j = 0; j < m; j++) {
                    if (need[i][j] > work[j]) {
                        break;
                    }
                }
                if (j == m) {
                    for (j = 0; j < m; j++) {
                        work[j] += allocation[i][j];
                    }
                    safeSequence[count] = i;
                    finish[i] = 1;
                    count++;
                    found = 1;
                }
            }
        }
        if (found == 0) {
            printf("System is in an unsafe state!\n");
            break;
        }
    }

    if (count == n) {
        printf("System is in a safe state.\nSafe sequence: ");
        for (int i = 0; i < n; i++) {
            printf("P%d ->", safeSequence[i]);
        }
        printf("\n");
        printf("Need allocation table is: \n");
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                printf("%d\t",need[i][j]);
            }
            printf("\n");
        }
    }

    return 0;
}