/*
 * Produtor-consumidor com memoria compartilhada e semaforos POSIX.
 * Esta versao coloca produtor e consumidor no mesmo arquivo fonte,
 * usando fork() para criar um processo filho. O produtor sera' o pai,
 * e o consumidor sera' o filho.
 *
 * Obs.: esta versão é a alteração do exemplo, utilizando ao invés de um semáforo nomeado, um semáforo anônimo.
 *
 * Para compilar: gcc -pthread -Wall -o prodcons-proc prodcons-proc.c -lrt
 * ou: gcc prodcons-proc-anonimus.c -Wall -pthread -lrt -o prodcons-proc-anonimus && ./prodcons-proc-anonimus
 */

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <semaphore.h>
#include <signal.h>
#include <stdlib.h>

int sai = 0;

int produz()
{
    int n;
    printf("Indique um numero inteiro (0 encerra): ");
    scanf("%d", &n);
    return n;
}

void sair()
{
    sai = 1;
}

typedef struct Shared_bag {
    sem_t *sem_full, *sem_empty;
    int *ptr;
} shared_bag;


int main(int argc, char *argv[])
{
    shared_bag *backpack;
    pid_t pid;

    // (3) Abre objeto de memoria compartilhada, criando se nao existir:
    int fd = shm_open("/shm", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    if (-1 == fd){
        perror("/shm");
        exit(3);
    }
    // (4) Define o tamanho da região de memoria compartilhada:
    int ret = ftruncate(fd, sizeof(shared_bag));
    if (ret == -1){
        perror("/shm");
        exit(4);
    }
    // (5) Obtem um ponteiro para a regiao de memoria compartilhada:
    backpack = mmap(0, sizeof(shared_bag), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (backpack == MAP_FAILED){
        perror("shm-mmap");
        exit(5);
    }

    int rc;
    backpack->ptr = malloc(sizeof(int));
    backpack->sem_empty = malloc(sizeof(sem_t));
    backpack->sem_full = malloc(sizeof(sem_t));
    
    // (1) Cria o semaforo "full" e o inicializa em 0:
    rc = sem_init(backpack->sem_full, 1, 0);
    printf("Chegou aqui\n");
    if (rc == -1){
        perror("full");
        exit(1);
    }

    // (2) Cria o semaforo "empty" e o inicializa em 1:
    rc = sem_init(backpack->sem_empty, 1, 1);
    if (rc == -1){
        perror("empty");
        exit(2);
    }
    signal(SIGINT, sair);

    pid = fork();
    if (pid == 0){  
        // (6) filho => consumidor:
        while (!sai){
            if (sem_wait(backpack->sem_full) == -1){ // (7) => down(&sem_full) + verificacao de erro:
                perror("sem_wait");
                break;
            }
            printf("Consumindo: %d\n", *(backpack->ptr));
            if (sem_post(backpack->sem_empty) == -1){ // (8) => up(&sem_empty) + verificacao de erro:
                perror("sem_post");
                break;
            }
            if (*(backpack->ptr) == 0) sai = 1;
        }
        exit(0);
    }
    else {
        // (9) pai => produtor:   
        while (!sai){
            if (sem_wait(backpack->sem_empty) == -1){ // (10) => down(&sem_empty) + verificacao de erro:
                perror("sem_wait");
                break;
            }
            *(backpack->ptr) = produz();
            printf("A espera de ser consumido: %d\n\n", *(backpack->ptr));
            if (sem_post(backpack->sem_full) == -1){ // (11) => up(&sem_full) + verificacao de erro:
                perror("sem_post");
                break;
            }
            if (*(backpack->ptr) == 0) sai = 1;
        }
    }

    /*
     * Retirando a chamada `a funcao signal(), este codigo nunca sera'
     * executado. E' preciso fazer rm /dev/shm/sem.{empty,full} /dev/shm/shm
     */

    ret = munmap(backpack, sizeof(shared_bag));
    if (-1 == ret)
        perror("shm-munmap");
    ret = shm_unlink("/shm");
    if (-1 == ret)
        perror("shm-unlink");
    return 0;
}
