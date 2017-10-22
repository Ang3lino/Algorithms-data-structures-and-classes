
#ifndef VECTOR_H
#define VECTOR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <errno.h>

// size_t es un unsigned int
typedef struct vector {
    void **item;
    size_t size;
    size_t capacity;
} Vector;

typedef void *T; // Emulacion generica

Vector *newVector (void);
T vectorPopBack (Vector *);
T vectorPopFront (Vector *);

void vectorResize (Vector *, size_t);
void vectorPushBack (Vector *, void *);
void vectorPushFront (Vector *, void *);
void vectorClear (Vector *);
void vectorResize (Vector *, size_t);
void vectorAdd (Vector *, size_t, void *);
void vectorSet (Vector *, size_t, void *);

#endif

