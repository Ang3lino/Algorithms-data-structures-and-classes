
#include "rational.h"

// hilos petry linux hilos

lli 
gcd(lli a, lli b){
    lli r;
    while(b != 0) {
		r = a % b;
		a = b; 
		b = r;
	}
    return a;
}

bool 
rationalCompareTo(Rational *p, Rational *q) {
	if (p->a * q->b == q->a * p->b)
		return true;
	return false;
}

void 
rationalSimplify(Rational *r) {
	if (r->a == 0) 
		r->b = 1;
	else {
		if ((r->a < 0 && r->b < 0) || (r->a >= 0 && r->b < 0)) {
			r->a *= -1;
			r->b *= -1;
		} 
		lli mcd = gcd(abs(r->a), abs(r->b));
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
	// Rational *
	rh->add = rationalAdd;
	rh->sub = rationalSubtraction;
	rh->prod = rationalProduct;
	rh->quot = rationalQuotient;
	rh->rec = rationalReciprocal;
	rh->new = newRational;

	// bool
	rh->compareTo = rationalCompareTo;

	//void 
	rh->simp = rationalSimplify;
	rh->print = rationalPrint;

	rh->one.a = 1;
	rh->one.b = 1;
	rh->zero.a = 0;
	rh->zero.b = 1;
	rh->minusOne.a = -1;
	rh->minusOne.b = 1;
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
	rationalSimplify(r);
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
	rationalSimplify(r);
	return r;
}

Rational *
rationalQuotient(Rational *p, Rational *q) {
	if (q->a == 0) {
		perror("Arithmetic exception at rationalQuotient : divition by zero D: ");
		exit(-1);
	}
	Rational *r = rationalProduct(p, rationalReciprocal(q));
	rationalSimplify(r);
	return r;
}

Rational *
rationalReciprocal(Rational *p) {
	if (p->a == 0) {
		perror("Arithmetic exception at rationalReciprocal: 1 / 0 D: ");
		exit(-1);
	}
	Rational *r = newRational();
	r->a = p->b;
	r->b = p->a;
	rationalSimplify(r);
	return r;
}

