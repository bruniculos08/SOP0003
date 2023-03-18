#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <pthread.h>

#define T_PAR 1
#define T_IMPAR 2

#define NELEM 2000000
int pares, impares;

int conta(int *v, char tipo) 
{
     int i, total = 0;
     
     for (i = 0; i < NELEM; i++) {
	  if ((tipo == T_PAR) && ((v[i] % 2) == 0))
	      total++;
	  else if ((tipo == T_IMPAR) && ((v[i] % 2) != 0))
	       total++;
     }
     return total;
}

void *contaThread(void *arg){
    int **tupla = (int**) arg;
    int tipo = tupla[1][0]; 
    int *vetor = tupla[0];
    printf("tipo: %i\n", tipo);

     int i, total = 0;
     
     for (i = 0; i < NELEM; i++) {
	  if ((tipo == T_PAR) && ((vetor[i] % 2) == 0))
	      total++;
	  else if ((tipo == T_IMPAR) && ((vetor[i] % 2) != 0))
	       total++;
     }
     
     if(tipo == T_IMPAR) impares = total;
     else pares = total;
}

int main(int argc, char *argv[])
{
     int vetor[NELEM], i, rc;
     struct timeval tv_ini, tv_fim;
     unsigned long time_diff, sec_diff, usec_diff, msec_diff;

     srandom(time(NULL));
     for (i = 0; i < NELEM; i++) {
	  vetor[i] = (int)random();
/*	  vetor[i] = i*2;*/
     }
     
     /* marca o tempo de inicio */
     rc = gettimeofday(&tv_ini, NULL);
     if (rc != 0) {
	  perror("erro em gettimeofday()");
	  exit(1);
     }

     /* faz o processamento de interesse */

     // (1) Sequencial:
     // pares = conta(vetor, T_PAR);
     // impares = conta(vetor, T_IMPAR);

     // (2) Multi-thread:
     pthread_t threads[2];
     int **tuplaPar = malloc(sizeof(int*) * 2);
     tuplaPar[0] = vetor;
     tuplaPar[1] = malloc(sizeof(int));
     tuplaPar[1][0] = T_PAR;
     pthread_create(&threads[0], NULL, contaThread, (void *)tuplaPar);

     int **tuplaImpar = malloc(sizeof(int*) * 2);
     tuplaImpar[0] = vetor;
     tuplaImpar[1] = malloc(sizeof(int));
     tuplaImpar[1][0] = T_IMPAR;
     pthread_create(&threads[1], NULL, contaThread, (void *)tuplaImpar);

     pthread_join(threads[0], NULL);
     pthread_join(threads[1], NULL);

     /* marca o tempo de final */
     rc = gettimeofday(&tv_fim, NULL);
     if (rc != 0) {
	  perror("erro em gettimeofday()");
	  exit(1);
     }
     /* calcula a diferenca entre os tempos, em usec */
     time_diff = (1000000L*tv_fim.tv_sec + tv_fim.tv_usec) - 
  	         (1000000L*tv_ini.tv_sec + tv_ini.tv_usec);
     /* converte para segundos + microsegundos (parte fracion�ria) */
     sec_diff = time_diff / 1000000L;
     usec_diff = time_diff % 1000000L;
     
     /* converte para msec */
     msec_diff = time_diff / 1000;
     
     printf("O vetor tem %d numeros pares e %d numeros impares.\n", pares,
	    impares);
/*     printf("Tempo de execucao: %lu.%06lu seg\n", sec_diff, usec_diff);*/
     printf("Tempo de execucao: %lu.%03lu mseg\n", msec_diff, usec_diff%1000);
     return 0;
}
