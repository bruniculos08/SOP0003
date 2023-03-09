#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Fila circular (sim eu poderia fazer isso com lista encadeada mas fiz com vetor);
void printVetor(int *vetor, int size, int start);

int main(int argc, char **argv){
    int size = (int) atoi(argv[1]);
    int actualSize = 0;
    int actualStart = 0;
    int *vetor;
    vetor = (int *)malloc(size*sizeof(int));
    int num = 0;
    for (int i = 0; 1; i++){
        scanf("%i", &num);
        if(num == -2){
            i--;
            printVetor(vetor, actualSize, actualStart);
        }
        else if(num == -1) break;
        else{
            vetor[(i%size)] = num;
            if(actualSize < size) actualSize++;
            else actualStart = (actualStart + 1)%size;
        }
    }
    return 0;
}

void printVetor(int *vetor, int size, int start){
    printf("Fila: ");
    for (int i = 0; i < size; i++) printf("%i ", *(vetor+(i+start)%size));
    printf("\n");
    return;
}