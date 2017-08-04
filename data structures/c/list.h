
#ifndef LIST_H
#define LIST_H 

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

typedef struct listNode {
	Element e;
	struct listNode *prev,
                    *next;
} listNode;

typedef struct list {
	listNode *front, 
             *back;
	int size;
} List;

typedef Element E;

List *newList ();
List *listSetSize (int);
List *listSublist (List *, int, int);

void listAdd (List *, int, Element);
void listClean (List *);
void listRemove (List *, Element);
void listDelete (List *, int);
void listSet (List *, Element, int);
void listPushBack (List *, Element);

int listEquals (List *, int, Element);
int listCapacity (List *);
int listContains (List *, Element);
int listIndexOf (List *, Element);

Element listLastElement (List *);
Element listGet (List *, int);
Element listPopFront (List *);
Element listPopBack (List *);

#endif

