#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <semaphore.h>
#include <signal.h>
#include <stdlib.h>

typedef struct Bag{
    int n;
    sem_t sy, sz;
} bag;

bag *stuff;

// Aqui cheguei na conclusão de que um mutex é simulado por um semáforo que começa em 1;

void X(){
    stuff->n = stuff->n*16;
    sem_post(&stuff->sz);
}

void Y(){
    sem_wait(&stuff->sy);
    stuff->n = stuff->n/7;
}

void Z(){
    sem_wait(&stuff->sz);
    stuff->n = stuff->n+40;
    sem_post(&stuff->sy);
}

int main(void){

    int fd = shm_open("/shm", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    int ret = ftruncate(fd, sizeof(bag));
    stuff = mmap(0, sizeof(bag), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    
    sem_init(&stuff->sz, 1, 0);
    sem_init(&stuff->sy, 1, 0);
    
    stuff->n = 1;

    int son;

    son = fork();
    if(son == 0){
        Y();
        printf("n = %i\n", stuff->n);
        printf("FIM\n");
    }
    else{
        X();
        Z();
    }
    return 0;
}

