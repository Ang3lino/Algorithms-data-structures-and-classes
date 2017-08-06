
#include "vector.h"

Vector *
newVector (void) {
    Vector *v = malloc (sizeof (Vector));
    v->capacity = 10;
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

void 
vectorPushFront (Vector *v, void *data) {
    int i;
    if (v->size + 1 >= v->capacity)
        resize (v);
    for (i = 0; i < v->size; i++) 
        v->item[i + 1] = v->item[i];
    v->item[0] = data;
    v->size++;
}

void 
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
    v->size--;
    return v->item[v->size];
}

void 
vectorSet (Vector *v, size_t index, void *data) {
    if (index < v->size && index >= 0) 
        v->item[index] = data;
    else {
        perror ("Error at vectorSet: Indice invalido -__- \n");
        exit (EXIT_FAILURE);
    }
}

void
vectorAdd (Vector *v, size_t index, void *data) {
    if (index >= v->size || index < 0) {
        perror ("Error at vectorAdd: Indice invalido -__- \n");
        exit (EXIT_FAILURE);
    }
    int i;
    if (v->size + 1 >= v->capacity)
        resize (v);
    for (i = index; i < v->size; i++)
        v->item[i + 1] = v->item[i];
    v->item[index] = data;
    
}
