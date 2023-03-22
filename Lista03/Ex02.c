#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define NUM_THREADS 5

void *PrintHello(void *arg)
{
    long tid = (long)arg;
    printf("Alo da thread %ld\n",
           tid);
    pthread_exit(NULL);
}

void *PrintQuadrado(void *arg)
{
    long tid = (long)arg;
    printf("Quadrado do parâmetro: %ld\n",
           tid*tid);
    pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
    // (1) Cria-se um vetor de threads:
    pthread_t threads[NUM_THREADS];
    pthread_t extra_threads[NUM_THREADS + 3];
    int rc;
    long t;
    // (2) Criando uma thread para cada espaço do vetor:
    for (t = 0; t < NUM_THREADS + 3; t++)
    {
        if (t < NUM_THREADS)
        {
            printf("main: criando thread %ld\n", t);
            rc = pthread_create(&threads[t], NULL, PrintHello, (void *)t);
            // (2.1) Se rc == 1 então a thread não foi criada:
            if (rc)
            {
                printf("ERRO - rc=%d\n", rc);
                exit(-1);
            }
        }
        rc = pthread_create(&extra_threads[t], NULL, PrintQuadrado, (void *)t);
        if (rc)
        {
            printf("ERRO - rc=%d\n", rc);
            exit(-1);
        }
    }
    /* Ultima coisa que main() deve fazer */
    pthread_exit(NULL);
}
