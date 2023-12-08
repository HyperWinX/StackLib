#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "stack.h"

int main(){
	struct Stack stack;
	clock_t start, end, lstack_init, fstack_init, rnd_gen, lpush_time, fpush_time, lverification_time, fverification_time;
	double cputime;
	uint64_t stack_failures = 0;
	start = clock();
	printf("Testing LIFO stack\n");
	printf("Initializing 1GB stack\n");
	stack_lifo_new(&stack, 1024 * 1024 * 1024);
	int* arr = calloc(256 * 1024 * 1024, sizeof(int));
	lstack_init = clock();
	srand(time(NULL));
	printf("Generating random numbers...\n");
	for (int i = 0; i < 256 * 1024 * 1024; i++) arr[i] = rand();
	rnd_gen = clock();
	printf("Pushing data...\n");
	for (int i = 0; i < 256 * 1024 * 1024; i++)
		stack_push(&stack, (void*)&arr[i], sizeof(int));
	lpush_time = clock();
	printf("Verifying data...\n");
	for (int i = 0; i < 32 * 1024 * 1024; i++){
		int num;
		stack_pop(&stack, &num, sizeof(int));
		if (num != arr[(256 * 1024 * 1024) - i - 1]) stack_failures++;
	}
	lverification_time = clock();
	free(stack.srcptr);
	printf("Testing FIFO stack\n");
	printf("Initializing 1GB stack\n");
	stack_lifo_new(&stack, 1024 * 1024 * 1024);
	fstack_init = clock();
	printf("Pushing data...\n");
	for (int i = 0; i < 256 * 1024 * 1024; i++)
		stack_push(&stack, (void*)&arr[i], sizeof(int));
	fpush_time = clock();
	printf("Verifying data...\n\n");
	for (int i = 0; i < 256 * 1024 * 1024; i++){
		int num;
		stack_pop(&stack, &num, sizeof(int));
		if (num != arr[(256 * 1024 * 1024) - i - 1]) stack_failures++;
	}
	end = clock();
	printf("Statistics:\n");
	printf("LIFO stack init time:   %fs\n", ((double)(lstack_init - start)) / CLOCKS_PER_SEC);
	printf("Size of LIFO stack:     1GB\n");
	printf("Random number gen time: %fs\n", ((double)(rnd_gen - lstack_init)) / CLOCKS_PER_SEC);
	printf("Random numbers count:   %d\n", 256*1024*1024);
	printf("LIFO stack push time:   %fs\n", ((double)(lpush_time - rnd_gen)) / CLOCKS_PER_SEC);
	printf("Verification time:      %fs\n", ((double)(lverification_time - lpush_time)) / CLOCKS_PER_SEC);
	printf("FIFO stack init time:   %fs\n", ((double)(fstack_init - lverification_time)) / CLOCKS_PER_SEC);
	printf("Size of FIFO stack:     1GB\n");
	printf("FIFO stack push time:   %fs\n", ((double)(fpush_time - fstack_init)) / CLOCKS_PER_SEC);
	printf("Verification time:      %fs\n\n", ((double)(end - fpush_time)) / CLOCKS_PER_SEC);
	printf("Total time:             %fs\n", ((double)(end - start)) / CLOCKS_PER_SEC);
	printf("Clear working time:     %fs\n", (((double)(end - start)) / CLOCKS_PER_SEC) - ((double)(rnd_gen - lstack_init) / CLOCKS_PER_SEC));
	return 0;
}

