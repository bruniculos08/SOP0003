#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>

int copyFile(char original[], char copy[]);

int main(int argc, char *argv[]){
    copyFile("something.txt", "copyOfSomething.txt");
    return 0;
}

int copyFile(char original[], char copy[]){
    int fileOrig = open(original, O_RDONLY | O_CREAT);
    if(fileOrig == -1){
        perror("Failed to open file!\n");
    }
    else{
        printf("File opened with success!\n");
    }

    struct stat modeOrig;
    stat(original, &modeOrig); 

    int fileNew = open(copy, O_CREAT | O_TRUNC | O_WRONLY, modeOrig.st_mode);
    if(fileNew == -1){
        perror("Failed to open file!\n");
    }
    else{
        printf("File opened with success!\n");
    }   

    long bufferSize = modeOrig.st_blksize;
    printf("Buffer Size = %ld\n", bufferSize);

    char text[bufferSize];
    int n = read(fileOrig, text, bufferSize);
    write(fileNew, text, n);
    return 0;
}