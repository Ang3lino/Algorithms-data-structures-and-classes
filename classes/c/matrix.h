
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
    Matrix *(*new)(int, int);
    Matrix *(*add)(Matrix *, Matrix *);
    Matrix *(*prod)(Matrix *, Matrix *);
    Matrix *(*subt)(Matrix *, Matrix *);
    Matrix *(*trans)(Matrix *);
    Matrix *(*adj)(Matrix *);
    Matrix *(*escProd)(Matrix *, Rational *);
    Matrix *(*rand)(int, int);
    Matrix *(*minor)(Matrix *, int, int);
    Matrix *(*inv)(Matrix *);

    Rational *(*det)(Matrix *);
    Rational *(*cof)(Matrix *, int, int);
    Rational *(*get)(Matrix *, int, int);

    void (*print)(Matrix *);
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

Rational *matrixDeterminant(Matrix *);
Rational *matrixCofactor(Matrix *, int, int);
Rational *matrixGet(Matrix *, int, int);

void matrixPrinter(Matrix *);
void initMatrixHandler(MatrixHandler *);
void swapRows(Matrix *, int , int);

#endif
