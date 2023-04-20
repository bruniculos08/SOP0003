#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <semaphore.h>
#include <signal.h>
#include <stdlib.h>


int n = 1;

int main(void){
    int *ptr, rc, fd, son;

    fd = shm_open("/shm", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    if (fd == -1) exit(1);
    rc = ftruncate(fd, sizeof(int)*100);
    if (rc == -1) exit(2);
    ptr = mmap(NULL, sizeof(int)*100, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (ptr == MAP_FAILED) exit(3);

    son = fork();

    if(son == 0){
        int sum = 0;
        for(int i = 0; i < 1000; i++){
            ptr[i] = i;
            printf("%i\n", ptr[i]);
        }
    }

    if(son != 0) printf("pai aqui (filho = %i)\n", son);
    else printf("filho aqui (son = %i)\n", son);

    return 0;
}