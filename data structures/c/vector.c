
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
    if (v->size  + 1 >= v->capacity)
        resize (v);
    v->item[v->size++] = data;
}

static void 
moveSubVectorOneStepRight (Vector *v, int a) {
	int i;
	for (i = v->size - 1; i >= a; i--)
		v->item[i + 1] = v->item[i];
}

void 
vectorPushFront (Vector *v, void *data) {
    v->size++;  
	int i;
    if (v->size > v->capacity)
        resize (v);
	moveSubVectorOneStepRight (v, 0);
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
	moveSubVectorOneStepRight (v, index);
	v->item[index] = data;
}

void 
vectorClear(Vector *v) {
    free(v->item);
    free(v);
}
