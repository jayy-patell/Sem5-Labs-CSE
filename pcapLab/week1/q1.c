#include<stdio.h>
#include"mpi.h"
#include<math.h>

int power(int a,int b){
	int result=1;
	while(b--){
		result = result*a;
	}
	return result;
}

int main(int argc, char* argv[]){
	int rank,size;
	int x=3;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	int result = power(x,rank);
	printf("my rank is %d in total %d processes\nmy power is %d^%d = %d\n", rank,size,x,rank,result);
	MPI_Finalize();
	return 0;
}