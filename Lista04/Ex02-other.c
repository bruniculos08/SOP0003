#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <pthread.h>

// Igual o Ex02.c, porém usando apenas uma variável de condição (note que esta solução é menos eficiente pois...
// ... todas as threads podem acordar e a ultima a verificar a condição ser a que deveria ser liberada).

int n = 1;
pthread_mutex_t mtx;
pthread_cond_t cond;

void X(void *argp){
    pthread_mutex_lock(&mtx);
    n = n*16;
    pthread_cond_broadcast(&cond);
    pthread_mutex_unlock(&mtx);
}

void Y(void *argp){
    pthread_mutex_lock(&mtx);
    while(n != 56) 
        pthread_cond_wait(&cond, &mtx);
    n = n/7;
    pthread_mutex_unlock(&mtx);
}

void Z(void *argp){
    pthread_mutex_lock(&mtx);
    while(n != 16)
        pthread_cond_wait(&cond, &mtx);
    n = n+40;
    pthread_cond_broadcast(&cond);
    pthread_mutex_unlock(&mtx);
}

int main(void){
    pthread_t t1, t2, t3;
    int rc;
    rc = pthread_mutex_init(&mtx, NULL);
    rc = pthread_cond_init(&cond, NULL);
    rc = pthread_create(&t1, NULL, (void *)X, NULL);
    rc = pthread_create(&t2, NULL, (void *)Y, NULL);
    rc = pthread_create(&t3, NULL, (void *)Z, NULL);
    rc = pthread_join(t1, NULL);
    rc = pthread_join(t2, NULL);
    rc = pthread_join(t3, NULL);
    printf("n = %d\n", n);
    return 0;
}