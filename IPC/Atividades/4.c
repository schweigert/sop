#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <semaphore.h>
#include <signal.h>
#include <assert.h>

#define MAX 2000

int *n;
sem_t *sem;

void f1(){
	puts("Processo filho");
	int i = 0, temp, rc;
	for (i = 0; i < MAX; i++){
		rc = sem_wait(sem); assert(rc == 0);
		puts("FILHO!");
		temp = *n;
		temp++;
		*n = temp;
		rc = sem_post(sem); assert(rc == 0);
	}
}

void f2(){
	puts("Processo pai");
	int i = 0, temp, rc;
	for (i = 0; i < MAX; i++){
		rc = sem_wait(sem); assert(rc == 0);
		puts("PAI!");
		temp = *n;
		temp--;
		*n = temp;
		rc = sem_post(sem); assert(rc == 0);
	}
}

int main (void){


	// Memoria Compartilhada
	puts("Memória criada");
	int fd = shm_open("/shm", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
	if ( fd == -1 ) exit(1);
	
	int ret = ftruncate (fd, sizeof(int));
	if ( ret == -1 ) exit(2);

	n = mmap(0, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	if ( n == MAP_FAILED) exit(3);

	// Semáforo
	puts("Criando semáforo");
	sem = sem_open("/sem", O_CREAT, 0664, 1);
	if (sem == SEM_FAILED) exit (4);

	pid_t f;
	int status;
	puts("Fork");
	f = fork();
	if (f == 0){
		f1();
		exit(0);
	} else {
		f2();
		waitpid(f, &status, 0);
	}
	printf ("n = %d\n", *n);

	return 0;

}


