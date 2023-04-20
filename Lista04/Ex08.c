#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <pthread.h>
#include <semaphore.h>

int n = 1;
sem_t sy, sz;

// Aqui cheguei na conclusão de que um mutex é simulado por um semáforo que começa em 1;

void *X(void *argp){
    n = n*16;
    sem_post(&sz);
    pthread_exit(0);
}

void *Y(void *argp){
    sem_wait(&sy);
    n = n/7;
    pthread_exit(0);
}

void *Z(void *argp){
    sem_wait(&sz);
    n = n+40;
    sem_post(&sy);
    pthread_exit(0);
}

int main(void){
    pthread_t t1, t2, t3;
    int rc;
    rc = sem_init(&sz, 0, 0);
    rc = sem_init(&sy, 0, 0);
    rc = pthread_create(&t1, NULL, X, NULL);
    rc = pthread_create(&t2, NULL, Y, NULL);
    rc = pthread_create(&t3, NULL, Z, NULL);
    rc = pthread_join(t1, NULL);
    rc = pthread_join(t2, NULL);
    rc = pthread_join(t3, NULL);
    printf("n = %d\n", n);
    return 0;
}