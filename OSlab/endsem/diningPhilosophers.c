#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define N 5 // Number of philosophers

sem_t mutex;
sem_t forks[N];

void *philosopher(void *arg)
{
    int philosopher_id = *(int *)arg;
    int left_fork = philosopher_id;
    int right_fork = (philosopher_id + 1) % N;

    while (1)
    {
        // Thinking
        printf("Philosopher %d is thinking\n", philosopher_id);
        sleep(rand() % 3 + 1); // Simulate thinking time

        // Pick up forks
        sem_wait(&mutex);
        sem_wait(&forks[left_fork]);
        sem_wait(&forks[right_fork]);
        sem_post(&mutex);

        // Eating
        printf("Philosopher %d is eating\n", philosopher_id);
        sleep(rand() % 3 + 1); // Simulate eating time

        // Put down forks
        sem_post(&forks[left_fork]);
        sem_post(&forks[right_fork]);
    }
}

int main()
{
    pthread_t philosophers[N];
    int philosopher_ids[N];

    sem_init(&mutex, 0, 1);

    for (int i = 0; i < N; ++i)
    {
        sem_init(&forks[i], 0, 1);
    }

    for (int i = 0; i < N; ++i)
    {
        philosopher_ids[i] = i;
        pthread_create(&philosophers[i], NULL, philosopher, &philosopher_ids[i]);
    }

    for (int i = 0; i < N; ++i)
    {
        pthread_join(philosophers[i], NULL);
    }

    return 0;
}