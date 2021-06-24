#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>
#include <pthread.h>

int x, y, z;

void* sum() {
	z = y + x;
	return NULL;
}

int main() {

	// Initializing the global variables
	x = 10, y = 20, z = 0;

	/* Add code under every comment to demonstrate differences between child and thread */
	//create child
	pid_t pid = fork();

	//fork error handling...
	if (pid == -1) {
		printf("main function: errno number is %d\n", errno);
	}
	else if (pid > 0) {
		//wait for child, and print value of z
		wait(NULL);

		printf("Using a fork(), the value of z in the parent process is: %d\n", z); //value of z after the fork process won't change
		// create thread, wait for it to complete, then print value of z
		
		pthread_t thrd;

		pthread_create(&thrd, NULL, sum, NULL);

		pthread_join(thrd, NULL);

		printf("Using a thread, the value of z is: %d\n", z); //value of z after passing to the thread will change
	}

	else if (pid == 0) {
		// sum x and y and store it in z
		z = x + y;
		// print value of z
		printf("Using a fork(), the value of z in the child process is: %d\n", z);
	}
	return 0;
}
