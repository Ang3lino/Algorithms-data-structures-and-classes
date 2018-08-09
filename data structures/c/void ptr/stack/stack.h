#ifndef __STACK_H__
#define __STACK_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>

// stack node
typedef struct stack_n {
	struct stack_n *next;
	void *data;
} stack_n;

typedef struct stack {
	stack_n *top;
	size_t size;
	size_t element_size;
} stack;

stack *new_stack(size_t elemsize); 
void stack_push(stack *self, void *elem); 
bool stack_pop(stack *self, void *addr); 

#endif