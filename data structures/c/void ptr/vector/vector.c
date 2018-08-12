#include "vector.h"

// private:
static void resize (vector *v) {
    v->capacity *= 2;
	v->item = realloc(v->item, v->elemsize * v->capacity);
    assert (v->item != NULL);
}

static void *_voffset(vector *v, size_t i) { return v->item + i * v->elemsize; }

// public:
vector *new_vector (size_t elemsize) {
    vector *v = malloc(sizeof(vector));
    v->capacity = 2;
    v->size = 0;
    v->item = calloc(elemsize, v->capacity);
    v->elemsize = elemsize;
    return v;
}

void vpush_back (vector *v, void *data) {
    if (v->size  + 1 >= v->capacity) resize(v);
    memcpy(_voffset(v, v->size++), data, v->elemsize);
}

void vresize (vector *v, size_t len) {
    assert(len >= 2);
    while (v->capacity < len) resize (v);
    v->size = len;
}

void *vpop_back (vector *v) {
    assert(0 < v->size);
    void *data = malloc(v->elemsize);
    memcpy(data, _voffset(v, --v->size), v->elemsize);
    return data;
}

void vset(vector *v, size_t index, void *data) {
    assert(index <= 0 || index < v->size);
    memcpy(_voffset(v, index), data, v->elemsize);
}

void vclear(vector *v) {
    free(v->item);
    v->capacity = 2;
    v->size = 0;
}