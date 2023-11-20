#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int pid;
    int priority;
    int burst_time;
} Process;

typedef struct
{
    Process **process; // array of pointers
    int front;
    int rear;
    int capacity;
} Queue;

Queue *createQueue(int capacity)
{
    Queue *queue = (Queue *)malloc(sizeof(Queue));
    queue->process = (Process **)malloc(capacity * sizeof(Process *));
    queue->capacity = capacity;
    queue->front = queue->rear = -1; // both front and rear made -1
    return queue;
}

void enqueue(Queue *queue, Process *process)
{
    if (queue->rear == queue->capacity - 1)
    {
        printf("Queue is full cannot enqueue");
        return;
    }
    queue->process[++queue->rear] = process;
    if (queue->front == -1)
    {
        queue->front = 0;
    }
}

Process *dequeue(Queue *queue)
{
    if (queue->front == -1)
    {
        return NULL;
    }

    Process *process = queue->process[queue->front]; // return front value

    if (queue->front == queue->rear) // reset to -1
    {
        queue->front = queue->rear = -1;
    }
    else
    {
        queue->front++; // deqeued
    }

    return process;
}

void runFCFS(Queue *queue)
{
    printf("Running FCFS Queue:\n");

    while (queue->front != -1) // Allways there
    {
        Process *process = dequeue(queue); // Simply dequeue

        printf("Process %d running with burst time %d\n", process->pid, process->burst_time);
    }
}

void runRR(Queue *queue, int time_quantum)
{
    printf("Running RR Queue:\n");

    while (queue->front != -1)
    {
        Process *process = dequeue(queue);

        printf("Process %d running with burst time %d\n", process->pid, process->burst_time);

        process->burst_time -= time_quantum; // reducing burst time
        if (process->burst_time > 0)
        {
            printf("Process %d goes back into the queue\n", process->pid);

            enqueue(queue, process);
        }
        else
        {
            free(process);
        }
    }
}

void runPriority(Queue *queue)
{
    printf("Running Priority Queue:\n");

    while (queue->front != -1)
    {
        int highest_priority_index = queue->front;
        int highest_priority = queue->process[highest_priority_index]->priority;

        // Find the process with the highest priority
        for (int i = queue->front + 1; i <= queue->rear; i++)
        {
            if (queue->process[i]->priority > highest_priority)
            {
                highest_priority_index = i;
                highest_priority = queue->process[i]->priority;
            }
        }

        Process *process = queue->process[highest_priority_index];
        printf("Process %d running with burst time %d\n", process->pid, process->burst_time);

        // Swap the processes to move the one with the highest priority to the front
        queue->process[highest_priority_index] = queue->process[queue->front];
        queue->process[queue->front] = process;

        dequeue(queue);

        free(process);
    }
}

int main()
{
    Queue *fcfsQueue = createQueue(10);
    Queue *rrQueue = createQueue(10);
    Queue *priorityQueue = createQueue(10);

    Process *processes[2];
    for (int i = 0; i < 2; i++)
    {
        processes[i] = (Process *)malloc(sizeof(Process));
        processes[i]->pid = i + 1;
        processes[i]->burst_time = (i + 1) * 2;
        processes[i]->priority = i + 1;
    }

    enqueue(fcfsQueue, processes[0]);
    enqueue(fcfsQueue, processes[1]);

    enqueue(rrQueue, processes[0]);
    enqueue(rrQueue, processes[1]);

    enqueue(priorityQueue, processes[0]);
    enqueue(priorityQueue, processes[1]);

    runFCFS(fcfsQueue);
    runRR(rrQueue, 2);
    runPriority(priorityQueue);

    return 0;
}