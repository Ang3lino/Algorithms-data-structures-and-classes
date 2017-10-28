
#include "matrix.h"

// posix pthread threads at c

void 
initMatrixHandler(MatrixHandler *mh) {
    // Matrix *
    mh->add = matrixAddition;
    mh->prod = matrixProduct;
    mh->subt = matrixSubtract;
    mh->trans = matrixTransposed;
    mh->adj = matrixAdjunct;
    mh->escProd = matrixEscalarProduct; 
    mh->rand = matrixRandom;
    mh->minor = matrixMinor;
    mh->new = newMatrix;
    mh->inv = matrixInverse;

    // Rational *
    mh->det = matrixDeterminant;
    mh->cof = matrixCofactor;
    mh->get = matrixGet;

    // void
    mh->print = matrixPrinter;
    mh->free = matrixFree;
}

Matrix *
matrixRandom(int x, int y) {
    int i, j;
    Matrix *a = newMatrix(x, y);
    srand(time(NULL));
    //srand(0);
    for (i = 0; i < x; i++) 
        for (j = 0; j < y; j++) {
            a->mat[i][j]->a = rand() % 10;
            a->mat[i][j]->b = 1;
        }
    return a;
}

Matrix *
newMatrix(int x, int y) {
    int i, j;
    Matrix *m = (Matrix *) malloc (sizeof (Matrix));
    m->mat = (Rational ***) malloc (sizeof (Rational **) * x);
    if (m->mat == NULL) {
        perror("Se acabo la memoria D: ");
        exit(-1);
    }
    for (i = 0; i < x; i++) {
        m->mat[i] = (Rational **) malloc (sizeof (Rational *) * y);
        if (m->mat[i] == NULL) {
            perror("Se acabo la memoria D:");
            exit(-1);
        }
    }
    for (i = 0; i < x; i++)
        for (j = 0; j < y; j++)
            m->mat[i][j] = newRational();
    m->m = x;
    m->n = y;
    return m;
}

void 
matrixFree(Matrix *a) {
    int i, j;
    for (i = 0; i < a->m; i++)
        free(a->mat[i][0]);
    free(a->mat);
    free(a);
}

void 
matrixPrinter(Matrix *a) {
    int i, j;
    for (i = 0; i < a->m; i++) {
        for (j = 0; j < a->n; j++) {
            if (a->mat[i][j]->b == 1)
                printf ("%ld\t", a->mat[i][j]->a);
            else  
                printf("%ld/%ld\t", a->mat[i][j]->a, a->mat[i][j]->b);
        }
        printf("\n");
    }
    printf("\n");
}


Matrix *
matrixAddition(Matrix *a, Matrix *b) {
    Matrix *c = newMatrix(a->m, a->n);
    if (a->m == b->m && a->n == b->n) {
        int i, j;
        RationalHandler rh;
        initRationalHandler(&rh);
        for (i = 0; i < a->m; i++)
            for (j = 0; j < a->n; j++)
                c->mat[i][j] = rh.add(a->mat[i][j], b->mat[i][j]);
    } else {
        perror("The addition of the matrices are undefined \n");
        exit(-1);
    }
    return c;
}

// c_{ij} = \sum_{k = 0}^{b.n-1} a_{ik}b_{kj}
Matrix *
matrixProduct(Matrix *a, Matrix *b) {
    Matrix *c = newMatrix(a->m, b->n);
    if (a->n == b->m) {
        int i, j, k;
        RationalHandler rh;
        initRationalHandler(&rh);
        for (i = 0; i < a->m; i++) 
            for (j = 0; j < b->n; j++) {
                c->mat[i][j]->a = 0;
                for (k = 0; k < b->n; k++) 
                    c->mat[i][j] = rh.prod(a->mat[i][k], b->mat[k][j]);
            }
    } else {
        perror("The product's undefined \n");
        exit(-1);
    }
    return c;
}

