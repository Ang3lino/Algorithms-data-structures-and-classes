
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
	node->prev = v->back;
	v->back->next = node;
	v->back = node;
}

void vectorAdd (Vector *v, int index, E element) {
	vectorNode *node = newNode (element);
	if (v == nil && index == 0) {
		v->front = node;
		v->back = node; 
	} else if (index >= v->size)
		vectorPushBack (v, element);
	else if (index < v->size) {
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
		if (index == 0) 
			v->front = node;
		if (index == v->size - 1)
			v->back = node;
	} else {
		perror ("Error at vectorAdd: Se esta insertando un elemento en un indice invalido. \n");
		exit (EXIT_FAILURE);
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





		
