
#ifndef LIST_H
#define LIST_H 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdbool.h>

#define nil 0

typedef struct Element {
	int Integer;
	double Double;
	char String[100];
} Element;

typedef struct listNode {
	Element e;
	struct listNode *prev,
                    *next;
} listNode;

typedef struct list {
	listNode *front, 
             *back;
	size_t size;
} List;

typedef Element E;

List *newList ();
List *listSetSize (size_t);
List *listSubList (List *, size_t, size_t);

void listAdd (List *, size_t, Element);
void listClean (List *);
void listDelete (List *, size_t);
void listPushBack (List *, Element);
void listPushFront (List *, Element);

bool listRemove (List *, Element);
bool listContains (List *, Element);
bool listSet (List *, size_t, Element);

int listIndexOf (List *, Element);

Element listGet (List *, size_t);
Element listPopFront (List *);
Element listPopBack (List *);

#endif

