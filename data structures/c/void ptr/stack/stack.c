#include "stack.h"

stack *new_stack(size_t elemsize) {
	stack *s = (stack *) malloc(sizeof(stack));
	s->element_size = elemsize;
	s->top = NULL;
	s->size = 0;
	return s;
}

void stack_push(stack *self, void *elem) {
	stack_n *node = (stack_n *) malloc(sizeof(stack_n));
	node->data = malloc(self->element_size);
	memcpy(node->data, elem, self->element_size); // dst, src, size
	node->next = self->top;
	self->top = node;
	++self->size;
}

bool stack_pop(stack *self, void *addr) {
	if (self->size == 0) return false;
	stack_n *n = self->top;
	memcpy(addr, n->data, self->element_size);
	self->top = n->next;
	free(n->data);
	free(n);
	--self->size;
	return true;
}