Matrix *
matrixSubtract(Matrix *a, Matrix *b) {
    Matrix *c = newMatrix(a->m, a->n);
    if (a->m == b->m && a->n == b->n) {
        int i, j;
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
    Matrix *e = newMatrix(a->m, a->n);
    for (i = 0; i < a->m; i++) 
        for (j = 0; j < a->n; j++) 
            e->mat[i][j] = rh.prod(a->mat[i][j], k);
    return e;
}

Matrix *
matrixAdjunct(Matrix *a) {
    int i, j;
    Matrix *adj = newMatrix(a->m, a->n);
    for (i = 0; i < a->m; i++)
        for (j = 0; j < a->n; j++)
            adj->mat[i][j] = matrixCofactor(a, i, j);
    return adj;
}

Matrix * 
matrixMinor (Matrix *a, int x, int y) {
    int i, j, k = 0, l = 0;
    Matrix *m = newMatrix(a->m - 1, a->n - 1);
    for (i = 0; i < a->m; i++) {
        for (j = 0; j < a->n; j++) {
            if (i == x || j == y)   
                continue;
            m->mat[k][l++] = a->mat[i][j];
            if (l == a->n - 1) {
                k++;
                l = 0;
            }
        }
    }
    return m;
}

// C_{ij} = (-1)^{i+j} |M_{ij}|
Rational *
matrixCofactor(Matrix *a, int i, int j) {
    RationalHandler rh;
    initRationalHandler(&rh);
    Rational *r = newRational();
    r->a = pow(-1, i + j);
    return rh.prod(matrixDeterminant(matrixMinor(a, i, j)), r);
}

Rational *
matrixGet(Matrix *a, int i, int j) {
    return a->mat[i][j];
}

void 
swapRows(Matrix *a, int x, int y) {
    Rational *r = newRational();
    int j;
    for (j = 0; j < a->n; j++) {
        r = a->mat[x][j];
        a->mat[x][j] = a->mat[y][j];
        a->mat[y][j] = r;
    }
}

void 
multRow(Matrix *a, int x, Rational *esc) {
    int j;
    RationalHandler rh;
    initRationalHandler(&rh);
    for (j = 0; j < a->n; j++)
        a->mat[x][j] = rh.prod(esc, a->mat[x][j]);
}

// R[q] <- R[p] + R[q]
void 
addRows(Matrix *a, int p, int q) {
    int j;
    RationalHandler rh;
    initRationalHandler(&rh);
    for (j = 0; j < a->n; j++)
        a->mat[q][j] = rh.add(a->mat[p][j], a->mat[q][j]);
}

void 
subtractRows(Matrix *a, int p, int q) {
    int j;
    RationalHandler rh;
    initRationalHandler(&rh);
    for (j = 0; j < a->n; j++)
        a->mat[p][j] = rh.sub(a->mat[p][j], a->mat[q][j]);
}

// rx <- rx + a ry
void 
addMultRows(Matrix *a, int x, int y, Rational *esc) {
    int i, j;
    RationalHandler rh;
    initRationalHandler(&rh);
    for (j = 0; j < a->n; j++) 
        a->mat[x][j] = rh.add(a->mat[x][j], rh.prod(esc, a->mat[y][j]));
}

int 
detPivot(Matrix *a, int x) {
    int i = x + 1, j;
    Rational *r = newRational(), *minusOne = newRational();
    minusOne->a = -1;
    RationalHandler rh;
    initRationalHandler(&rh);
    if (a->mat[x][x]->a == 0) {
        while (a->mat[i++][x]->a == 0 && i < a->m);
        if (i == a->m) 
            return 0;
        swapRows(a, i, x);
    }
    for (i = x + 1; i < a->m; i++) {
        if (a->mat[i][x]->a == 0)
            continue;
        r = rh.quot(rh.prod(minusOne, a->mat[i][x]), a->mat[x][x]);
        addMultRows(a, i, x, r);
    }
    return 1;
}

// it modifies the matrix
Rational *
matrixDeterminant(Matrix *a) {
    if (a->m != a->n) {
        perror("error at matrixDeterminant: Matrix for a non-square matrix's undefined. -_-");
        exit(-1);
    }
    Rational *r = newRational();
    RationalHandler rh;
    int i;
    for (i = 0; i < a->m - 1; i++) {
        if (detPivot(a, i) == 0)
            return r; // r = 0
    }
    initRationalHandler(&rh);
    r->a = 1;
    for (i = 0; i < a->m; i++) 
        r = rh.prod(r, a->mat[i][i]);
    return r;
}

/*
Matrix *
matrixInverse(Matrix *a) {
    if (a->m != a->n) {
        perror("Error at matrixInverse: it's a non-square matrix :O ");
        exit(-1);
    }
    Rational *r = newRational();
    RationalHandler rh;
    MatrixHandler mh;
    initMatrixHandler(&mh);
    initRationalHandler(&rh);
    if ((r = mh.det(a))->a == 0) {
        puts("The matrix has no inverse. ");
        return NULL;
    }
    Matrix *inv = mh.new(a->m, a->n);
    int i, j;
    for (i = 0; i < a->m; i++)
        for (j = 0; j < a->n; j++)
            inv->mat[i][j] = rh.prod(rh.rec(r), mh.cof(a, i, j));
    return inv;
}
*/ 

static Matrix * 
inverserHelper(Matrix *a) {
    Matrix *temp = newMatrix(a->m, a->n * 2);
    Rational *unit = newRational();
    unit->a = 1;
    int i, j;
    for (i = 0; i < a->m; i++)
        for (j = 0; j < a->n; j++) 
            temp->mat[i][j] = matrixGet(a, i, j);
    j = a->n;
    for (i = 0; i < a->m; i++)
        temp->mat[i][j++] = unit;
    return temp;
}

Matrix *
aumentedCutter(Matrix *aum) {
    MatrixHandler mh;
    initMatrixHandler(&mh);
    Matrix *dism = mh.new(aum->m, aum->m);
    int i, j;
    for (i = 0; i < aum->m; i++) 
        for (j = aum->m; j < 2 * aum->m; j++) 
            dism->mat[i][j - aum->m] = mh.get(aum, i, j);
    return dism;
}

static bool
gaussPivot(Matrix *a, const int x) {
    int i = x + 1;
    RationalHandler rh;
    MatrixHandler mh;
    initRationalHandler(&rh);
    initMatrixHandler(&mh); 
    if (rh.compareTo(&rh.zero, mh.get(a, x, x))){
        while (i < a->m && rh.compareTo(&rh.zero, a->mat[i][x]))
            i++;
        if (i == a->m)
            return false;
        swapRows(a, x, i);
    }
    if (!rh.compareTo(mh.get(a, x, x), &rh.one))
        multRow(a, x, rh.rec(mh.get(a, x, x)));
    for (i = 0; i < a->m; i++) {
        if (i == x || rh.compareTo(mh.get(a, i, x), &rh.zero))
            continue;        
        addMultRows(a, i, x, rh.prod(mh.get(a, i, x), &rh.minusOne));
    }
    return true;
}

// yt cs50
Matrix * 
matrixInverse(Matrix *a) {
    if (a->m != a->n) {
        perror("Error at matrixInverse: it's a non-square matrix :O ");
        exit(-1);
    }
    MatrixHandler mh;
    RationalHandler rh;
    initMatrixHandler(&mh);
    initRationalHandler(&rh);
    Matrix *temp = inverserHelper(a);
    int i, j;
    for (i = 0; i < temp->m; i++) {
        //mh.print(temp);
        if (!gaussPivot(temp, i)) {
            puts("The matrix given isn't invertible D: ");
            return NULL;
        }
    } 
    for (i = 0; i < temp->m; i++) 
        if (!rh.compareTo(mh.get(temp, i, i), &rh.one))
            multRow(temp, i, rh.rec(mh.get(temp, i, i)));
    Matrix *dism = aumentedCutter(temp);
    return dism;
}

/*
    Rational *
    matrixDeterminant(Matrix *a) {
        if (a->m != a->n) {
            perror("Determinant for not squared matrices is undefined.");
            exit(-1);
        }
        if (a->m == 1) 
            return a->mat[0][0];
        Rational *r = newRational(); 
        RationalHandler rh;
        initRationalHandler(&rh);
        int j;
        for (j = 0; j < a->n; j++) 
            r = rh.add(r, rh.prod(a->mat[0][j], matrixCofactor(a, 0, j)));
        return r;
    }
*/
