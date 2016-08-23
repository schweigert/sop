#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_THREADS    25

void *Quadrado(void *arg) {
	long ret = (long)arg;
	printf("num = %ld\n", ret);
	pthread_exit((void*)(ret*ret));
}

int main (int argc, char *argv[]) {
	
	pthread_t threads[NUM_THREADS];
	
	int rc;
	long t;
	
	for (t=0; t<NUM_THREADS; t++)
	{
		printf("main: criando thread %ld\n", t);
		rc = pthread_create(&threads[t], NULL, Quadrado, (void *)t);
		if (rc) 
		{
			printf("Erro ao criar a Thread - rc=%d\n", rc);
			exit(-1);
		}
   }
   long resultado = 0;
   long ret = 0;
   for (t=0;t<NUM_THREADS; t++)
   {
	   printf("main: esperando thread %ld\n", t);
	   pthread_join(threads[t], (void*)&ret);
	   resultado += ret;
	   printf("resultado: %ld\n", resultado);
   }
   
   printf ("\n\n\t Resposta: %ld\n", resultado);
   
   /* Ultima coisa que main() deve fazer */
   pthread_exit(NULL); 
   return 0;
}
