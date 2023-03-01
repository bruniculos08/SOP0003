#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Fila circular (sim eu poderia fazer isso com lista encadeada mas fiz com vetor);
void printVetor(int *vetor, int size);

int main(int argc, char **argv){
    int size = (int) atoi(argv[1]);
    int actualSize = 0;
    printf("size: %d\n", size);
    int *vetor;
    vetor = (int *)malloc(size*sizeof(int));
    int num = 0;
    for (int i = 0; 1; i++){
        scanf("%i", &num);
        fflush(stdin);
        if(num == -2){
            i--;
            printVetor(vetor, actualSize);
            continue;
        }
        else if(num == -1) break;
        else if(num != -2){
            vetor[(i%size)] = num;
            if(actualSize < size) actualSize++;
        }
    }
    return 0;
}

void printVetor(int *vetor, int size){
    printf("Fila: ");
    for (int i = 0; i < size; i++) printf("%i ", *(vetor+i));
    printf("\n");
    return;
}