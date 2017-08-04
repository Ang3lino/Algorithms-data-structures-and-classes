
#ifndef VECTOR_H
#define VECTOR_H 

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <stdbool.h>
#include <stdarg.h>

#define nil 0

typedef struct Element {
	int Integer;
	double Double;
	char String[100];
} Element;

typedef struct vectorNode {
	Element e;
	struct vectorNode *prev,
					  *next;
} vectorNode;

typedef struct vector {
	vectorNode *front, 
			   *back;
	int size;
	vectorNode **collection;
} Vector;

typedef Element E;

Vector *newVector ();
Vector *vectorSetSize (int);
Vector *vectorSublist (Vector *, int, int);

void    vectorAdd (Vector *, int, Element);
void    vectorClean (Vector *);
void    vectorRemove (Vector *, Element);
void    vectorSet (Vector *, Element, int);
void    vectorPushBack (Vector *, Element);

int     vectorEquals (Vector *, int, Element);
int     vectorCapacity (Vector *);
int     vectorContains (Vector *, Element);
int     vectorIndexOf (Vector *, Element);

Element vectorLastElement (Vector *);
Element vectorGet (Vector *, int);


#endif

