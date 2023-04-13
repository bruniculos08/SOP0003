#define _XOPEN_SOURCE 600 // Coloque esta linha no código caso esteja em Linux (sem isto a barreira não é definida)
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>
#include <math.h>

// gcc Ex06.c -Wall -pthread -o Ex06 && ./Ex06

int T, N;
unsigned int *queue;
unsigned int **matrix;
pthread_barrier_t waitToLookQueue;
pthread_barrier_t allThreadsEnded;

void *find_min(void *arg){
    long t = (long) arg;
    int index = (int) t;

    int min = matrix[index][0];
    for(int i = 0; i < N/T; i++){
        for(int j = 0; j < N; j++){
            if(matrix[index*(N/T) + i][j] < min) 
                min = matrix[index*(N/T) + i][j];
        }
    }
    queue[index] = min;
    pthread_barrier_wait(&waitToLookQueue);
    int numMenores = 0;
    for(int i = 0; i < T; i++){
        if(queue[i] < min)
            numMenores++;
    }
    printf("(thread %d) menor elemento=%d, threads com elementos menores=%d\n", index, min, numMenores);
    pthread_barrier_wait(&allThreadsEnded);
    return 0;
}  

void printMatrix(unsigned int **array, int lines, int cols){
    for(int i = 0; i < lines; i++){
        printf("\t");
        for(int j = 0; j < cols; j++){
            printf("%d ", array[i][j]);
        }
        printf("\n");
    }
}

// Usar como argumento um número de threads e um número k tal que N = k.T para que N seja divisível por T;
int main(int argc, char *argv[]){
    // T = atoi(argv[1]);
    // N = T*atoi(argv[2]);
    T = 4;
    N = 2*T;

    srand(time(NULL));

    matrix = malloc(sizeof(unsigned int*)*N);
    for(int i = 0; i < N; i++){
        matrix[i] = malloc(sizeof(unsigned int)*N);
        for(int j = 0; j < N; j++){
            matrix[i][j] = random()%100 + 2;
        }
    }

    queue = malloc(T*sizeof(unsigned int));
    pthread_barrier_init(&waitToLookQueue, NULL, T+1);
    pthread_barrier_init(&allThreadsEnded, NULL, T+1);
    pthread_t ths[T];
    for(int i = 0; i < T; i++){
        queue[i] = 100; // definimos 99 como maior elemento;
        // Note que cada thread terá que verificar a linha k*i e a linha k*i+1, k*i+2, ..., k*i + (k-1);
        if(pthread_create(&ths[i], NULL, find_min, (void*) (long) i) != 0){
            perror("Failed to create thread");
        }
    }

    // Poderiamos utilizar pthread_join() mas utilizar ao barreira poderemos olhar a fila antes...
    // ... das threads encerrarem;
    pthread_barrier_wait(&waitToLookQueue);
    int min_thread = 0;
    for(int i = 0; i < T; i++){
        if(queue[i] < queue[min_thread]) min_thread = i;
    }
    
    // De qualquer jeito para que a ordem de print saia corretamente é necessário esperar todas as threads terminarem;
    pthread_barrier_wait(&allThreadsEnded);

    printf("O menor elemento da matriz é: %d\n", queue[min_thread]);

    printf("Matriz:\n");
    printMatrix(matrix, N, N);
    printf("Fila:\n");
    printMatrix(&queue, 1, T);


    return 0;
}