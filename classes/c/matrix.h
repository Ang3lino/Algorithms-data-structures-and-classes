
// matrix "class" simulation by Angel Lopez Manriquez

#ifndef MATRIX_H
#define MATRIX_H 

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "rational.h"

typedef struct matrix {
    int m, 
        n;
    Rational ***mat;
} Matrix;

typedef struct matrixHandler 
{
    Matrix *(*add)(Matrix *, Matrix *);
    Matrix *(*prod)(Matrix *, Matrix *);
    Matrix *(*subt)(Matrix *, Matrix *);
    Matrix *(*trans)(Matrix *);
    Matrix *(*adj)(Matrix *);
    Matrix *(*escProd)(Matrix *, Rational *);
    Matrix *(*rand)(int, int);
    Matrix *(*minor)(Matrix *, int, int);

    Rational *(*det)(Matrix *);
    Rational *(*cof)(Matrix *, int, int);

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

Rational *matrixDeterminant(Matrix *);
Rational *matrixCofactor(Matrix *, int, int);

void matrixPrinter(Matrix *);
void initMatrixHandler(MatrixHandler *);

#endif
