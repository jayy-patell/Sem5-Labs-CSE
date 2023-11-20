#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

struct DSA
{
    int request_id;
    int cylinder;
};

void FCFS(struct DSA *requests, int num_requests)
{
    int current_cylinder = 0;
    int total_movement = 0;
    for (int i = 0; i < num_requests; i++)
    {
        total_movement += abs(current_cylinder - requests[i].cylinder);
        current_cylinder = requests[i].cylinder;
        printf("Request ID:%d,cylinder:%d\n", requests[i].request_id, requests[i].cylinder);
    }

    printf("Total head movement:%d\n", total_movement);
}

void SSTF(struct DSA *requests, int num_requests)
{
    int current_cylinder = 0;
    int total_movement = 0;
    int done[num_requests];

    for (int i = 0; i < num_requests; i++)
    {
        done[i] = 0;
    }

    for (int i = 0; i < num_requests; i++)
    {
        int min_distance = INT_MAX;
        int next_request = -1;

        for (int j = 0; j < num_requests; j++)
        {
            if (!done[j] && i != j)
            {
                int distance = abs(current_cylinder - requests[j].cylinder);

                if (distance < min_distance)
                {
                    min_distance = distance;
                    next_request = j;
                }
            }
        }

        total_movement += min_distance;

        current_cylinder = requests[next_request].cylinder;
        done[next_request] = 1;

        printf("Request : %d, cylinder : %d\n", requests[next_request].request_id, requests[next_request].cylinder);

        printf("Total movements:%d\n", total_movement);
    }
}

int main()
{
    int num_requests = 5;
    struct DSA requests[] = {{1, 200},
                             {2, 75},
                             {3, 100},
                             {4, 20},
                             {5, 60}};

    FCFS(requests, num_requests);
    printf("---------------------------------------------\n");
    SSTF(requests, num_requests);
}