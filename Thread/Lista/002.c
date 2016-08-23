#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <pthread.h>

#define T_PAR 1
#define T_IMPAR 2

#define NELEM 2000000

int *v;

void *conta(char tipo) 
{
     int i, total = 0;
     
     for (i = 0; i < NELEM; i++) {
	  if ((tipo == T_PAR) && ((v[i] % 2) == 0))
	      total++;
	  else if ((tipo == T_IMPAR) && ((v[i] % 2) != 0))
	       total++;
     }
     pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
     int i, pares, impares, rc;
     struct timeval tv_ini, tv_fim;
     unsigned long time_diff, sec_diff, usec_diff, msec_diff;

	 v = (int*)malloc(sizeof(int)*NELEM);

     srandom(time(NULL));
     for (i = 0; i < NELEM; i++) {
	  v[i] = (int)random();
     }
     
     /* marca o tempo de inicio */
     rc = gettimeofday(&tv_ini, NULL);
     if (rc != 0) {
	  perror("erro em gettimeofday()");
	  exit(1);
     }




     /* faz o processamento de interesse */
     
     
     pthread_t pares_t;
     if (pthread_create(&pares_t, NULL, (void*)conta, (void *)T_PAR))
     {
		 puts("Erro ao criar a thread 1!");
	     return 0;
	 }
     pthread_t impares_t;
     if (pthread_create(&impares_t, NULL, (void*)conta, (void *)T_IMPAR))
     {
		 puts("Erro ao criar a thread 2!");
	     return 0;
	 }

	
	 pthread_join(pares_t, NULL);
	 pthread_join(impares_t, NULL);



     /* marca o tempo de final */
     rc = gettimeofday(&tv_fim, NULL);
     if (rc != 0) {
	  perror("erro em gettimeofday()");
	  exit(1);
     }
     /* calcula a diferenca entre os tempos, em usec */
     time_diff = (1000000L*tv_fim.tv_sec + tv_fim.tv_usec) - 
  	         (1000000L*tv_ini.tv_sec + tv_ini.tv_usec);
     /* converte para segundos + microsegundos (parte fracionária) */
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
