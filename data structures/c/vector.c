
#include "vector.h"

Vector *newVector () {
	Vector *v = (Vector *) calloc (sizeof (Vector), 1);
	v->front = 0;
	v->back = 0;
	v->size = 0;

	return v;
}

static vectorNode *newNode (E e) {
	vectorNode *nuevoNodo = (vectorNode *) calloc (sizeof (vectorNode), 1);
	nuevoNodo->prev = 0;
	nuevoNodo->next = 0;
	nuevoNodo->e = e;
	
	return nuevoNodo;
}

void vectorPushBack (Vector *v, E e) {
	vectorNode *node = newNode (e);
	if (v->front == nil) { // En el caso de que v sea vacio
		v->front = node;
		v->back = node;  
	}
	node->prev = v->back;
	v->back->next = node;
	v->back = node;
}

void vectorPushFront (Vector *v, E e) {
	vectorNode *node = newNode (e);
	if (v->front == nil) { // En el caso de que v sea vacio
		v->front = node;
		v->back = node; 
	}
	node->next = v->front;
	v->front->prev = node;
	v->front = node;
}

void vectorAdd (Vector *v, int index, E element) {
	if (v->front == nil && index == 0) {
		vectorNode *node = newNode (element);
		v->front = node;
		v->back = node; 
	} else if (index == 0) 
		vectorPushFront (v, element);
	else if (index >= v->size - 1)
		vectorPushBack (v, element);
	else {
		vectorNode *node = newNode (element);
		int pos = 0;
		vectorNode *ptr = v->front;
		while (pos < index) {
			ptr = ptr->next;
			pos++;
		}
		node->next = ptr;
		node->prev = ptr->prev;
		ptr->prev->next = node;
		ptr->prev = node;
	} 
	v->size++;
}

E vectorGet (Vector *v, int index) {
	vectorNode *ptr = v->front;
	int i = 0;
	while (ptr != nil && i < index) {
		ptr = ptr->next;
		++i;
	}
	if (ptr == nil) {
		perror ("Error at vectorGet: Se esta consultando un elemento con un indice mayor a la"
				"capacidad del vector. \n");
		exit (EXIT_FAILURE); 
	}
	return ptr->e;
}





		
