//SSTF

 

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include<limits.h>

// Structure to represent a disk request
struct DSA {
    int request_id;
    int arrival_time_stamp;
    int cylinder;
    int address;
    int process_id;
};

void sstf(struct DSA* requests, int num_requests) {
    int current_cylinder = 0;
    int total_seek_time = 0;

    printf("SSTF Disk Scheduling Algorithm:\n");
    printf("Order of execution:\n");

    int completed[num_requests];
    for (int i = 0; i < num_requests; i++) {
        completed[i] = 0;
    }

    for (int i = 0; i < num_requests; i++) {
        int min_seek = INT_MAX;
        int next_request = -1;

        for (int j = 0; j < num_requests; j++) {
            if (!completed[j]) {
                int seek = abs(current_cylinder - requests[j].cylinder);
                if (seek < min_seek) {
                    min_seek = seek;
                    next_request = j;
                }
            }
        }

        total_seek_time += min_seek;
        printf("Request ID: %d, Process ID: %d, Seek Time: %d\n", requests[next_request].request_id, requests[next_request].process_id, min_seek);
        current_cylinder = requests[next_request].cylinder;
        completed[next_request] = 1;
    }

    printf("Total Seek Time: %d\n", total_seek_time);
}

int main() {
    int num_requests;
    printf("Enter the number of disk requests: ");
    scanf("%d", &num_requests);

    struct DSA* requests = (struct DSA*)malloc(num_requests * sizeof(struct DSA));

    printf("Enter the disk requests (request_id, arrival_time_stamp, cylinder, address, process_id):\n");
    for (int i = 0; i < num_requests; i++) {
        scanf("%d %d %d %d %d", &requests[i].request_id, &requests[i].arrival_time_stamp, &requests[i].cylinder, &requests[i].address, &requests[i].process_id);
    }

    sstf(requests, num_requests);

    free(requests);
    return 0;
}
