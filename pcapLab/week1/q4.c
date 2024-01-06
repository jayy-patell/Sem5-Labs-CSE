#include<stdio.h>
#include"mpi.h"


char toggleChars(char c)
{
    if (c >= 'A' && c <= 'Z')
        c = c + 'a' - 'A';
    else if (c >= 'a' && c <= 'z')
        c = c + 'A' - 'a';
    return c;
}

int main(int argc, char* argv[]){
	int rank,size;
	char str[10] = "HeLLO";
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	printf("for rank %d - %c to %c\n",rank,str[rank],toggleChars(str[rank]));
	str[rank] = toggleChars(str[rank]);
	printf("%s",str);
	MPI_Finalize();
	return 0;
}