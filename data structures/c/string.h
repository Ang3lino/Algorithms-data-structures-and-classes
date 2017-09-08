
#ifndef STRING_H
#define STRING_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct string {
	char *str;
	size_t size, 
		   capacity;
} String;

String *newString (void);
String *stringSubstract (String *, String *);
void addLine (String *);
void stringClean (String *);
		   
#endif 

