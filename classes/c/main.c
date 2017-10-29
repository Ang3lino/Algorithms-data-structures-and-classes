
#include "matrix.h"
#include <string.h>
#define ord 10

MatrixHandler mh;
RationalHandler rh;

void 
writeMatrixFile(Matrix *a, const char *fileName) {
    FILE *fp = fopen(fileName, "w+");
    int i, j;
    for (i = 0; i < a->m; i++)  {
        for (j = 0; j < a->n; j++) 
            fprintf(fp, "%s ", rh.asString(mh.get(a, i, j)));
        fprintf(fp, "\n");
    }
    fclose(fp);
}

void 
readMatrixFile(const char *fileName) {
    FILE *fp = fopen(fileName, "r+");
    char *strtemp = (char *) calloc (sizeof (char), 50 * ord);
    while ((fgets(strtemp, 50 * ord, fp)) != NULL)
        printf ("%s", strtemp);
    fclose(fp);
    free(strtemp);
}

void 
showFiles() {
    char *paths[] = {
        "addition.txt", 
        "subtraction.txt", 
        "product.txt",
        "transposed1.txt",
        "transposed2.txt",
        "inverse1.txt",
        "inverse2.txt"
    };
    int i;
    for (i = 0; i < 7; i++)
        readMatrixFile(paths[i]);
}

int 
main (int argc, char **argv) {
    initMatrixHandler(&mh);
    initRationalHandler(&rh);
    Matrix *a = mh.rand(ord, ord), *c;
    sleep(1);
    Matrix *b = mh.rand(ord, ord);
    c = mh.add(a, b);
    writeMatrixFile(c, "addition.txt");
    c = mh.subt(a, b);
    writeMatrixFile(c, "subtraction.txt");
    c = mh.prod(a, b);
    writeMatrixFile(c, "product.txt");
    c = mh.trans(a);
    writeMatrixFile(c, "transposed1.txt");
    c = mh.trans(b);
    writeMatrixFile(c, "transposed2.txt");
    c = mh.inv(a); // mh.inv(Matrix *) retorna NULL si la matriz no tiene inversa
    if (c)
        writeMatrixFile(c, "inverse1.txt");
    else
        puts("No se creo el archivo inverse1.txt");
    c = mh.inv(b);
    if (c)
        writeMatrixFile(c, "inverse2.txt");
    else
        puts("No se creo el archivo inverse1.txt");
    showFiles();
    return 0;
}
