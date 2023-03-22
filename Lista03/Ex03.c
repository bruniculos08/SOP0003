#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_THREADS 5

void *PrintHello(void *arg) {
   long tid = (long)arg;
   printf("Alo da thread %ld\n", tid);
   pthread_exit((void *)tid);
}

int main (int argc, char *argv[]) {
   // (1) Cria-se um vetor de threads:
   pthread_t threads[NUM_THREADS];
   int rc;
   void *status;
   int sum = 0;
   long t;
   // (2) Criando uma thread para cada espaço do vetor:
   for (t=0; t<NUM_THREADS; t++){
      printf("main: criando thread %ld\n", t);
      rc = pthread_create(&threads[t], NULL, PrintHello, (void *)t);
      // (2.1) Para que a thread que está rodando esta linha espere pela thread t criada:
      rc = pthread_join(threads[t], &status);
      sum += (int) ((long) status);
      // (2.2) Se rc == 1 então a thread não foi criada:
      if (rc) {
         printf("ERRO - rc=%d\n", rc);
         exit(-1);
      }
   }
   /* Ultima coisa que main() deve fazer */
   printf("sum = %i\n", sum);
   pthread_exit(NULL); 
}
