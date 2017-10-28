
#include "matrix.h"
#define ord 5

MatrixHandler mh;
RationalHandler rh;

int 
main (void) {
    initMatrixHandler(&mh);
    initRationalHandler(&rh);

    Matrix *a = mh.rand(ord, ord), *b, *c;
    Rational *r = newRational();

    mh.print(a);
    b = mh.inv(a);
    if (b)
        mh.print(b);
   // mh.free(a);
    //mh.free(b);
    puts("");
    return 0;
}
