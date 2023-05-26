#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <dirent.h>

// gcc Ex02.c -o Ex02 && ./Ex02

int listDir(char dir[]);

int main(int argc, char *argv[]){
    // listDir("/home/bruno/SOP/Lista06/");
    listDir("/home/bruno/SOP/");
    // listDir("");
    return 0;
}

int listDir(char dir[]){
    DIR *d;

    if(strcmp(dir, "") == 0) d = opendir(".");
    else d = opendir(dir);
    
    printf("tipo \t| tipo de arquivo\n");
    struct dirent *r;
    r = readdir(d);
    do{
        printf("%d \t| %s\n", r->d_type, r->d_name);
        r = readdir(d);
    }
    while(r != NULL);
    closedir(d);
    return 0;
}