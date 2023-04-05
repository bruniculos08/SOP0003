#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define N 10
int buffer[N];
int proximo_item = 0;

pthread_mutex_t mtx;
pthread_cond_t cond;

void printVector(int *vector, int size){
    for (int i = 0; i < size; i++){
        printf("%d ", vector[i]);
    }
    printf("\n");
}

void *productor(void *argp){
    while (1){
        sleep(4);
        pthread_mutex_lock(&mtx);
        // Nesse caso, como se tratam apenas de 2 threads poderia-se utilizar o "if", porém o "while" funciona em todos os casos, isto é,...
        // ... até mesmo quando temos mais threads.
        while (proximo_item == N){
            pthread_cond_wait(&cond, &mtx);
        }
        buffer[proximo_item] = (rand() + 1)%100;
        proximo_item = (proximo_item+1)%N;
        printVector(buffer, N);
        pthread_cond_signal(&cond);        
        pthread_mutex_unlock(&mtx);        
    }
    return 0;
}

void *consumer(void *argp){
    while (1){
        sleep(1);
        pthread_mutex_lock(&mtx);
        // Nesse caso, como se tratam apenas de 2 threads poderia-se utilizar o "if", porém o "while" funciona em todos os casos, isto é,...
        // ... até mesmo quando temos mais threads.
        while (proximo_item == 0){
            pthread_cond_wait(&cond, &mtx);
        }
        buffer[proximo_item-1] = 0;
        proximo_item--;
        printVector(buffer, N);
        pthread_cond_signal(&cond);        
        pthread_mutex_unlock(&mtx);        
    }
    return 0;
}


int main(){
    srand(time(NULL));
    pthread_t t1, t2;
    int rc;
    rc = pthread_create(&t1, NULL, productor, NULL); 
    rc = pthread_create(&t2, NULL, consumer, NULL); 
    rc = pthread_mutex_init(&mtx, NULL);
    rc = pthread_cond_init(&cond, NULL);

    rc = pthread_join(t1, NULL);
    rc = pthread_join(t2, NULL);

}