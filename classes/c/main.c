
#include "matrix.h"
#define ord 9

MatrixHandler mh;
RationalHandler rh;

int 
main (void) {
    initMatrixHandler(&mh);
    initRationalHandler(&rh);

    Rational *r = newRational();
    Matrix *a = mh.rand(ord, ord), *b = mh.rand(ord, ord), *c;
    mh.print(a);
    c = mh.adj(a);
    mh.print(c);
    printf("\n");
    return 0;
}
