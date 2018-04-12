#include "pair.h"

pair *new_pair(void *first, void *second) {
    pair *self = malloc(sizeof(pair));
    self->a = first;
    self->b = second;
    return self;
}