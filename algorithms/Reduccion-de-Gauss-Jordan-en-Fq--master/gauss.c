/* Programa que resuelve un sistema de ecuaciones con enteros modulo n con memoria dinamica.
 	por Angel Lopez Manriquez. 	*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

/* Funcion que guarda espacio para una matriz de tamanio m(m + 1). */
int **genMat (int m){
	int n = m + 1;
	int i = 0;
	int **a = 0;

	a = (int **) calloc (sizeof (int), m);
	for (i = 0; i < m; i++)
		a[i] = (int *) calloc (sizeof (int *), n);

	if (!a){
		puts ("No hay espacio suficiente. ");
		exit (1);
	}

	return a;
}

/*	Muestra un mensaje que indica si la matriz escalonada reducida dada es consistente o no		*/
void
determineConsistency (int **mat, int m){
	m--;
	int n = m + 1;

	if (mat[m][m] == 0 && mat[m][n] == 0)
		puts ("El sistema tiene infinitas soluciones.");
	else if (mat[m][m] == 0 && mat[m][n] != 0)
		puts ("El sistema dado es inconsistente. ");
	else if (mat[m][m] != 0)
		puts ("El sistema dado es tiene solucion unica. ");
}

/* Funcion que imprime los elementos de la matriz. */
void
printMat (int **a, int m){
	int i = 0, j = 0;
	int n = m + 1;

	printf ("\n");

	for (i = 0; i < m; i++){
		for (j = 0; j < n; j++)
			printf ("%d \t", a[i][j]);
		printf ("\n\n");
	}

}

/*	Destruye el espacio reservado en memoria para la matriz.	*/
void
destroy (int **d, int m){
	int i = 0;

	for (i = 0; i < m; i++){
		free (d[i]);
	}

	free (d);
}

/* Funcion que cambia a un entero modulo n negativo a uno positivo,
	usando la definicion:
	 _    _____
	-a = (n - a) 	*/
int
posNum (int x, int modn){

	if (x < 0){
		x = x % modn;
		x = x + modn;
	}

	return x;
}

/*	Funcion que genera un numero aleatorio x, tal que x < |30| para
	cada elemento de la matriz.		*/
void
fillRand (int **a, int m){
	int n = m + 1, i = 0, j = 0, x = 0, y = 0;
	srand (time (NULL));

	for (i = 0; i < m; i++){
		for (j = 0; j < n; j++){
			x = rand () % 20;
			y = rand () % 3;
			a[i][j] = x * pow (-1, y);
		}
	}
}

/*	Calcula el modulo de todos los elementos de la matriz y los convierte a positivo.	*/
void
moduleAll (int **mat, int m, int modn){
	int i = 0, j = 0, n = m + 1;

	for (i = 0; i < m; i++){
		for (j = 0; j < n; j++){
			mat[i][j] = mat[i][j] % modn;
			mat[i][j] = posNum (mat[i][j], modn);
		}
	}
}

/* Funcion que devuelve el inverso multiplicativo en modulo n. No siempre funciona, pues si se esta
	en un modulo n y a = n, no existe tal inverso multiplicativo.
	
	Ademas: existe un x tal que ax % n = 1  ssi mcd (a, n) = 1, si n es primo, siempre existira un inverso
	multiplicativo.	*/
int
invMult (int a, int mod){
	int i = 0, ans =  0;

	for (i = 1; i < mod - 1; i++){
		ans = a * i;
		if (ans % mod == 1)
			return i;
	}

}

/* Funcion que suma todos los elementos de una fila a con una fila b.
   El resultado se colocara en la fila b. */
void
addRows (int **a, int posa, int posb, int m){
	int n = m + 1;
	int j = 0;

	for (j = 0; j < n; j++)
		a[posb][j] = a[posa][j] + a[posb][j];
}

/* Funcion que multplica a los elementos de una fila por un escalar. */
void
multRow (int **a, int posi, int escalar, int m){
	int j = 0;
	int n = m + 1;
	for (j = 0; j < n; j++)
		a[posi][j] = escalar * a[posi][j];
}

/*	Intercambia filas de la matriz	*/
void
swapRows (int **mat, const int filax, const int filay, const int m){
	int n = m + 1, i, j, temp = 0;
	int *aux = (int *) malloc (sizeof (int) * n);

	/* Guardando la fila y	*/
	for (j = 0; j < n; j++){
		temp = mat[filay][j];
		aux[j] = mat[filay][j];
	}

	/*	Pasando los elementos de la fila x a la fila y	*/
	for (j = 0; j < n; j++){
		temp = mat[filax][j];
		mat[filay][j] = temp;
	}

	for (j = 0; j < n; j++){
		mat[filax][j] = aux[j];
	}

	free (aux);
}

/*	Dada una matriz A en su forma escalonada reducida, esta funcion despeja a x_i multiplicando a cada fila
	por su inverso multiplicativo.	*/
void
clearVar (int **mat, const int m, const int modn){
	int i = 0, j = 0, inverso =  0;

	for (i = 0; i < m; i++){
		if (mat[i][i] == 1)
			continue;
		if (mat[i][i] != 0){
			if (mat[i][i] % modn != 0){
				inverso = invMult (mat[i][i], modn);
				multRow (mat, i, inverso, m);
			}
		}
	}

	moduleAll (mat, m, modn);
}

/*	Deja solo un uno (si es posible) en la columna j-esima.	*/
void
pivot (int **mat, int m, int modn){
	int i = 0, j = 0, x = 0, inverso, n = m + 1;

	for (x = 0; x < m; x++){
		for (i = 0; i < m; i++){
			if (mat[i][x] % modn != 0){
				inverso = invMult (mat[i][x], modn);
				multRow (mat, i, inverso, m);
			}
		}

		moduleAll (mat, m, modn);
		i = x + 1;
		while (mat[x][x] == 0 && i < m){
			swapRows (mat, i, x, m);
			i++;
		}

		for (i = 0; i < m; i++){
			if (mat[i][x] == 0)
				continue;
			if (i != x)
				multRow (mat, i, -1, m);
		}

		for (j = 0; j < m; j++){
			if (j != x && mat[j][x] != 0)
				addRows (mat, x, j, m);
		}

		moduleAll (mat, m, modn);
	}
}

/* Funcion que manda a llamar a todo el algoritmo, digamos que es la "Raiz" del programa 	*/
int
main (void){
	int **a = 0;
	int i = 0, filas = 0, columnas = 0, mod = 0;

	filas = 5;
	columnas = filas + 1;
	mod = 13;
	
	a = genMat (filas);
	fillRand (a, filas);
	
	printf ("Modulo: %d \n", mod);
	puts ("Antes: \n");
	printMat (a, filas);
	
	moduleAll (a, filas, mod);
	pivot (a, filas, mod);
	
	puts ("Despues: \n");
	clearVar (a, filas, mod);
	printMat (a, filas);
	determineConsistency (a, filas);

	destroy (a, filas);
	return 0;
}
