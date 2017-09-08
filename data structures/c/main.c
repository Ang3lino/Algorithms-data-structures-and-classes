
#include <stdio.h>
#include <string.h>
#include "stack.h"
#include "string.h"

int main(int argc, char *argv[])
{
	String *string = newString(),
		   *subString = newString(), 
		   *result = newString();
	printf ("Escribe la cadena principal: ");
	addLine (string);
	printf ("Escribe la subcadena: ");
	addLine (subString);
	// string.size >= subString.size
	result = stringSubstract (string, subString);
	printf ("%s ", result->str);
	return 0;
}

