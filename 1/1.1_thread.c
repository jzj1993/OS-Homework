#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t m1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t m2 = PTHREAD_MUTEX_INITIALIZER;

void *thread1(void *args)
{
        pthread_mutex_lock(&m1);
        sleep(1);
        pthread_mutex_lock(&m2);
        pthread_mutex_unlock(&m1);
        pthread_mutex_unlock(&m2);
        printf("thread1 finish\n");
}

void *thread2(void *args)
{
        pthread_mutex_lock(&m2);
        sleep(1);
        pthread_mutex_lock(&m1);
        pthread_mutex_unlock(&m1);
        pthread_mutex_unlock(&m2);
        printf("thread2 finish\n");
}

int main(void)
{
        int rc,t = 0;
        pthread_t t1, t2;

        printf("Creating thread...\n");

        pthread_create(&t1, NULL, thread1, (void *)t);
        pthread_create(&t2, NULL, thread2, (void *)t);

        pthread_join(t1, NULL);
        pthread_join(t2, NULL);

        printf("Create thread finish\n");

        pthread_mutex_destroy(&m1);
        pthread_mutex_destroy(&m2);

        return EXIT_SUCCESS;
}
