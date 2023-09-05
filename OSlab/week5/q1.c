// #include<pthread.h>
// #include<stdio.h>
// #include<stdlib.h>

// void* child_thread(void * param) {
// 	int* arr = (int*)param;
// 	arr[0] = 0; arr[1] = 1; arr[2] = 1;
// 	printf("%d",sizeof(arr)/sizeof(arr[0]));
// 	for(int i=2;i<sizeof(arr)/sizeof(arr[0]);i++){
// 		arr[i] = arr[i-1]+arr[i-2];
// 	}
// 	printf("%d",sizeof(arr)/sizeof(arr[0]));
// 	return (void *)arr;
// }

// int main(){
// 	printf("Enter the no. of FibNUm you want: ");
// 	int n;
// 	scanf("%d", &n);
// 	int* arr = (int*)calloc(n,sizeof(int));

// 	pthread_t thread;
// 	pthread_create( &thread, 0, &child_thread, (void *)arr);

// 	pthread_join(thread, (void*)&arr);
// 	for(int i=0;i<n;i++){
// 		printf("%d", arr[i]);
// 	}
// }


#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>

void* child_thread(void * param) {
	int* arr = (int*)param;
	int n = arr[0];
	arr[1]=0; arr[2]=1;
	for(int i=3;i<n+1;i++){
		arr[i] = arr[i-1]+arr[i-2];
	}
	return (void *)arr;
}

int main(){
	printf("Enter the no. of FibNUm you want: ");
	int n;
	scanf("%d", &n);
	int* arr = (int*)calloc(n+1,sizeof(int));
	arr[0] = n;

	pthread_t thread;
	pthread_create( &thread, 0, &child_thread, (void *)arr);

	pthread_join(thread, (void*)&arr);
	for(int i=1;i<n+1;i++){
		printf("%d", arr[i]);
	}
}