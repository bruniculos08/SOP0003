#include <stdlib.h>
#include <stdio.h>

void printArray(int *array, int start, int size);
int binarySearch(int *array, int target, int size);
int *mergeSort(int *array, int start, int end);
int *merge(int *array, int left, int right, int end);

int main(void) {
    int size;
    printf("Type array size: ");
    scanf("%d", &size);
    int *myArray = malloc(size*sizeof(int));

    printf("Type each array element:\n");
    for(int i = 0; i < size; i++) scanf("%d", &myArray[i]);

    int flag = -1;
    int auxNum;
    while (flag != 0)
    {
        printf("0 - Exit\n1 - Binary Search\n2 - Merge Sort\n");
        scanf("%d", &flag);
        system("cls");
        switch (flag)
        {
        case 1:
            printf("Type a number to search: ");
            scanf("%i", &auxNum);
            auxNum = binarySearch(myArray, auxNum, size);
            printf("Found this number in index %d\n", auxNum);
            break;
        case 2:
            printf("Unsorted Array:\n");
            printArray(myArray, 0, size);
            myArray = mergeSort(myArray, 0, size-1);
            printf("Sorted Array:\n");
            printArray(myArray, 0, size);
            break;
        default:
            break;
        }
    }

}

void printArray(int *array, int start, int size){
    if(array == NULL) return;
    for (int i = start; i < size; i++) printf("%d ", array[i]);
    printf("\n");
}

int binarySearch(int *array, int target, int size){
    if(array == NULL) return -1;
    int left = 0;
    int right = size-1;
    int middle = (right + left)/2;
    do{
        if(array[middle] == target) return middle;
        else if(array[middle] > target) right = middle - 1;
        else left = middle + 1;
        middle = (left + right)/2;
    } while (left <= right);
    return -1;
}

int *mergeSort(int *array, int start, int end) {
    if(array == NULL || start >= end) return array;
    array = mergeSort(array, start, (end+start)/2);
    array = mergeSort(array, (end+start)/2 + 1, end);
    array = merge(array, start, (end+start)/2 + 1, end);
    return array;   
}

int *merge(int *array, int left, int right, int end) {
    if(array == NULL) return NULL;
    else if(right > end || left > right) return array;

    int *tempArray = malloc((1 + end-left)*sizeof(int));
    int l = left, r = right;
    for(int i = 0; i <= end-left; i++){
        if(l > right-1){
            tempArray[i] = array[r];
            r++;
        }
        else if(r > end){
            tempArray[i] = array[l];
            l++;
        }
        else if(array[l] <= array[r]){
            tempArray[i] = array[l];
            l++;
        }
        else{
            tempArray[i] = array[r];
            r++;
        }
    }
    for(int i = 0; i <= end-left; i++) array[i+left] = tempArray[i];
    return array;
}