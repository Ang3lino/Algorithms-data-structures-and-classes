
#include "list.h"

// Esta funcion se tendra que modificar de acuerdo a 
// los campos que contenga la estructura element
static bool elementEquals (E e1, E e2) {
	if (e1.Double != e2.Double) 
		return false;
	if (e1.Integer != e2.Integer) 
		return false;
	if (strncmp (e1.String, e2.String, 100) != 0)
		return false;
	return true;
}

List *newList () {
	List *v = (List *) calloc (sizeof (List), 1);
	v->front = 0;
	v->back = 0;
	v->size = 0;
	return v;
}

List *listSetSize (size_t size) {
	List *lista = newList ();
	E *e = calloc (sizeof (E *), 1);
	int i;
	for (i = 0; i < size; i++)
		listPushBack (lista, *e);
	free (e);
	return lista;
}

List *listSubList (List *mainList, size_t lowLim, size_t highLim) {
	List *subList = newList ();
	listNode *node = mainList->front;
	int i = 0;
	if (lowLim < highLim && mainList->size != 0 && highLim < mainList->size) {
		while (i < lowLim) { 
			node = node->next;
			++i;
		}
		listPushBack (subList, node->e);
		while (i < highLim) {
			node = node->next;
			listPushBack (subList, node->e);
			++i;
		} 
	} else {
		perror ("Error at listSubList: Se esta tratando " 
			"de generar una sublista con limites invalido.");
		exit (EXIT_FAILURE);
	}
	return subList;
}

static listNode *newNode (E e) {
	listNode *nuevoNodo = (listNode *) calloc (sizeof (listNode), 1);
	if (nuevoNodo == nil) {
		perror ("Se acabo la memoria chavo :c \n");
		exit (EXIT_FAILURE);
	}
	nuevoNodo->prev = 0;
	nuevoNodo->next = 0;
	nuevoNodo->e = e;
	return nuevoNodo;
}

void listPushBack (List *v, E e) {
	listNode *node = newNode (e);
	if (v->size == 0) { // En el caso de que v sea vacio
		v->front = node;
		v->back = node;  
	} else if (v->size == 1) {
		v->back->next = node;
		node->prev = v->back;
		v->back = v->back->next;
	} else {
		node->prev = v->back;
		v->back->next = node;
		v->back = node;
	}
	v->size++;
}

void listPushFront (List *v, E e) {
	listNode *node = newNode (e);
	if (v->size == 0) { 
		v->front = node;
		v->back = node; 
	} else {
		node->next = v->front;
		v->front->prev = node;
		v->front = node;
	}
	v->size++;
}

// En caso de que index sea mayor que el v->size, se pondra el elemento al final
void listAdd (List *v, size_t index, E element) {
	if (index == 0) 
		listPushFront (v, element);
	else if (index >= v->size)
		listPushBack (v, element);
	else {
		listNode *node = newNode (element);
		int pos = 0;
		listNode *ptr = v->front;
		while (pos < index) {
			ptr = ptr->next;
			pos++;
		}
		node->next = ptr;
		node->prev = ptr->prev;
		ptr->prev->next = node;
		ptr->prev = node;
		v->size++;
	} 
}

bool listSet (List *lista, size_t index, E e) {
	if (index < lista->size) {
		int i = 0;
		listNode *ptr;
		if (index < lista->size / 2) {
			ptr = lista->front;
			while (i < index) {
				ptr = ptr->next;
				i++;
			}
			ptr->e = e;
		} else {
			ptr = lista->back;
			i = lista->size - 1;
			while (i > index) {
				ptr = ptr->prev;
				i--;
			}
			ptr->e = e;
		}
		return true;
	}
	return false;
}

E listGet (List *v, size_t index) {
	listNode *ptr = v->front;
	if (v->size != 0 && index < v->size) {
		int i = 0;
		while (i < index) {
			ptr = ptr->next;
			++i;
		}	
	} else {
		perror ("Error at listGet: Se esta consultando un elemento"
				"con un indice mayor a la capacidad del list. \n");
		exit (EXIT_FAILURE); 
	}
	return ptr->e;
}

E listPopFront (List *list) {
	E e;
	listNode *del = list->front;
	if (list->size) {
		if (list->size == 1) {
			del = list->front;
			e = del->e;
			list->front = nil;
			list->back = nil;
		} else {
			del = list->front;
			e = del->e;
			list->front = del->next;
			list->front->prev = nil;
		}	
		free (del);
		list->size--;
    }
	return e;
}

E listPopBack (List *list) {
	listNode *del;
	E e;
	if (list->size) {
		del = list->back;
		e = del->e;
		if (list->size == 1) {
			list->back = nil;
			list->front = nil;
		} else { 
			list->back->prev->next = nil;
			list->back = list->back->prev;
		}
		--list->size; 
		free (del);
	}
	return e;
}

void listDelete (List *list, size_t index) { 
	if (list->size != 0) {
		listNode *del;
		if (index == 0) // borramos el principio
			listPopFront (list);
		else if (index < list->size - 1) { // Borramos en medio
			int i = 0;
			listNode *ptr = list->front;
			while (i < index) {
				ptr = ptr->next;
				i++;
			}
			del = ptr;
			ptr->next->prev = ptr->prev;
			ptr->prev->next = ptr->next;
			--list->size;
			free (del);
		} else // Borramos el final 
			listPopBack (list);
	}
}

void listClean (List *list) {
	while (list->size) 
		listPopBack (list);
}

// Se retorna el puntero al nodo de la lista que contenga al 
// elemento, en caso contratio, retornamos null 
static listNode *getNode (List *list, E e) {
	if (list->size) {
		listNode *ptr = list->front;
		while (ptr) {
			if (elementEquals (ptr->e, e))
				return ptr;
			ptr = ptr->next;
		}
	} 
	return nil;
}

bool listContains (List *lista, E e) {
	if (getNode (lista, e))
		return true;
	return false;
}

bool listRemove (List *list, E e) {
	if (list->size) {
		listNode *del = getNode (list, e);
		if (del == nil) 
			return false;
		if (del->prev == nil) 
			listPopFront (list);
		else if (del->next == nil) 
			listPopBack (list);
		else {
			del->next->prev = del->prev;
			del->prev->next = del->next;
			--list->size;
			free (del);
		}		
		return true;
	}
	return false;
}

// Se retornara -1 en caso de que e no pertenezca a al lista
int listIndexOf (List *lista, E e) {
	if (lista->size >= 0) {
		int i = 0;
		listNode *current = lista->front;
		while (current) {
			if (elementEquals (e, current->e))
				return i;
			current = current->next;
			i++;
		}
	}	
	return -1;
}

