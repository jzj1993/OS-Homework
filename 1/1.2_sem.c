#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

pthread_mutex_t m1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t m2 = PTHREAD_MUTEX_INITIALIZER;

sem_t s1;

void *thread1(void *args)
{
	while(1) {
		sem_wait(&s1);
        pthread_mutex_lock(&m1);
        pthread_mutex_lock(&m2);
        printf("thread1\n");
        pthread_mutex_unlock(&m2);
        pthread_mutex_unlock(&m1);
		sem_post(&s1);
        sleep(1);
	}
}

void *thread2(void *args)
{
	while(1) {
		sem_wait(&s1);
        pthread_mutex_lock(&m2);
        pthread_mutex_lock(&m1);
        printf("thread2\n");
        pthread_mutex_unlock(&m1);
        pthread_mutex_unlock(&m2);
		sem_post(&s1);
        sleep(1);
	}
}

int main(void)
{
        int rc,t = 0;
        pthread_t t1, t2;

		sem_init(&s1, 0, 1);

        printf("Creating thread...\n");

        pthread_create(&t1, NULL, thread1, (void *)t);
        pthread_create(&t2, NULL, thread2, (void *)t);

        pthread_join(t1, NULL);
        pthread_join(t2, NULL);

        printf("Create thread finish\n");

        pthread_mutex_destroy(&m1);
        pthread_mutex_destroy(&m2);

		sem_destroy(&s1);
		
        return EXIT_SUCCESS;
}
