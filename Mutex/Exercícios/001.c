/* Exercicio 6 da lista de pthreads */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <pthread.h>

#define MAX 2000

int n;

pthread_mutex_t the_mutex;


void f1(void *argp)
{
    int i, temp;

    for (i = 0; i < MAX; i++) {
		pthread_mutex_lock(&the_mutex);
		
		temp = n;
		temp++;
		n = temp;
		
		pthread_mutex_unlock(&the_mutex);
    }
}

void f2(void *argp)
{
    int i, temp;

    for (i = 0; i < MAX; i++) {
		pthread_mutex_lock(&the_mutex);
		
		temp = n;
		temp--;
		n = temp;
		
		pthread_mutex_unlock(&the_mutex);
    }
}

int main(void)
{
    pthread_t t1, t2;

	pthread_mutex_init(&the_mutex, NULL);


    n = 0;
    pthread_create(&t1, NULL, (void *) f1, NULL);
    pthread_create(&t2, NULL, (void *) f2, NULL);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    
    
    pthread_mutex_destroy(&the_mutex);
    printf("n=%d\n", n);
    return 0;
}
