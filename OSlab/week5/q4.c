#include <pthread.h>
#include <stdio.h>

struct Args{
    int* arr;
    int n;
    int f;
};

typedef struct Args Args;

void* child_thread(void * args)
{
    int sum = 0;

    for (int  i = 0; i < ((Args *)args)->n ; i++)
    {
        if (i % 2 == (((Args *)args)->f))
            sum += ((Args *)args)->arr[i];
    }

    return (void *)sum;
}    

int main()
{
    int n, *arr;
    pthread_t threads[2];
    Args args[2];
    int return_value[2];

    printf("Enter N: "); 
    // n = 6;
    scanf("%d", &n);

    arr = (int*)calloc(sizeof(int), n);

    for(int i = 0 ; i < n; i ++)
        scanf("%d", arr+i);

    args[0].arr = arr;
    args[0].n = n;
    args[0].f = 1;
    args[1] = args[0];
    args[1].f = 0;
 
    // Even
    pthread_create(threads + 0, 0, &child_thread, (void*)args);
    pthread_create(threads + 1, 0, &child_thread, (void*)(args+1));

    pthread_join( threads[0], (void**)(return_value+0) );
    pthread_join( threads[1], (void**)(return_value+1) );
    
    // printf("S: %d", return_value[0]);

    printf("Result: %d + %d = %d", return_value[0], return_value[1], return_value[0] + return_value[1]);
    printf("\n");

}
