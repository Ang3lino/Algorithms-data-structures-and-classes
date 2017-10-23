
#include "rational.h"

void 
initRationalHandler(RationalHandler *rh) {
	rh->add = rationalAdd;
	rh->sub = rationalSubtraction;
	rh->prod = rationalProduct;
	rh->quot = rationalQuotient;
	rh->rec = rationalReciprocal;
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

