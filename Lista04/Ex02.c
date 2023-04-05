#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <pthread.h>

int n = 1;
pthread_mutex_t mtx;
pthread_cond_t cond1;
pthread_cond_t cond2;

void *X(void *argp){
    pthread_mutex_lock(&mtx);
    n = n*16;
    pthread_cond_signal(&cond1);
    pthread_mutex_unlock(&mtx);
}

void *Y(void *argp){
    pthread_mutex_lock(&mtx);
    while(n != 56) 
        pthread_cond_wait(&cond2, &mtx);
    n = n/7;
    pthread_mutex_unlock(&mtx);
}

void *Z(void *argp){
    pthread_mutex_lock(&mtx);
    while(n != 16)
        pthread_cond_wait(&cond1, &mtx);
    n = n+40;
    pthread_cond_signal(&cond2);
    pthread_mutex_unlock(&mtx);
}

int main(void){
    pthread_t t1, t2, t3;
    int rc;
    rc = pthread_mutex_init(&mtx, NULL);
    rc = pthread_cond_init(&cond1, NULL);
    rc = pthread_cond_init(&cond2, NULL);
    rc = pthread_create(&t1, NULL, X, NULL);
    rc = pthread_create(&t2, NULL, Y, NULL);
    rc = pthread_create(&t3, NULL, Z, NULL);
    rc = pthread_join(t1, NULL);
    rc = pthread_join(t2, NULL);
    rc = pthread_join(t3, NULL);
    printf("n = %d\n", n);
    return 0;
}