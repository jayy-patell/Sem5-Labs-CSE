#include <stdio.h>
#include <stdlib.h>
#define SIZE 4
#define REFS 20
typedef struct
{
    int pgno;
    int refno;
} PgTableEntry;
void initialize(PgTableEntry pgTable[])
{
    for (int i = 0; i < SIZE; i++)
    {
        pgTable[i].pgno = -1;
        pgTable[i].refno = 0;
    }
}
void display(PgTableEntry pgTable[])
{
    printf("Page Table\n");
    for (int i = 0; i < SIZE; i++)
    {
        if (pgTable[i].pgno != -1)
            printf("Entry: %d, Page: %d, RefBit: %d\n", i, pgTable[i].pgno, pgTable[i].refno);
    }
}
int findPage(PgTableEntry pgTable[], int pgno)
{
    for (int i = 0; i < SIZE; i++)
        if (pgTable[i].pgno == pgno)
            return i;
    return -1;
}
int main()
{
    PgTableEntry pgTable[SIZE];
    int pgRefs[REFS] = {1, 2, 3, 4, 1, 2, 5, 1, 2, 3, 4, 5, 2, 3, 1, 5, 4, 3, 2, 1};
    int faults = 0, hits = 0;
    initialize(pgTable);
    for (int i = 0; i < REFS; i++)
    {
        int pgno = pgRefs[i];
        int pgIndex = findPage(pgTable, pgno);
        if (pgIndex != -1)
        {
            pgTable[pgIndex].refno = 0;
            hits++;
            for (int j = 0; j < SIZE; j++)
            {
                if (j != pgIndex)
                    pgTable[j].refno++;
            }
        }
        else
        {
            faults++;
            int j, highest_refno = 0, highest = 0;
            for (j = 0; j < SIZE; j++)
            {
                if (pgTable[j].refno > highest_refno)
                {
                    highest_refno = pgTable[j].refno;
                    highest = j;
                }
                pgTable[j].refno++;
            }
            pgTable[highest].pgno = pgno; // Replace the page with highest refno
            pgTable[highest].refno = 0;   // Reset the refno
        }
        display(pgTable);
    }
    printf("Total Page Faults: %d\n", faults);
    printf("Hit Ratio: %.2f\n", (float)hits / REFS);
    return 0;
}