#include<stdio.h>
#include"mpi.h"

int main(int argc, char* argv[]){
	int rank,size,x=6,y=3;
	double result=0.0;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	switch(rank){
		case 0:{
			result = x+y;
			printf("Addition: %d+%d = %.1f\n",x,y,result); break;
		}
		case 1:{
			result = x/y;
			printf("Division: %d/%d = %.1f\n",x,y,result); break;
		}
		case 2:{
			result = x-y;
			printf("Subtraction: %d+%d = %.1f\n",x,y,result); break;
		}
		case 3:{
			result = x*y;
			printf("Multiplication: %d+%d = %.1f\n",x,y,result); break;
		}
		default: printf("only 4 operations till now. medieval calc.\n");
	}
	MPI_Finalize();
	return 0;
}