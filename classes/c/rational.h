

#ifndef RATIONAL_H
#define RATIONAL_H

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <stdbool.h>

typedef long long int lli;

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
    Rational *(*new)(void);

    bool (*compareTo)(Rational *, Rational *);
    
    void (*simp)(Rational *);
    void (*print)(Rational *);

    Rational one, 
             zero, 
             minusOne;

} RationalHandler;

void initRationalHandler(RationalHandler *);
void rationalSimplify(Rational *);
void rationalPrint(Rational *);

Rational *newRational(void);
Rational *rationalAdd(Rational *, Rational *);
Rational *rationalSubtraction(Rational *, Rational *);
Rational *rationalProduct(Rational *, Rational *);
Rational *rationalQuotient(Rational *, Rational *);
Rational *rationalReciprocal(Rational *);


long gdc(long, long);


#endif 