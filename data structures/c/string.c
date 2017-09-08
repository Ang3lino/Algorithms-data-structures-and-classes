
#include "string.h"

String *
newString (void) {
	String *s = (String *) malloc (sizeof (String));
	s->size = 0;
	s->capacity = 1;
	s->str = 0;
	return s;
}

static void stringResize (String *s) {
	s->capacity *= 2;
	s->str = realloc (s->str, sizeof (char) * s->capacity);
}

bool 
isSubString (String *a, String *b) {
	int i, j, k = 0;
	for (i = 0; i < a->size; i++) {
		if (a->str[i] == b->str[0]) {
			for (j = i, k = 0; j < b->size; j++, k++) {
				if (a->str[j] != b->str[k])
					break;
			}
			return true; 
		}
	}
	return false;
}

String *
stringSubstract (String *string, String *substr) {
	String *other = newString();
	int i, j;
	while (other->capacity < string->capacity)
		stringResize (other);
	if (isSubString (string, substr)) {
		for (j = 0; j < string->size - substr->size; j++)
			other->str[j] = string->str[j];
		other->str[++j] = '\0';
	}
	return other;
}

void 
addLine (String *s) {
	char c;
	if (s->size == 0) {
		s->str = (char *) calloc (sizeof (char), 2);
		s->capacity = 2;
	}
	s->size = 0;
	while ((c = getchar()) != '\n') {
		if (s->capacity == s->size) 
			stringResize (s);
		s->str[s->size++] = c;
	}
	if (s->size == s->capacity)
		stringResize (s);
	s->str[s->size++] = '\0';
}

void 
stringClean (String *s) {
	free (s->str);
}


