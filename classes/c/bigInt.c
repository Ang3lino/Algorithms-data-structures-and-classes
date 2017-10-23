
#include "bigInt.h"
#include "vector.h"

// zero as default
BigInt *
newBigInt() {
    BigInt *n = (BigInt *) malloc(sizeof(BigInt));
    n->v = newVector();
    n->size = 1;
    return n;
}

static int
addHelper (int a, int b, int *carry) {
    int n = a + b + *carry;
    if (n >= 10) {
        *carry = 1;
        n -= 10;
    } else 
        *carry = 0;
    return n;
}

// a.size \geq b.size
BigInt *
bigIntAddHelper(BigInt *a, BigInt *b) {
    int i, j, carry = 0, n;
    BigInt *c = newBigInt();
    for (i = 0; i < b->size; i++) {
        n = addHelper((int) a->v->item[i], (int) b->v->item[i], &carry);
        vectorPushBack(c->v, n);
    }
    while (i < a->size) {
        n = addHelper((int) a->v->item[i], 0, &carry);
        vectorPushBack(c->v, n);
        i++;
    }
    if (carry == 1) {
        vectorPushBack(c->v, carry);
        c->size = a->v->size + 1;
    } else
        c->size = a->v->size;
    return c;
}

BigInt *
bigIntAdd(BigInt *x, BigInt *y) {
    if (x->size < y->size) 
        return bigIntAddHelper(y, x);
    return bigIntAddHelper(x, y);
}

void 
bigIntClear(BigInt *n) {
    vectorClear(n->v);
    free(n);
}

BigInt * 
stringAsBigInt(char *s) {
    int n = strlen(s), i = 0;
    BigInt *bi = newBigInt();
    for (i = n - 1; i >= 0; i--)
        vectorPushBack(bi->v, s[i] - '0');
    bi->size = n;
    return bi;
}

char * 
bigIntAsString(BigInt *n) {
    char *s = (char *) malloc (sizeof(char) * (n->size + 1));
    int i, j; 
    for (i = n->size - 1, j = 0; i >= 0; i--, j++)
        s[j] = n->v->item[i] + '0';
    s[j] = '\0';
    return s;
}

