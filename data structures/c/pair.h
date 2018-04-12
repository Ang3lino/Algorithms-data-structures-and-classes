#ifndef PAIR_H
#define PAIR_H

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    void *a, *b;
} pair;

pair *new_pair(void *, void *);

#endif