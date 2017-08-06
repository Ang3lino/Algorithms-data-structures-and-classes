
#include "vector.h"

Vector *
newVector (void) {
    Vector *v = malloc (sizeof (Vector));
    v->capacity = 2;
    v->size = 0;
    v->item = calloc (sizeof (void *), v->capacity);
    return v;
}

static void 
resize (Vector *v) {
    v->capacity *= 2;
	v->item = realloc (v->item, sizeof (void *) * v->capacity);
    if (v->item == NULL) {
        perror ("Se acabo la memoria. D: \n");
        exit (EXIT_FAILURE);
    }
}

void 
vectorPushBack (Vector *v, void *data) {
    v->item[v->size++] = data;
    if (v->size == v->capacity)
        resize (v);
}

void // Se pone un null al final
vectorPushFront (Vector *v, void *data) {
    v->size++;  
    if (v->size > v->capacity)
        resize (v);
	v->item[1] = v->item[0]; 
    v->item[0] = data;
}

void // Se debe hacer que len > 0
vectorResize (Vector *v, size_t len) {
    while (v->capacity < len)
        resize (v);
}

T 
vectorPopBack (Vector *v) {
    if (v->size <= 0) {
        perror ("Error at vectorPopBack: Se pretende " 
                "excarvar en el vacio. -___- \n");
        exit (EXIT_FAILURE);
    }
    return v->item[--v->size];
}

void 
vectorSet (Vector *v, size_t index, void *data) {
    if (index < v->size && index >= 0) 
        v->item[index] = data;
    else {
        perror ("Error at vectorSet: Indice invalido -__- ");
        exit (EXIT_FAILURE);
    }
}

void  
vectorAdd (Vector *v, size_t index, void *data) {
    if (index >= v->size || index < 0) {
        perror ("Error at vectorAdd: Indice invalido -__- ");
        exit (EXIT_FAILURE);
    }
    int i, j;
	void **temp = malloc (sizeof (void *) * (v->size - index)); 
	for (i = index, j = 0; i < v->size; i++, j++) 
		temp[j] = v->item[i];
	v->size++;
    if (v->size > v->capacity)
        resize (v);
    for (i = index + 1, j = 0; i < v->size; i++, j++)
        v->item[i] = temp[j];
    v->item[index] = data;
	free (temp);
}

