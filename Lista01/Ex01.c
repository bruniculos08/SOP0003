#include <stdio.h>
#include <string.h>

int main(int argc, char **argv){
    // int sizeOfArg = strlen(argv[1]);
    printf("numOfArg = %i\n", argc);
    printf("Programa: %s\n", argv[0]);
    printf("Parametros:\n");
    for(int i = 1; i < argc; i++){
        printf("%s", argv[i]);
        printf("\n");
    }
}