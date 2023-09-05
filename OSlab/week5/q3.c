// #include<pthread.h>
// #include<stdio.h>
// #include<stdlib.h>

// void* child_thread(void * param) {
// 	int* arr = (int*)param;
// 	int m = arr[0], n = arr[1];
// 	for(int i=m;i<=n;i++){
// 		int flag=0;
// 		for(int j = 1;j<i;j++){
// 			if(i%j!=0){
// 				flag=1;
// 			}
// 		}
// 		if(!flag) printf("%d", i);
// 	}
// }

// int main(){
// 	int n,m;
// 	printf("Enter starting number:");
// 	scanf("%d", &m);
// 	printf("Enter ending number:");
// 	scanf("%d", &n);
// 	int* arr = (int*)calloc(2,sizeof(int));
// 	arr[0] = m; arr[1] = n;

// 	pthread_t thread;
// 	pthread_create( &thread, 0, &child_thread, (void *)arr);

// 	pthread_join(thread, 0);
// }

#include <pthread.h>
#include <stdio.h>

int is_prime(n)
{
    if (n < 2)
        return 0;
    for (int i= 2; i < n; i++)
    {
        if (n % i == 0)
            return 0;
    }
    return 1;
}

void* child_thread( void * param )
{
    int id = is_prime((int)param);
    
    return (void *)id;
}

int main()
{
    int n, s, e;
    pthread_t* threads;
    int *return_value;

    printf("Enter Start: "); 
    // n = 6;
    scanf("%d", &s);

    printf("Enter End: ");
    scanf("%d", &e);
    
    n = e - s + 1;

    threads = (pthread_t*) calloc(n , sizeof(pthread_t));
    return_value = (int*) calloc(n , sizeof(int));

    for (int i = 0; i < n; i ++)
    {
        pthread_create( threads+i, 0, &child_thread, (void*)(s+ i) );
    }

    for ( int i=0; i<n; i++ )
    {
        pthread_join( threads[i], (void**)(return_value+i) );
    }

    // // Result
    for (int i = 0; i < n; i++)
    {
        if (return_value[i])
            printf("%d  ", s+i);
    }    
    printf("\n");

}