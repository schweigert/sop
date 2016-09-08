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

#define MAX 2000

int *n;
sem_t *sem;

void f1(){
	int i = 0, temp;
	for (i = 0; i < MAX; i++){
		if (sem_wait(sem) == -1) exit (10);
		temp = *n;
		temp++;
		*n = temp;
		if (sem_post(sem) == -1) exit (11);
	}
}

void f2(){
	int i = 0, temp;
	for (i = 0; i < MAX; i++){
		if (sem_wait(sem) == -1) exit (12);
		temp = *n;
		temp--;
		*n = temp;
		if (sem_post(sem) == -1) exit (13);
	}
}

int main (void){


	// Memoria Compartilhada

	int fd = shm_open("/shm", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
	if ( fd == -1 ) exit(1);
	
	int ret = ftruncate (fd, sizeof(int));
	if ( ret == -1 ) exit(2);

	n = mmap(0, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	if ( n == MAP_FAILED) exit(3);

	// Semáforo

	sem = sem_open("/sem", O_CREAT, 0664, 0);
	if (sem == SEM_FAILED) exit (4);

	pid_t f;
	int status;

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


