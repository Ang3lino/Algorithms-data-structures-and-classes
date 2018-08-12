#ifndef VECTOR_H
#define VECTOR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <errno.h>

typedef struct vector {
// public:
    size_t size; // how many useful items we have stored

// private: 
    void *item; // a generic pointer
    size_t capacity; // number of elements of reserved memory
    size_t elemsize; // size in bytes of each element
} vector;

// It'll return a value
#define vget_as(type, vec, index) \
	*(type *) (vec->item + i * vec->elemsize)

vector *new_vector(size_t elemsize);

void *vpop_back (vector *);
void *vpop_front (vector *);

void vpush_back (vector *, void *);
void vpush_front (vector *, void *);
void vclear (vector *);
void vresize (vector *, size_t);
void vadd (vector *, size_t, void *);
void vset (vector *, size_t, void *);

#endif