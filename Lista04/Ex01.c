#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <pthread.h>

#define MAX 2000

int n;
pthread_mutex_t mtx; 

// A condição de disputa neste código está sobre a variável n;

// Obs. 1: o "comando para testes" (que o professor costuma usar) é:
// for i in {1..1000}; do ./Ex01; done | sort | uniq -c

// Obs. 2: note que tipo de retorn void != void * mas também funciona para as threads, e evita warning ("control reaches...
// ...end of non-void function").

void *f1(void *argp){
    int i, temp;
    for(i = 0; i < MAX; i++){
        // Início da região crítica:
        pthread_mutex_lock(&mtx);
        temp = n;
        temp++;
        n = temp;
        pthread_mutex_unlock(&mtx);
        // Final da região crítica;
    }
}

void *f2(void *argp){
    int i, temp;
    for(i = 0; i < MAX; i++){
        // Início da região crítica:
        pthread_mutex_lock(&mtx);
        temp = n;
        temp--;
        n = temp;
        pthread_mutex_unlock(&mtx);
        // Final da região crítica;
    }
    
}

int main(void){
    pthread_t t1, t2;
    int rc;
    n = 0;
    rc = pthread_mutex_init(&mtx, NULL);
    rc = pthread_create(&t1, NULL, (void *)f1, NULL);
    rc = pthread_create(&t2, NULL, (void *)f2, NULL);
    rc = pthread_join(t1, NULL);
    rc = pthread_join(t2, NULL);
    printf("n = %d\n", n);
    return 0;
}