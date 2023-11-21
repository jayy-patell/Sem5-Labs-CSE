#include <stdio.h>

typedef struct {
	int pid, burst_time, rem_time, qlevel;
} Process;
void enqueue(Process queue[], int *rear, Process p)
{
	queue[++(*rear)]=p;
}
Process dequeue(Process queue[], int *front)
{
	return queue[(*front)++];
}
int isEmpty(int front, int rear)
{
	return front > rear;
}
int main()
{
	int n, time=0;
	Process processes[30];
	Process rr4[30],rr8[30],fcfs[30];
	int front[3] = {0,0,0};
	int rear[3] = {-1,-1,-1};
	printf("Enter number of processes: "); scanf("%d", &n);
	for(int i=0; i<n; i++)
	{
		processes[i].pid = i+1;
		printf("Enter burst time of process %d: ", i+1); scanf("%d", &processes[i].burst_time);
		processes[i].rem_time = processes[i].burst_time;
		processes[i].qlevel=1;
		enqueue(rr4, &rear[0],processes[i]);
	}
	while(1)
	{
		if(!isEmpty(front[0],rear[0]))
		{
			Process curr = dequeue(rr4,&front[0]);
			int time_slice = curr.rem_time<4 ? curr.rem_time : 4;
			curr.rem_time -= time_slice;
			time+=time_slice;
			if(curr.rem_time>0)
			{
				curr.qlevel=2;
				enqueue(rr8,&rear[1],curr);
			}
			else printf("Process %d completed in level 1", curr.pid);
		}
		else if(!isEmpty(front[1],rear[1]))
		{
			Process curr = dequeue(rr8,&front[1]);
			int time_slice = curr.rem_time<8 ? curr.rem_time : 8;
			curr.rem_time -= time_slice;
			time+=time_slice;
			if(curr.rem_time>0)
			{
				curr.qlevel=3;
				enqueue(fcfs,&rear[2],curr);
			}
			else printf("Process %d completed in level 2", curr.pid);
		}
		else if(!isEmpty(front[2],rear[2]))
		{
			Process curr = dequeue(fcfs,&front[2]);
			time+=curr.rem_time;
			curr.rem_time=0;
			printf("Process %d completed in level 3", curr.pid);
		}
		else break;
	}
	return 0;
}