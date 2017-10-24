
#include "matrix.h"
#define ord 2

MatrixHandler mh;
RationalHandler rh;

int 
main (void) {
    initMatrixHandler(&mh);
    initRationalHandler(&rh);

    Matrix *a = mh.rand(ord, ord), *b = mh.rand(ord, ord), *c;
    Rational *r = newRational();
    mh.print(a);
    //r = mh.det(a);
    detPivot(a, 0);
    mh.print(a);
    detPivot(a, 1);
    mh.print(a);
    detPivot(a, 2);
    mh.print(a);
    detPivot(a, 3);
    mh.print(a);
    puts("");
    return 0;
}
