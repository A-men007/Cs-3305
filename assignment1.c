#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>

int main(int argc, char **argv)
{
	/************************************************** command line arguments ***********************************************
		For the purposes of this explanation, assume that "external_program.out" is located in /home/usr/A1/external_program.out

		When you are testing your program, replace "/home/usr/A1/external_program.out" with the path to the executable file
		generated when you compile "external_program.c"

		To compile assignment1.c: gcc assignment1.c -o assignment1
		To run your program: ./assignment1 /home/usr/A1/external_program.out
		argv[0] = "./assignment1"
		argv[1] = "/home/usr/A1/external_program.out"

		Number of arguments (argc) = 2

		In this assignment, the path to the external program is in argv[1]
	*************************************************************************************************************************/

	// If the path of external_program.out isn't provided by the user, the program will terminate
	if (argc != 2)
	{
		printf("Invalid arguments\n");
		exit(0);
	}

	pid_t i, j, PID;
	PID = fork();
	if (PID < 0) {
		printf("fork unsuccessful 1 \n");
	}

	// You must insert the following into your code (Replace zeros with the appropriate values/variables)
	//if fork success parent
	if (PID > 0) {
		printf("parent process (PID %d) created child_1 (PID %d) \n", getpid(), PID);
		printf("parent (PID %d) is waiting for child_1 (PID %d) to complete before creating child_2\n", getpid(), PID);
	}

	//child
	if (PID == 0) {
		i = fork();
		printf("child_1 (PID %d) created child_1.1 (PID %d)\n", getppid(), i);
		if (i > 0) {
		printf("child_1 (PID %d) is now complete\n", getpid());
		exit(0);
		}
		exit(0);
	}
	wait(NULL);


	j=fork();
	if (j > 0) {
	char buffer[40];
	printf("parent (PID %d) created child_2 (PID %d)\n", getpid(), j);
	printf("child_2 (PID %d) is calling an external program external_program.out and leaving child_2..\n", j);
	snprintf(buffer, 20, "%d", j);
	execl(argv[1], "external_program.out", buffer, NULL);
	exit(0);
	}
	// Hint: You might find snprintf() helpful in this assignment

	return 0;
}