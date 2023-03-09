#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

typedef struct PairList pair_list;
struct PairList{
    char **nameList;
    int nameListSize;
    int priority;
};

int binarySearchVerify(pair_list *list, int size, int priorityToFind);
void printNames(pair_list *list, int index);
void printList(pair_list *list, int size);
pair_list *insertPair(pair_list *list, int *size, char *nameArg, int priorityArg);
pair_list *mergeSort(pair_list *list, int start, int end);
pair_list *merge(pair_list *list, int left, int right, int end);

int main(void){
    char *nameArg = (char *)malloc(sizeof(char)*20);
    int priorityArg;
    pair_list *list = NULL;
    int listSize = 0;
    while(1){
        scanf("%s %i", nameArg, &priorityArg);
        fflush(stdin);
        if(strcmp(nameArg, "MENIG") == 0){
            for(int i=binarySearchVerify(list, listSize, priorityArg); i>=0; i--) printNames(list, i);
        }
        else if(strcmp(nameArg, "FIM") == 0) break;
        else list = insertPair(list, &listSize, nameArg, priorityArg);
        printList(list, listSize);
    }
}

void printList(pair_list *list, int size){
    for(int i=0; i<size; i++){
        printf("List with priority %i: ", list[i].priority);
        for(int j=0; j<list[i].nameListSize; j++) printf("%s ", list[i].nameList[j]);
        printf("\n");
    }
}

void printNames(pair_list *list, int index){
    for(int i=0; i<list[index].nameListSize; i++) printf("%s\n", list[index].nameList[i]);
}

pair_list *insertPair(pair_list *list, int *size, char *nameArg, int priorityArg){
    int index = binarySearchVerify(list, *size, priorityArg);
    if(index == -1){
        
        // Aumenta o tamanho da lista de pares:
        *size = *size + 1;

        // Aloca espaço na lista de pares:
        if(list == NULL) list = malloc(sizeof(pair_list));
        else list = realloc(list, (*size)*sizeof(pair_list));

        // Aumenta o tamanho da lista de nomes na nova lista de pares (para 1):
        list[(*size)-1].nameListSize = 1;

        // Aloca um espaço na lista de nomes:
        list[*size-1].nameList = malloc(sizeof(char*));
        // realloc(list[*size-1].nameList, sizeof(char**));

        list[*size-1].nameList[0] = malloc(20*sizeof(char));

        // Coloca o nome na primeira posição da lista de nomes (pois de início só há um nome):
        strcpy(list[*size-1].nameList[0], nameArg);

        // Coloca a prioridade na lista de nomes:
        list[*size-1].priority = priorityArg;
    }
    else{
        list[index].nameListSize++;
        list[index].nameList = realloc(list[index].nameList, list[index].nameListSize*sizeof(char*));
        list[index].nameList[(list[index].nameListSize)-1] = malloc(20*sizeof(char));
        strcpy(list[index].nameList[(list[index].nameListSize)-1], nameArg);
        printNames(list, index);
    }
    list = mergeSort(list, 0, *size-1);
    return list;
}

int binarySearchVerify(pair_list *list, int size, int priorityToFind){
    if(list == NULL) return -1;
    // Retorna o índice ou se não existe retorna -1 (poderia retorna a posição na qual o item estaria mas...
    // ... não sei como usaria isto neste código):
    int left = 0;
    int right = size-1;
    int middle = (left + right)/2;
    do{
        if(list[middle].priority == priorityToFind) return middle;
        else if(list[middle].priority > priorityToFind) right = middle - 1;
        else left = middle + 1;
        middle = (left + right)/2;
    } while(left <= right);
    return -1;
}

pair_list *mergeSort(pair_list *list, int start, int end){
    if(list == NULL || start >= end) return list;
    // Note que o meio é o índice de início da lista à direita:
    int middle = (end + start)/2;
    list = mergeSort(list, start, middle);
    list = mergeSort(list, middle+1, end);
    list = merge(list, start, middle+1, end);
    return list;
}

pair_list *merge(pair_list *list, int left, int right, int end){
    if(list == NULL) return NULL;
    else if(right > end || left > right) return list;

    pair_list *temp = malloc((1 + end-left)*sizeof(pair_list));
    int l = left, r = right;

    for(int i = 0; i <= end-left; i++){
        if(l > right-1){
            temp[i] = list[r];
            r++;
        }
        else if(r > end){
            temp[i] = list[l];
            l++;
        }
        else if(list[l].priority <= list[r].priority){
            temp[i] = list[l];
            l++;
        }
        else{
            temp[i] = list[r];
            r++;
        }
    }
    for(int i = 0; i <= end-left; i++) list[i+left] = temp[i];
    return list;
}