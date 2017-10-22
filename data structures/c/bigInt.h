

#ifndef BIG_INT_H
#define BIG_INT_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "vector.h"
#include "string.h"

typedef struct bigInt {
    Vector *v;
    int size;
} BigInt;

BigInt *newBigInt();
BigInt *BigIntAdd(BigInt *, BigInt *);
BigInt *stringAsBigInt(char *);

void *BigIntClear(BigInt *);

char *bigIntAsString(BigInt *); // bugs

#endif

