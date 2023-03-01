#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

typedef struct PairList
{
    char** nameList;
    int nameListSize;
    int priority;
} pair_list;

int main(void){
    char *nameArg;
    int priorityArg;
    pair_list *list = NULL;
    int listSize = 0;
    while(1){
        scanf("%s %d", nameArg, &priorityArg);
        if(strcmp(nameArg, "MENIG")){}
        else if(strcmp(nameArg, "FIM")) break;
        else{
            
        }
    }
}

void insertPair(pair_list *list, int *size, char *nameArg, int priorityArg){
    int index = binarySearchVerify(list, size, priorityArg);
    if(index == -1){
        // Aumenta o tamanho da lista de pares:
        *size = *size + 1;
        // Aloca espaço na lista de pares:
        realloc(list, (*size) * sizeof(pair_list));

        // Aumenta o tamanho da lista de nomes na nova lista de pares (para 1):
        list[*size].nameListSize = 1;
        // Aloca um espaço na lista de nomes:
        realloc(list[*size].nameList, sizeof(char**));

        // Coloca o nome na primeira posição da lista de nomes (pois de início só há um nome):
        strcpy(list[*size].nameList[0], nameArg);
        // Coloca a prioridade na lista de nomes:
        list[*size].priority = priorityArg;
    }
    else{
        list[index].nameListSize++;
        realloc(list[*size].nameList, list[*size].nameListSize*sizeof(char**));
        strcpy(list[index].nameList[list[index].nameListSize], nameArg);
    }
}

int binarySearchVerify(pair_list *list, int size, int priority){
    // Retorna o índice ou se não existe retorna -1 (poderia retorna a posição na qual o item estaria mas...
    // ... não sei como usaria isto neste código):
    int index = size/2;
    while(size != 0){
        
    }
    return -1;
}

pair_list mergeSort(pair_list *list, int size){
    pair_list *newList = (pair_list *)malloc(sizeof(pair_list)*size);
    if(size > 1){
        int newSize1 = size/2;
        int newSize2 = size - size/2;
        // pairList *list1 = 
    }
    return;
}

void merge(pair_list *list, pair_list *newList, int index1, int index2, int end){
    pair_list tempVetor[end+1];
    return;
}