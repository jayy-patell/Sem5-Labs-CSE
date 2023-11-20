#include <pthread.h>
#include <stdio.h>
void* thread_code()
{
printf( "In thread code\n" );
pthread_exit(0);  //is passed implicitly when thread ends
}
int main()
{
pthread_t thread;
pthread_create( &thread, 0, &thread_code, 0 );
printf( "In main thread\n" );
pthread_join( thread, 0 );
}