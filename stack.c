#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include "stack.h"

enum StackType{
	LIFO=0,
	FIFO=1
};

void smemcpy(char* dst, char* src, size_t n){
	if (n % 4 != 0)
		while(n--) *dst++ = *src++;
	else
		while(n -= 4) *(int*)dst++ = *(int*)src++;
} 

int stack_lifo_new(struct Stack* stack, size_t initial_size){
	void* ptr = calloc(sizeof(char), initial_size);
	if (!ptr) return -1;
	stack->sptr = ptr + initial_size;
	stack->bptr = stack->sptr;
	stack->srcptr = ptr;
	stack->size = 0;
	stack->allocated = initial_size;
	stack->type = LIFO;
	return 0;
}

int stack_fifo_new(struct Stack* stack, size_t initial_size){
	void* ptr = calloc(sizeof(char), initial_size);
	if (!ptr) return -1;
	stack->sptr = ptr + initial_size;
	stack->bptr = ptr + initial_size;
	stack->srcptr = ptr;
	stack->size = 0;                         
	stack->allocated = initial_size;
	stack->type = FIFO;
	return 0;
}

int stack_push(struct Stack* stack, void* element, size_t elementsize){
	if (stack->allocated - stack->size < elementsize) return -1;
	stack->sptr -= elementsize;
	memcpy(stack->sptr, element, elementsize);
	stack->size += elementsize;
	return 0;
}

int stack_pop(struct Stack* stack, void* element, size_t elementsize){
	if (stack->size < elementsize) return -1;
	if (stack->type == LIFO){
		memcpy(element, stack->sptr, elementsize);
        	stack->sptr += elementsize;
        	stack->size -= elementsize;
        	return 0;
	}
    	else if (stack->type == FIFO){
        	memcpy(element, stack->sptr - elementsize, elementsize);
        	stack->size -= elementsize;
		stack->sptr += elementsize;
        	smemcpy((char*)stack->sptr, (char*)stack->sptr - elementsize, stack->size);
		return 0;
    	} 
	return -1;
}

int stack_peek(struct Stack* stack, void* element, size_t elementsize){
	if (stack->size < elementsize) return -1;
	if (stack->type == LIFO)
		memcpy(element, stack->sptr, elementsize);
	else if (stack->type == FIFO)
		memcpy(element, stack->sptr - elementsize, elementsize);
	return 0;
}

int is_empty(struct Stack* stack){
	if (stack->sptr == stack->bptr)
		return 1;
	return 0;
}
int is_full(struct Stack* stack){
	if (stack->bptr - stack->sptr == stack->allocated)
		return 1;
	return 0;
}

void stack_destroy(struct Stack* stack){
	free(stack->srcptr);
	memset(stack, 0x00, sizeof(struct Stack));
}
