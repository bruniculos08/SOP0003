#define _XOPEN_SOURCE 600 // Coloque esta linha no código caso esteja em Linux (sem isto a barreira não é definida)
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>
#include <math.h>


#define MAX 2000

int n;
sem_t semaphore; 

// A condição de disputa neste código está sobre a variável n;

// Obs. 1: o "comando para testes" (que o professor costuma usar) é:
// for i in {1..1000}; do ./Ex07; done | sort | uniq -c

// Obs. 2: note que tipo de retorn void != void * mas também funciona para as threads, e evita warning ("control reaches...
// ...end of non-void function").

void *f1(void *argp){
    int i, temp;
    for(i = 0; i < MAX; i++){
        // Início da região crítica:
        sem_wait(&semaphore);
        temp = n;
        temp++;
        n = temp;
        sem_post(&semaphore);
        // Final da região crítica;
    }
    pthread_exit(0);
}

void *f2(void *argp){
    int i, temp;
    for(i = 0; i < MAX; i++){
        // Início da região crítica:
        sem_wait(&semaphore);
        temp = n;
        temp--;
        n = temp;
        sem_post(&semaphore);
        // Final da região crítica;
    }
    pthread_exit(0);
}

int main(void){
    pthread_t t1, t2;
    int rc;
    n = 0;
    rc = sem_init(&semaphore, NULL, 1);
    rc = pthread_create(&t1, NULL, (void *)f1, NULL);
    rc = pthread_create(&t2, NULL, (void *)f2, NULL);
    rc = pthread_join(t1, NULL);
    rc = pthread_join(t2, NULL);
    printf("n = %d\n", n);
    return 0;
}