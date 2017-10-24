

#ifndef RATIONAL_H
#define RATIONAL_H

#include <stdlib.h>
#include <stdio.h>

typedef struct rational {
    long a, 
         b;
} Rational;

typedef struct rationalHandler {
    Rational *(*add)(Rational *, Rational *);
    Rational *(*sub)(Rational *, Rational *);
    Rational *(*prod)(Rational *, Rational *);
    Rational *(*quot)(Rational *, Rational *);
    Rational *(*rec)(Rational *);
    
    void (*simp)(Rational *);
    void (*print)(Rational *);
} RationalHandler;

void initRationalHandler(RationalHandler *);
void rationalSimplify(Rational *);
void rationalPrint(Rational *);

Rational *newRational();
Rational *rationalAdd(Rational *, Rational *);
Rational *rationalSubtraction(Rational *, Rational *);
Rational *rationalProduct(Rational *, Rational *);
Rational *rationalQuotient(Rational *, Rational *);
Rational *rationalReciprocal(Rational *);


long gdc(long, long);


#endif 