#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <pthread.h>

int n = 1;

// X -> Z -> Y

void X() {
	n *= 16;
}

void Y() {
	n /= 7;
}

void Z() {
	n += 40;
}

int main(void){
	
	
	
	return 0;
}

