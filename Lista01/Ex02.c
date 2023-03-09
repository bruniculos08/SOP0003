// Contabits
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    int numOfOneBits = 0;
    int size;
    int *digits = (int *)malloc(sizeof(int));
    // int Q = atoi(argv[1]);
    int Q = atoi(*(argv + 1));
    int R;
    for(int i=0; Q != 0; i++) {
        R = Q%2;
        if(R == 1) numOfOneBits++;
        Q = Q/2;
        digits = realloc(digits, (i+1)*sizeof(int));
        digits[i] = R;
        size = i+1;
    }
    for (int i = 0; i < size; i++){
        printf("%i", digits[size - (i+1)]);
    }
    printf("\nO numero %i possui %i bits em 1", atoi(argv[1]), numOfOneBits);
}