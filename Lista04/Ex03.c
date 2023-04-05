#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define NUM_THREADS 4

pthread_barrier_t barrier;

void *contagem(void *arg){
    printf("Cheguei na barreira!\n");
    pthread_barrier_wait(&barrier);

    long t = (long)arg;
    unsigned int n = (unsigned int) t;

    unsigned int count = 0;
    for(int i = 0; i < n; i++) count++;
    
    t = (long) count;

    pthread_exit((void *) t);
}

int main(void){
    unsigned int count = 0, peace = (unsigned int) floor(((unsigned int)pow(2, 31))/NUM_THREADS);
    void *status;
    long incremento = 0;
    printf("2^31 = %u\n", (unsigned int) pow(2, 31));
    printf("peace = %u\n\n", peace);

    pthread_t threads[NUM_THREADS];
    pthread_barrier_init(&barrier, NULL, (unsigned int) NUM_THREADS);

    for (int i = 0; i < NUM_THREADS ; i++){
        pthread_create(&threads[i], NULL, contagem, (void *) (long) peace);

    }

    for (int i = 0; i < NUM_THREADS ; i++){
        printf("Esperando thread %i...\n", i);
        pthread_join(threads[i], &status);
        incremento = (long) status;
        count += (unsigned int) incremento;
        printf("Final da thread %i...\n", i);
    }
    printf("\nresto = %u", (unsigned int)pow(2, 31)%NUM_THREADS);
    count += (unsigned int)pow(2, 31)%NUM_THREADS;
    printf("\ncount = %u\n", count);
}
