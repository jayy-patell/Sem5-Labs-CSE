#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>

void* child_thread(void * param) {
	int* arr = (int*)param;
	int n = arr[0];
	int sum = 0;
	for(int i=1;i<n+1;i++){
		if(arr[i]>0) sum += arr[i];
	}
	return (void *)sum;
}

int main(){
	printf("Enter no. of elements: ");
	int n, sum=0;
	scanf("%d", &n);
	int* arr = (int*)calloc(n+1,sizeof(int));
	arr[0]=n;
	printf("Enter elements: ");
	for(int i=1;i<n+1;i++){
		scanf("%d", &arr[i]);
	}

	pthread_t thread;
	pthread_create( &thread, 0, &child_thread, (void *)arr);

	pthread_join(thread, (void*)&sum);
	printf("Sum is: %d", sum);
}