
#include "rational.h"

long 
gcd (long n1, long n2) {
	while (n1 != n2) {
        if (n1 > n2)
            n1 -= n2;
        else
            n2 -= n1;
	}
	return n1;
}

void 
rationalSimplify(Rational *r) {
	if (r->a == 0) 
		r->b = 1;
	else {
		if (r->a < 0 && r->b < 0) {
			r->a *= -1;
			r->b *= -1;
		}
		long mcd = gcd(r->a, r->b);
		r->a /= mcd;
		r->b /= mcd;
	}
}

void 
rationalPrint(Rational *r) {
	if (r->b == 1) 
		printf("%ld", r->a);
	else
		printf("%ld/%ld", r->a, r->b);
}

void 
initRationalHandler(RationalHandler *rh) {
	rh->add = rationalAdd;
	rh->sub = rationalSubtraction;
	rh->prod = rationalProduct;
	rh->quot = rationalQuotient;
	rh->rec = rationalReciprocal;

	//void 
	rh->simp = rationalSimplify;
	rh->print = rationalPrint;
}

Rational *
newRational() {
	Rational *r = (Rational *) malloc (sizeof (Rational));
	r->a = 0;
	r->b = 1;
	return r;
}

Rational *
rationalAdd(Rational *x, Rational *y) {
	Rational *r = newRational();
	r->a = x->a * y->b + y->a * x->b;
	r->b = x->b * y->b;
	return r;
}

Rational *
rationalSubtraction(Rational *p, Rational *q) {
	Rational *invAdd = newRational();
	invAdd->a = -1;
	return rationalAdd(p, rationalProduct(invAdd, q));
}

Rational *
rationalProduct(Rational *p, Rational *q) {
	Rational *r = newRational();
	r->a = p->a * q->a;
	r->b = p->b * q->b;
	return r;
}

Rational *
rationalQuotient(Rational *p, Rational *q) {
	Rational *r = newRational();
	return rationalProduct(p, rationalReciprocal(q));
}

Rational *
rationalReciprocal(Rational *p) {
	Rational *r = newRational();
	r->a = p->b;
	r->b = p->a;
	return r;
}

