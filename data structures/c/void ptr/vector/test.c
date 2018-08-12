#include <stdio.h>
#include <stdlib.h>

#include "vector.h"

#define NMEMBS 10e3

// This function makes sure that the pointer to return is not null.
FILE *fopen_ok(const char *path, const char *mode) {
    FILE *fp = fopen(path, mode);
    assert(fp);
    return fp;
}

void fillWithFile(vector *v, FILE *fp) {
    int i = 0, x;
    // fscanf returns -1 if the file can't be read anymore
    while ( i < NMEMBS && (1 == fscanf(fp, "%d", &x)) ) {
        vpush_back(v, &x);
        ++i;
    } 
}

int main(int argc, char const *argv[]) {
    FILE *fp = fopen_ok("10mil.txt", "r");
    vector *array = new_vector(sizeof(int));
    fillWithFile(array, fp);
    for (int i = 0; i < array->size; i++) printf("v[%d]: %d \n", i, vget_as(int, array, i));
    vclear(array);
    free(fp);
    return 0;
}