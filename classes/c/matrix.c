
#include "matrix.h"

Matrix *
newMatrix(int x, int y) {
    int i, j;
    Matrix *m = (Matrix *) malloc (sizeof (Matrix));
    for (i = 0; i < x; i++)
        for (j = 0; j < y; j++)
            m->mat[i][j] = newRational();
    m->m = x;
    m->n = y;
    return m;
}

Matrix *
matrixAddition(Matrix *a, Matrix *b) {
    if (a->m == b->m && a->n == b->n) {
        int i, j;
        Matrix *c = newMatrix(a->m, a->n);
        RationalHandler rh;
        initRationalHandler(&rh);
        for (i = 0; i < a->m; i++)
            for (j = 0; j < a->n; j++)
                c->mat[i][j] = rh.add(a->mat[i][j], b->mat[i][j]);
    } else {
        perror("The addition of the matrices are undefined \n")
        exit(-1);
    }
    return c;
}

// c_{ij} = \sum_{k = 0}^{b.n-1} a_{ik}b_{kj}
Matrix *
matrixProduct(Matrix *a, Matrix *b) {
    if (a->n == b->m) {
        int i, j, k;
        Matrix *c = newMatrix(a->m, b->n);
        RationalHandler rh;
        initRationalHandler(&rh);
        for (i = 0; i < a->m; i++) 
            for (j = 0; j < b->n; j++) 
                for (k = 0; k < b->n; k++) 
                    c->mat[i][j] = rh.prod(a->mat[i][k], b->mat[k][j]);
    } else {
        perror("The product's undefined \n");
        exit(-1);
    }
    return c;
}

Matrix *
matrixSubtract(Matrix *a, Matrix *b) {
    if (a->m == b->m && a->n == b->n) {
        int i, j;
        Matrix *c = newMatrix(a->m, a->n);
        RationalHandler rh;
        initRationalHandler(&rh);
        for (i = 0; i < a->m; i++)
            for (j = 0; j < a->n; j++)
                c->mat[i][j] = rh.sub(a->mat[i][j], b->mat[i][j]);
    } else {
        perror("Addition of the matrices are undefined \n");
        exit(-1);
    }
    return c;
}

Matrix *
matrixTransposed(Matrix *a) {
    Matrix *t = newMatrix(a->n, a->m);
    int i, j;
    for (i = 0; i < a->n; i++)
        for (j = 0; j < a->n; j++)
            t->mat[j][i] = a->mat[i][j];
    return t;
}

Matrix *
matrixEscalarProduct(Matrix *a, Rational *k) {
    int i, j;
    RationalHandler rh;
    initRationalHandler(&rh);
    for (i = 0; i < a->m; i++) 
        for (j = 0; j < a->n; j++) 
            a->mat[i][j] = rh.prod(a->mat[i][j], k);
    return a;
}

Matrix *
matrixAdjunct(Matrix *);

Matrix *
matrixCofactor(Matrix *a, int x, int y) {
    int i, j;
    Matrix *c = newMatrix(a->m - 1, a->n - 1);
    for (i = 0; i < a->m; i++) 
        for (j = 0; j < a->n; j++)
            if (i != x )
     
}

Rational *
matrixDeterminant(Matrix *a) {
    if (a->m == a->n) {
        if (a->m == 0) 
            return a->mat[0][0];
        Rational *r = newRational(), 
                 *aux = newRational();
        RationalHandler rh;
        initRationalHandler(&rh);
        int j;
        for (j = 0; j < a->m; j++) {
            aux->a = pow(-1, j) * aux->a;
            r = rh.add(r, rh.prod(a->mat[0][j], matrixCofactor(a, 0, j)));
        }


    }


}

