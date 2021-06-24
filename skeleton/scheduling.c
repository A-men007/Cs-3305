#include <stdlib.h>
#include <string.h>
#include "scheduling.h"

/*
##  Round-Robin Scheduling Algorithm  ##

	Parameters:-

	queue: 1D int array containing the CPU burst time for every process in a ready queue
	np: number of processes (length of `queue` array)
	tq: time quantum for the RR algorithm


	Returns:-

	rr_result struct pointer, where
	rr_result -> order: 1D int array, containing the execution order of processes (i.e. `(rr_result -> order)[0]` is the process number of the first process)
		** hint: p1 is always the first item in order of selection in round-robin and FCFS
    rr_result -> order_n: int, representing the size of the `order` array, described above ^
	rr_result -> turnarounds: 1D int array, containing the turnaround time for each process (i.e. `(rr_result -> turnarounds)[0]` is the turnaround time for p1)
*/
rr_result *rr(int *queue, int np, int tq){
	rr_result *result = malloc(sizeof(rr_result));
	result->np = np;
	result->turnarounds = malloc(sizeof(int) * np);
    //set buffer size
	int b_size = 100;
    result -> order = malloc(sizeof(int) * b_size);
    result -> order_n = 0;
    int *processTimeRemaining = malloc(sizeof(int) * np);
    int initialTimes[np];
    int time = 0, fin = 0, unfin = 1, i = 0;

    memcpy(processTimeRemaining, queue, sizeof(int) * np);
    while (unfin == 1){
        for (int x = 0; x < np; x++){

            // increment start time of first iteration
            if (i < np)
            {
                initialTimes[i] = time;
            }
            if (processTimeRemaining[x] != 0)
            {
                (result -> order)[i] = x;
                result -> order_n += 1;
                // If time quantum < time remaining
                if (tq < processTimeRemaining[x])
                {
                    //Increment time by time quantum. Decrease time left on process by time quantum
                    time += tq;
                    processTimeRemaining[x] -= tq;
                } else {
                    time += processTimeRemaining[x];
                    (result -> turnarounds)[x] = time - initialTimes[x];
                    processTimeRemaining[x] = 0;
                    fin++;
                }
                i++;
            }
        }
        // If all the processes finished, then exit
        if (fin == np){
            unfin = 0;
            //free up allocated memory
			free(processTimeRemaining);
        }
    }
	return result;
}
