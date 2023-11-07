//FCFS

 

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

void fcfs(struct DSA* requests, int num_requests) {
    int current_cylinder = 0;
    int total_seek_time = 0;

    printf("FCFS Disk Scheduling Algorithm:\n");
    printf("Order of execution:\n");

    for (int i = 0; i < num_requests; i++) {
        int seek = abs(current_cylinder - requests[i].cylinder);
        total_seek_time += seek;
        printf("Request ID: %d, Process ID: %d, Seek Time: %d\n", requests[i].request_id, requests[i].process_id, seek);
        current_cylinder = requests[i].cylinder;
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

    fcfs(requests, num_requests);

    free(requests);
    return 0;
}

 