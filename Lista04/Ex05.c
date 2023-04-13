#define _XOPEN_SOURCE 600 // Coloque esta linha no código caso esteja em Linux (sem isto a barreira não é definida)
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

#define INC 10 //1000000000
int N = 1;
// gcc Ex05.c -Wall -pthread -o Ex05 && ./Ex05
// for i in {1..1000}; do ./Ex05; done | sort | uniq -c

// Resposta da questão: independente da quantidade de threads, a tendência é que as rodadas ocorram na mesma ordem em que...
// ... as threads foram criadas, ou seja, a thread 0 termina em 1º, a thread 1 termina em 2º e assim por diante, sendo que...
// ... o segundo comportamento mais comum é a troca de ordem entre a última e a penúltima thread, isto é, casos em que...
// ... a última thread termina a rodada antes da penúltima;

int quest, queue_next;
int *queue;

pthread_barrier_t barrier;
sem_t s1, s2; 
// Poderíamos utilizar um mutex porém iremos utilizar neste código um semáforo para lembrar melhor deste;
// Semáforo binário (que é um caso de utilização do semáforo e não um tipo de semáforo) possuem a mesma lógica de...
// ... de utilização; 

void printVector(int *vector, int size){
    printf("{ ");
    for (int i = 0; i < size; i++){
        printf("%d ", vector[i]);
    }
    printf("}\n");
}

void *incrementa(void *arg){
    long t = (long) arg;
    int index = (int) t;
    
    for(int i = 0; i < 10; i++){
        for(int j = 0; j < INC; j++){
            sem_wait(&s1);
            quest += 1;
            sem_post(&s1);
        }

        sem_wait(&s2);
        queue[queue_next] = index;
        if(queue_next == N-1){
            printVector(queue, N);
            // quest = 0;
        }
        queue_next = (queue_next+1)%N;
        sem_post(&s2);
        pthread_barrier_wait(&barrier);
    }
    return 0;
}

int main(int argc, char *argv[]){

    N = atoi(argv[1]);

    if(pthread_barrier_init(&barrier, NULL, N) != 0)
        perror("Failed to init barrier");

    if(sem_init(&s1, 0, 1) != 0 || sem_init(&s2, 0, 1) != 0)
        perror("Failed to init semaphore");
        
    pthread_t threads[N];

    queue = malloc(sizeof(int)*N);
    quest = 0;
    queue_next = 0;


    for(int i = 0; i < N; i++){
        if(pthread_create(&threads[i], NULL, incrementa, (void*) (long) i) != 0) 
            perror("Failed to create thread");
    }
    
    for(int i = 0; i < N; i++){
        if(pthread_join(threads[i], NULL) != 0) 
            perror("Failed to join thread");
    }

    printf("quest = %d\n", quest);
    return 0;
}