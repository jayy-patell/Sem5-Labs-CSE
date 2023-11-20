#include <stdio.h>
#include <stdlib.h>

int main()
{
    int m, n;

    m = 5;
    n = 3;

    int alloc[5][3] = {{0, 1, 0},  // P0    // Allocation Matrix
                       {2, 0, 0},  // P1
                       {3, 0, 2},  // P2
                       {2, 1, 1},  // P3
                       {0, 0, 2}}; // P4

    int max[5][3] = {{7, 5, 3},  // P0    // MAX Matrix
                     {3, 2, 2},  // P1
                     {9, 0, 2},  // P2
                     {2, 2, 2},  // P3
                     {4, 3, 3}}; // P4

    int avail[3] = {3, 3, 2}; // Available Resources

    int f[m];
    int ans[m];

    for (int i = 0; i < m; i++)
    {
        f[i] = 0;
    }

    int need[m][n];

    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            need[i][j] = max[i][j] - alloc[i][j];
        }
    }

    int ind = 0; // for ans array

    for (int i = 0; i < 5; i++) // to do entire process agin (since many wont happen in first go)
    {
        for (int j = 0; j < m; j++) // for each process
        {
            if (f[j] == 0) // not been checked before
            {
                int nsflag = 0;             // flag to see if process is safe or not
                for (int k = 0; k < n; k++) // for each resource
                {
                    if (need[j][k] > avail[k])
                    {
                        nsflag = 1; // not safe
                        break;
                    }
                }

                if (nsflag == 0) // safe
                {
                    ans[ind++] = j;
                    for (int y = 0; y < n; y++)
                    {
                        avail[y] += need[j][y]; // update avail with safe process
                    }
                    f[j] = 1; // fin array updates
                }
            }
        }
    }

    // To see if sequence is safe or not
    int sseqflag = 1;

    for (int i = 0; i < m; i++) // will check through all process if still marked 0 then not safe
    {
        printf("%d\t", f[i]);
        if (f[i] == 0)
        {
            sseqflag = 0;
            printf("Not a safe sequence!");
            break;
        }
    }

    if (sseqflag == 1)
    {
        printf("Following code is in a safe sequence:\n");
        for (int i = 0; i < m - 1; i++)
            printf(" P%d ->", ans[i]);
        printf(" P%d", ans[m - 1]);
    }
}
