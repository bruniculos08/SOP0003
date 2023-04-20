#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <semaphore.h>
#include <pthread.h>
#include <signal.h>
#include <stdlib.h>

//gcc old-exercise.c -pthread -lrt -o old-exercise && ./old-exercise

sem_t s1, s2, s3;

void *A(){
    while(1){
        sem_wait(&s2);
        printf("i");
        sem_post(&s3);
        sem_wait(&s2);
        printf("a");
        sem_post(&s3);
    }
    pthread_exit(0);
}

void *B(){
    int i;
    while(1){
        for(i = 0; i < 2; i++){
            sem_wait(&s3);
            printf("t");
            if(i == 0){
                printf("-");
            }
            sem_post(&s1);
        }
    }
    pthread_exit(0);
}

void *C(){
    int j;
    while(1){
        for(j = 0; j < 2; j++){
            sem_wait(&s1);
            printf("K");
            sem_post(&s2);
        }
        sem_wait(&s1);
        printf("\n");
        sem_post(&s1);
    }
    
    pthread_exit(0);
}

int main(){

    sem_init(&s1, 0, 1);
    sem_init(&s2, 0, 0);
    sem_init(&s3, 0, 0);

    pthread_t ts[3];
    pthread_create(&ts[0], NULL, A, NULL);
    pthread_create(&ts[1], NULL, B, NULL);
    pthread_create(&ts[2], NULL, C, NULL);

    for(int i = 0; i < 3; i++){
        pthread_join(ts[i], NULL);
    }
}