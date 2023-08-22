//Examaple of wait()

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
int main()
{
	int status;
	pid_t pid;
	pid = fork();
	if(pid = -1)
		printf("\nERROR child not created");
	else if (pid == 0) /* child process */
	{
		printf("\n I'm the child!");
		exit(0);
	}
	else /* parent process */
	{
		pid = wait(&status);
		printf("\n I'm the parent!");
		printf("\n Child returned: %d\n", status);
	}
	return 0;
}


/*A few notes on this program:
wait(&status) causes the parent to sleep until the child process has finished execution.
The exit status of the child is returned to the parent.*/