#include <sys/types.h>
#include <sys/stat.h>

int mkfifo(const char *filename, mode_t mode);

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>

int main()
{
	int res = mkfifo("/tmp/my_fifo", 0773);
	if (res == 0) printf("FIFO created\n");
	exit(EXIT_SUCCESS);
}

// We can look for the pipe with
// $ ls -lF /tmp/my_fifo
// prwxr-xr-x 1 rick users 0 July 10 14:55 /tmp/my_fifo|

// Notice that the first character of output is a p, indicating a pipe. The | symbol at the end
// is added by the ls command’s -F option and also indicates a pipe.