
// matrix "class" simulation by Angel Lopez Manriquez

#ifndef MATRIX_H
#define MATRIX_H 

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <stdbool.h>
#include "rational.h"

typedef long long int lli;

typedef struct matrix {
    int m, 
        n;
    Rational ***mat;
} Matrix;

typedef struct matrixHandler 
{
    Matrix *(*new)(int, int),
        *(*add)(Matrix *, Matrix *),
        *(*prod)(Matrix *, Matrix *),
        *(*subt)(Matrix *, Matrix *),
        *(*trans)(Matrix *),
        *(*adj)(Matrix *),
        *(*escProd)(Matrix *, Rational *),
        *(*rand)(int, int),
        *(*minor)(Matrix *, int, int),
        *(*inv)(Matrix *),
        *(*clone)(Matrix *);

    Rational *(*det)(Matrix *);
    Rational *(*cof)(Matrix *, int, int);
    Rational *(*get)(Matrix *, int, int);

    void (*print)(Matrix *);
    void (*free)(Matrix *);
} MatrixHandler;

Matrix *newMatrix(int, int);

Matrix *matrixMinor(Matrix *, int, int);
Matrix *matrixRandom(int, int);
Matrix *matrixAddition(Matrix *, Matrix *);
Matrix *matrixProduct(Matrix *, Matrix *);
Matrix *matrixSubtract(Matrix *, Matrix *);
Matrix *matrixTransposed(Matrix *);
Matrix *matrixAdjunct(Matrix *);
Matrix *matrixEscalarProduct(Matrix *, Rational *);
Matrix *matrixInverse(Matrix *);
Matrix *matrixClone(Matrix *);

Rational *matrixDeterminant(Matrix *);
Rational *matrixCofactor(Matrix *, int, int);
Rational *matrixGet(Matrix *, int, int);

void matrixPrinter(Matrix *);
void matrixFree(Matrix *);
void initMatrixHandler(MatrixHandler *);
void swapRows(Matrix *, int , int);

#endif
