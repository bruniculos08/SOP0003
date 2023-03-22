#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define NUM_THREADS 4

void *contagem(void *arg){
    long t = (long)arg;
    unsigned int n = (unsigned int) t;

    unsigned int count = 0;
    for(int i = 0; i <= n; i++) count++;
    
    t = (long) count;

    pthread_exit((void *) t);
}

int main(void){
    unsigned int count = 0, peace = (unsigned int) ceil(((int)pow(2, 31))/NUM_THREADS);
    void *status;
    long incremento = 0;
    printf("2^31 = %u\n", (unsigned int) pow(2, 31));
    printf("peace = %u\n\n", peace);
    pthread_t threads[NUM_THREADS];
    for (int i = 0; i < NUM_THREADS ; i++) pthread_create(&threads[i], NULL, contagem, (void *) (long) peace);
    for (int i = 0; i < NUM_THREADS ; i++){
        printf("Esperando thread %i...\n", i);
        pthread_join(threads[i], &status);
        incremento = (long) status;
        count += (unsigned int) (long) incremento;
        printf("Final da thread %i...\n", i);
    }
    printf("\nresto = %u", ((unsigned int)pow(2, 30)%NUM_THREADS + (unsigned int)pow(2, 30)%NUM_THREADS)%NUM_THREADS);
    count += ((unsigned int)pow(2, 30)%NUM_THREADS + (unsigned int)pow(2, 30)%NUM_THREADS)%NUM_THREADS;
    printf("\ncount = %u\n", count);
}


// void *contagem(void *arg){
//     long *n = (long *) arg;
//     printf("%d\n", (int) *n);
//     int max = (((int) pow(2, 30))/NUM_THREADS);
//     for(int i = 0; i < max; i++) (*n) += 1;
//     pthread_exit(NULL);
// }

// int main(int argc, char *argv[])
// {
//     long count = 0;
//     printf("Grande número: %i\n", ((int)pow(2, 30)%NUM_THREADS + (int)pow(2, 30)%NUM_THREADS)%NUM_THREADS);
//     printf("Grande número: %i\n", ((int) pow(2, 30)));
//     pthread_t threads[NUM_THREADS];
//     int rc;
//     long total_thr = 0;
//     for (int i = 0; i < NUM_THREADS ; i++) pthread_create(&threads[i], NULL, contagem, (void *)&total_thr);
//     for (int i = 0; i < NUM_THREADS ; i++){
//         printf("Esperando thread %i...\n", i);
//         rc = pthread_join(threads[i], NULL);
//         printf("Final da thread %i...\n", i);
//     }
//     // count += total_thr + (((int)pow(2, 31))%NUM_THREADS);
//     count = total_thr; //+ ((int)pow(2, 30)%NUM_THREADS + (int)pow(2, 30)%NUM_THREADS)%NUM_THREADS;
//     printf("count = %d\n", (int) count);
//     pthread_exit(NULL);
// }
