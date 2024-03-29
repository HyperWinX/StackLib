#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "stack.h"

void display_help(char *name){
	printf("Usage: %s <size_in_MB>\n", name);
	exit(0);
}

int main(int argc, char *argv[]){
	if (argc != 2) display_help(argv[0]);
	int32_t size;
	if ((size = atoi(argv[1])) == 0){
		printf("Passed incorrect string or zero.\n");
		exit(1);
	}
	int32_t stack_sz = size*1024*1024;
	int32_t numcount = (int32_t)(stack_sz/4);
	struct Stack stack;
	clock_t start, end, lstack_init, fstack_init, rnd_gen, lpush_time, fpush_time, lverification_time, fverification_time;
	double cputime;
	int is_empty_success, is_full_success, peek_success;
	uint64_t lifo_failures = 0, fifo_failures = 0;
	start = clock();
	printf("Testing LIFO stack\n");
	printf("Initializing stack\n");
	stack_lifo_new(&stack, stack_sz);
	int* arr = calloc(stack_sz, sizeof(int));
	lstack_init = clock();
	srand(time(NULL));
	printf("Generating random numbers...\n");
	for (int i = 0; i < numcount; i++) arr[i] = rand();
	rnd_gen = clock();
	printf("Pushing data...\n");
	for (int i = 0; i < numcount; i++)
		stack_push(&stack, (void*)&arr[i], sizeof(int));
	lpush_time = clock();
	printf("Verifying data...\n");
	for (int i = 0; i < numcount; i++){
		int num;
		stack_pop(&stack, &num, sizeof(int));
		if (num != arr[numcount - i - 1]) lifo_failures++;
	}
	lverification_time = clock();
	stack_destroy(&stack);
	printf("Testing FIFO stack\n");
	printf("Initializing stack\n");
	stack_lifo_new(&stack, stack_sz);
	fstack_init = clock();
	printf("Pushing data...\n");
	for (int i = 0; i < numcount; i++)
		stack_push(&stack, (void*)&arr[i], sizeof(int));
	fpush_time = clock();
	printf("Verifying data...\n");
	for (int i = 0; i < numcount; i++){
		int num;
		stack_pop(&stack, &num, sizeof(int));
		if (num != arr[(numcount) - i - 1]) fifo_failures++;
	}
	stack_destroy(&stack);
	stack_lifo_new(&stack, 4);
	int val = rand();
	if (is_empty(&stack)) is_empty_success = 1;
	else is_empty_success = 0;
	stack_push(&stack, &val, sizeof(val));
	int peeked = 0;
	stack_peek(&stack, &peeked, sizeof(peeked));
	if (peeked == val) peek_success = 1;
	else peek_success = 0;
	if (is_full(&stack)) is_full_success = 1;
	else is_full_success = 0;
	end = clock();
	printf("Statistics:\n");
	printf("LIFO stack init time:   %fs\n", ((double)(lstack_init - start)) / CLOCKS_PER_SEC);
	printf("Size of LIFO stack:     %dMB\n", stack_sz/1024/1024);
	printf("Random number gen time: %fs\n", ((double)(rnd_gen - lstack_init)) / CLOCKS_PER_SEC);
	printf("Random numbers count:   %d\n", numcount);
	printf("LIFO stack push time:   %fs\n", ((double)(lpush_time - rnd_gen)) / CLOCKS_PER_SEC);
	printf("Verification time:      %fs\n", ((double)(lverification_time - lpush_time)) / CLOCKS_PER_SEC);
	printf("Total failures:         %lu\n", lifo_failures);
	printf("FIFO stack init time:   %fs\n", ((double)(fstack_init - lverification_time)) / CLOCKS_PER_SEC);
	printf("Size of FIFO stack:     %dMB\n", stack_sz/1024/1024);
	printf("FIFO stack push time:   %fs\n", ((double)(fpush_time - fstack_init)) / CLOCKS_PER_SEC);
	printf("Verification time:      %fs\n", ((double)(end - fpush_time)) / CLOCKS_PER_SEC);
	printf("Total failures:         %lu\n", fifo_failures);
	printf("IsEmpty success:        %s\n", is_empty_success == 1 ? "Yes" : "No");
	printf("IsFull success:         %s\n", is_full_success == 1 ? "Yes" : "No");
	printf("Peek() success:         %s\n", peek_success == 1 ? "Yes" : "No");
	printf("Total time:             %fs\n", ((double)(end - start)) / CLOCKS_PER_SEC);
	printf("Clear working time:     %fs\n", (((double)(end - start)) / CLOCKS_PER_SEC) - ((double)(rnd_gen - lstack_init) / CLOCKS_PER_SEC));
	return 0;
}

