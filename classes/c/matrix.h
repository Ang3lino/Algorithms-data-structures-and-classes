
#ifndef MATRIX_H
#define MATRIX_H 

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct matrix {
    int m, 
        n;
    Rational ***mat;
} Matrix;

typedef struct matrixHandler {

} MatrixHandler;

Matrix *newMatrix();
Matrix *matrixAddition(Matrix *, Matrix *);
Matrix *matrixProduct(Matrix *, Matrix *);
Matrix *matrixSubtract(Matrix *, Matrix *);
Matrix *matrixTransposed(Matrix *);
Matrix *matrixAdjunct(Matrix *);
Matrix *matrixCofactor(Matrix *, int, int);
Matrix *matrixEscalarProduct(Matrix *, double);
Rational *matrixDeterminant(Matrix *);


#endif
