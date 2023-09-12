#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv)
{
	int n;
	int fd[2];
	char buf[1025];
	char *data = "hello... this is sample data";
	pipe(fd);
	write(fd[1], data, strlen(data));
	if ((n = read(fd[0], buf, 1024)) >= 0) {
		buf[n] = 0;
		/* terminate the string */
		printf("read %d bytes from the pipe: \"%s\"\n", n, buf);
	}
	else
		perror("read");
	exit(0);
}


// Pipes are unidirectional byte streams that connect the standard output from one
// process into the standard input of another process. A pipe is created using the
// system call pipe that returns a pair of file descriptors.


// call to the pipe () function which returns an array of
// file descriptors fd[0] and fd [1]. fd [1] connects to the write end of the pipe, and
// fd[0] connects to the read end of the pipe. Anything can be written to the pipe, and
// read from the other end in the order it came in.