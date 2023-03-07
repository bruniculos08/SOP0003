#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

typedef struct PairList pair_list;
struct PairList{
    char** nameList;
    int nameListSize;
    int priority;
};

int binarySearchVerify(pair_list *list, int size, int priorityToFind);
void printNames(pair_list *list, int index);
void insertPair(pair_list *list, int *size, char *nameArg, int priorityArg);
pair_list *mergeSort(pair_list list[], int start, int end);
pair_list *merge(pair_list *list, int left, int right, int end);

int main(void){
    char *nameArg = (char *)malloc(sizeof(char)*20);
    int priorityArg;
    pair_list *list = NULL;
    int listSize = 0;
    while(1){
        scanf("%s %i", nameArg, &priorityArg);
        if(strcmp(nameArg, "MENIG") == 0){
            for(int i=binarySearchVerify(list, listSize, priorityArg); i>=0; i--) printNames(list, i);
        }
        else if(strcmp(nameArg, "FIM") == 0) break;
        else insertPair(list, &listSize, nameArg, priorityArg);
    }
}

void printNames(pair_list *list, int index){
    for(int i=0; i<list[index].nameListSize; i++) printf("%s", list[index].nameList[i]);
}

void insertPair(pair_list *list, int *size, char *nameArg, int priorityArg){
    int index = binarySearchVerify(list, *size, priorityArg);
    if(index == -1){
        // Aumenta o tamanho da lista de pares:
        *size = *size + 1;

        // Aloca espaço na lista de pares:
        if(list == NULL) list = malloc(sizeof(pair_list *));
        else realloc(list, (*size)*sizeof(pair_list *));

        // Aumenta o tamanho da lista de nomes na nova lista de pares (para 1):
        list[(*size)-1].nameListSize = 1;


        // Aloca um espaço na lista de nomes:
        list[*size-1].nameList = (char**)malloc(sizeof(char**));
        // realloc(list[*size-1].nameList, sizeof(char**));

        // Coloca o nome na primeira posição da lista de nomes (pois de início só há um nome):
        strcpy(list[*size-1].nameList[0], nameArg);

        // Coloca a prioridade na lista de nomes:
        list[*size-1].priority = priorityArg;
    }
    else{
        list[index].nameListSize++;
        realloc(list[*size].nameList, list[*size].nameListSize*sizeof(char**));
        strcpy(list[index].nameList[list[index].nameListSize], nameArg);
    }
    // list = mergeSort(list, 0, *size);
}

int binarySearchVerify(pair_list *list, int size, int priorityToFind){
    if(list == NULL) return -1;
    // Retorna o índice ou se não existe retorna -1 (poderia retorna a posição na qual o item estaria mas...
    // ... não sei como usaria isto neste código):
    int middle = size/2;
    while((middle != 0 && middle != size-1) || list[middle].priority != priorityToFind){
        if(list[middle].priority == priorityToFind) return middle;
        else if(list[middle].priority < priorityToFind) middle = middle + (size-middle)/2;
        else middle = middle - (size-middle)/2;
    }
    return -1;
}

pair_list *mergeSort(pair_list list[], int start, int end){
    if(start == end) return list;
    // Note que o meio é o índice de início da lista à direita:
    int middle = (end+1)/2;
    list = mergeSort(list, start, middle);
    list = mergeSort(list, middle, end);
    list = merge(list, start, middle, end);
    return list;
}

pair_list *merge(pair_list *list, int left, int right, int end){
    // Se os elementos são os mesmos:
    if(left == right) return list;
    // Senão:
    else{
        pair_list temp[end-left];
        int l = left, r = right, i = 0;
        // Ordenação e preenchimento da lista temporária:
        while(1){
            // Se os elementos da lista à esquerda já acabaram:
            if(l > left){
                // Colocar todos os elementos da lista da direita na lista temporária:
                while(r < right){
                    temp[i] = list[r];
                    i++;
                    r++;
                }
                // Para o preenchimento da lista temporária:
                break;
            }
            // Se os elementos da lista à direita já acabaram:
            else if(r > right){
                // Colocar todos os elementos da lista da esquerda na lista temporária:
                while(l < left){
                    temp[i] = list[l];
                    i++;
                    l++;
                }
                // Para o preenchimento da lista temporária:
                break;
            }
            else if(list[l].priority <= list[r].priority){
                temp[i] = list[l];
                l++;
            }
            else{
                temp[i] = list[r];
                r++;
            }
            i++;
        }
        // Copiando a lista temporária para o seu respectivo lugar na lista definitiva:
        for(int j = left; j <= right; j++) list[j] = temp[j-left];
    }
    return list;
}