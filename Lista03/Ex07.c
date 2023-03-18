#include <time.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MIN(i, j) (((i) < (j)) ? (i) : (j))
// #define MAX(i, j) (((i) > (j)) ? (i) : (j))

#define N 1000000000
int vetor[N];

#define NTHR 10
int thread_row[NTHR];
int next_row_element = 0;

void *procuraMenor(void *arg)
{
    int i = (int)(long)arg;
    // (1) Note que para otimização cada thread deve procurar o menor número em um lugar diferente do vetor:
    int min_index = i * (N / NTHR);
    int max_index = MIN(N, (i + 2) * (N / NTHR));
    int *min_value = malloc(sizeof(int));
    *min_value = vetor[min_index];
    for (int j = min_index + 1; j < max_index; j++)
    {
        if (*min_value > vetor[j])
            *min_value = vetor[j];
    }

    thread_row[next_row_element] = i;
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
    for (int j = min_index + 1; j < max_index; j++)
    {
        if (*max_value < vetor[j])
            *max_value = vetor[j];
    }
    thread_row[next_row_element] = i;
    next_row_element++;
    return (void *)max_value;
}

int main(void)
{
    srand(time(NULL));
    pthread_t threads[NTHR];
    for (int i = 0; i < N; i++)
    {
        vetor[i] = rand();
        // printf("vetor[%i] = %i\n", i, vetor[i]);
    }
    int max = vetor[1], min = vetor[1], *value;
    for (int i = 0; i < NTHR; i++)
    {
        if ((i + 1) % 2 == 1)
            pthread_create(&threads[i], NULL, procuraMenor, (void *)(long)i);
        else
            pthread_create(&threads[i], NULL, procuraMaior, (void *)(long)i);
    }
    for (int i = 0; i < NTHR; i++)
    {
        pthread_join(threads[i], (void *)&value);
        if (max < *value)
            max = *value;
        else if (min > *value)
            min = *value;
    }
    printf("min = %d\n", min);
    printf("max = %d\n", max);
    printf("ordem: ");
    for (int i = 0; i < NTHR; i++)
        printf("%i ", thread_row[i]);
    printf("\n");
    return 0;
}