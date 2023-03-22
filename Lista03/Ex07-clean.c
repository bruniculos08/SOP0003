#include <time.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MIN(i, j) (((i) < (j)) ? (i) : (j))
// #define MAX(i, j) (((i) > (j)) ? (i) : (j))

#define N 100
int vetor[N];

int NTHR;
int *thread_row;
int next_row_element = 0;

void *procuraMenor(void *arg)
{
    int i = (int)(long)arg;
    // (1) Note que para otimização cada thread deve procurar o menor número em um lugar diferente do vetor:
    int min_index = i * (N / NTHR);
    int max_index = MIN(N, (i + 2) * (N / NTHR));
    int *min_value = malloc(sizeof(int));
    *min_value = vetor[min_index];
    // printf("thread[%i]: min_index = %i, max_index = %i\n", i, min_index, max_index);
    for (int j = min_index + 1; j < max_index; j++)
    {
        if (*min_value > vetor[j])
            *min_value = vetor[j];
    }
    // thread_row[next_row_element] = i;
    thread_row[next_row_element] = *min_value;
    next_row_element++;
    return (void *)min_value;
}

void *procuraMaior(void *arg)
{
    int i = (int)(long)arg;
    // (1) Note que para otimização cada thread deve procurar o menor número em um lugar diferente do vetor:
    int min_index = i * (N / NTHR);
    int max_index = MIN(N, (i + 2) * (N / NTHR));
    int *max_value = malloc(sizeof(int));
    *max_value = vetor[min_index];
    // printf("thread[%i]: min_index = %i, max_index = %i\n", i, min_index, max_index);
    for (int j = min_index + 1; j < max_index; j++)
    {
        if (*max_value < vetor[j])
            *max_value = vetor[j];
    }
    // thread_row[next_row_element] = i;
    thread_row[next_row_element] = *max_value;
    next_row_element++;
    return (void *)max_value;
}

int main(int argc, char **argv)
{
    NTHR = atoi(argv[1]);
    printf("NTHR = %i\n", NTHR);
    thread_row = malloc(sizeof(int)*NTHR);
    srand(time(NULL));
    pthread_t threads[NTHR];
    void *status;
    for (int i = 0; i < N; i++)
    {
        vetor[i] = rand()%1000;
        printf("vetor[%i] = %i\n", i, vetor[i]);
    }
    int max = vetor[1], min = vetor[1], *value;
    for (int i = 0; i < NTHR; i++){
        if ((i + 1) % 2 == 1) pthread_create(&threads[i], NULL, procuraMenor, (void *)(long)i);
        else pthread_create(&threads[i], NULL, procuraMaior, (void *)(long)i);
    }
    for (int i = 0; i < NTHR; i++){
        pthread_join(threads[i], (void *)&value);
        if (max < *value) max = *value;
        else if (min > *value) min = *value;
    }
    printf("min = %d\n", min);
    printf("max = %d\n", max);
    printf("ordem: ");
    for (int i = 0; i < NTHR; i++) printf("%i ", thread_row[i]);
    printf("\n");

    // (?) A função "pthread_exit(NULL)" serve como um "return 0" que espera todas as threads terminarem:
    pthread_exit(NULL);
}