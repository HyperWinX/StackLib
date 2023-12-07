#include <stdlib.h>
#include <stdint.h>
#include "stack.h"

enum StackType{
	LIFO=0,
	FIFO=1
};

void dmp(struct Stack* stack){
	for (int i = 0; i < stack->size; i++) printf("%d\n", *((char*)stack->bptr + i));
	printf("\n");
}

void smemcpy(char* dst, char* src, size_t n){
    while(n--) *dst++ = *src++;
} 

void stack_lifo_new(struct Stack* stack, size_t initial_size){
	void* ptr = calloc(sizeof(char), initial_size);
	printf("Initial size: %zu\n", initial_size);
	if (!ptr) return;
	stack->sptr = ptr + initial_size;
	stack->bptr = stack->sptr;
	stack->srcptr = ptr;
	stack->size = 0;
	stack->allocated = initial_size;
	stack->type = LIFO;
}

void stack_fifo_new(struct Stack* stack, size_t initial_size){                                                   void* ptr = calloc(sizeof(char), initial_size);                                                     if (!ptr) return;
    stack->sptr = ptr + initial_size;
    stack->bptr = ptr + initial_size;
    stack->srcptr = ptr;
    stack->size = 0;                                  
    stack->allocated = initial_size;
    stack->type = FIFO;                      
}

int stack_push(struct Stack* stack, void* element, size_t elementsize){
	if (stack->allocated - stack->size < elementsize) return -1;
	//dmp(stack);
    stack->bptr -= elementsize;
    memcpy(stack->bptr, element, elementsize);
    stack->size += elementsize;
    //dmp(stack);
    return 0;
}

int stack_pop(struct Stack* stack, void* element, size_t elementsize){
	if (stack->size < elementsize) return -1;
	if (stack->type == LIFO){
		//dmp(stack);
		memcpy(element, stack->bptr, elementsize);        
        stack->bptr += elementsize;                       
        stack->size -= elementsize;
	//dmp(stack);
        return 0;
	}
    else if (stack->type == FIFO){
        memcpy(element, stack->sptr - elementsize, elementsize);
        stack->size -= elementsize;
	stack->bptr += elementsize;
        smemcpy((char*)stack->bptr, (char*)stack->bptr - elementsize, stack->size);
	return 0;
    } 
	return -1;
}

