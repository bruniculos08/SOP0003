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
        printNames(list, 0);
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
    if(list == NULL){
        return -1;
    }
    // Retorna o índice ou se não existe retorna -1 (poderia retorna a posição na qual o item estaria mas...
    // ... não sei como usaria isto neste código):
    int middle = size/2;
    int left = 0;
    int right = size-1;
    do{
        if(list[middle].priority == priorityToFind) return middle;
        else if(list[middle].priority < priorityToFind){
            left = middle;
            middle = (left + right)/2;
        }
        else{
            right = middle;
            middle = (left+middle)/2;
        }
    } while(left != right);
    return -1;
}

pair_list *mergeSort(pair_list *list, int start, int end){
    if(start >= end) return list;
    // Note que o meio é o índice de início da lista à direita:
    int middle = (end)/2;
    list = mergeSort(list, start, middle);
    list = mergeSort(list, middle+1, end);
    list = merge(list, start, middle+1, end);
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
        while(i < end-left){
            // Se os elementos da lista à esquerda já acabaram:
            if(l > right){
                // Colocar todos os elementos da lista da direita na lista temporária:
                while(r <= end){
                    temp[i] = list[r];
                    i++;
                    r++;
                }
                // Para o preenchimento da lista temporária:
                break;
            }
            // Se os elementos da lista à direita já acabaram:
            else if(r > end){
                // Colocar todos os elementos da lista da esquerda na lista temporária:
                while(l < right){
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
        for(int j = left; j <= end; j++) list[j] = temp[j-left];
    }
    return list;
}