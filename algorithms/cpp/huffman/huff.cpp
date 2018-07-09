#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

// bibliotecas de C
#include <assert.h> // macro assert
#include <stdio.h> // funciones fread, fwrite 
#include <stdlib.h> 
#include <math.h> 
#include <string.h>

#include "MinHeap.h"
#include "HuffNode.h"

using namespace std;

uint FLEN = 0; // almacenara la cantidad de caracteres del archivo
const char *BINARY_EXTENSION = "bin";
const char NULL_SYMBOL = '$';

/*
 *    Esta función apaga un bit específico de un arreglo de Chars
 *        p: 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17...
 *        i: 0 0 0 0 0 0 0 0 1 1 1  1  1  1  1  1  1  2 ...
 *        j: 0 1 2 3 4 5 6 7 0 1 2  3  4  5  6  7  0  1 ...
 *
 *    128 = 1000 0000, 
 *    128 >> 3 = 0001 0000
 */
void bit_down(u_char *data, size_t pos) {
	size_t i = pos >> 3; // Calculamos en qué byte está el bit que buscamos
	int j = pos & 7; // Calculamos la posición del bit dentro del byte
	data[i] &= ~(128 >> j); // Mediante un AND, apagamos el bit correspondiente
}

/* Esta función prende un bit específico de un arreglo de Chars */
void bit_up(u_char *data, size_t pos) {
        size_t i = pos >> 3; // Calculamos en qué byte está el bit que buscamos
        int j = pos & 7; // Calculamos la posición del bit dentro del byte
        data[i] |= (128 >> j); // Mediante un OR, prendemos el bit correspondiente
}

// void heapsort_test() {
//     vector<int> v = read_from_file("10e3.txt", 1e3); 
//     //vector<int> v = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
// 	MinHeap<int> heap;
// 	vector<int> w = MinHeap<int>::sort(v);
// 	for (auto x: w)
// 		cout << x << endl;
// }

map<u_char, uint> count_frequences(const u_char *source) {
    map<u_char, uint> mfreq;
    for (int i = 0; i < FLEN; i++)
        mfreq[source[i]] = 0; // se inician las frecuencias explicitamente en 0
    for (int i = 0; i < FLEN; i++)
        mfreq[source[i]]++;
    return mfreq; 
}

void find_codes(HuffNode *node, string walk, map<u_char, string> &table) {
    if (node->leaf()) 
        table[node->c] = walk;
    else {
        find_codes(node->left, walk + "0", table);
        find_codes(node->right, walk + "1", table);
    }
}

template<typename K, typename V>
void print_map(const map<K, V> mfreq) {
    for (auto x: mfreq) 
        cout << "key: " << x.first << " value: " << x.second << "\n";
}

/** Funcion que retorna la raiz del arbol Huffman.
 * observaciones:
 *  Se debe reservar memoria en el heap en las ramas del nodo z, de no ser asi seran 
 * eliminadas en la siguiente vuelta del bucle, al conectar estas ramas tambien hay que 
 * pasarles el apuntador a sus hijos.
 *  La sobrecarga de operadores definida sobre un tipo no funciona apropiadamente cuando
 * una clase o estructura parametrizada hace uso de este. 
 */    
HuffNode build_huffman_tree(const map<u_char, uint> mfreq) {
    MinHeap<HuffNode> heap;
    int n = mfreq.size();
    for (auto x: mfreq) 
        heap.add(HuffNode(x.first, x.second)); // construimos el heap
    for (int i = 0; i < n - 1; i++) { 
        HuffNode x, y, z;
        x = heap.pop();
        z.left = new HuffNode(x.c, x.freq, x.left, x.right); // importante reservar memoria en el heap
        y = heap.pop();
        z.right = new HuffNode(y.c, y.freq, y.left, y.right);
        z.freq = x.freq + y.freq;
        heap.add(z);
    }
    HuffNode x = heap.pop();
    return x;
}

/* Funcion mejorada de fopen, retorna un puntero FILE no nulo */
FILE *fopen_ok(const char *name, const char *mode) {
    FILE *fp = fopen(name, mode); // lectura en binario de fp (file pointer)
    if (fp == NULL) {
		printf("El archivo %s no existe\n", name);
		exit(EXIT_FAILURE);
	}
    return fp;
}

u_char *file_to_u_char_ptr(const char *path) {
    FILE *src = fopen_ok(path, "rb"); // lectura en binario de src (file pointer)
	u_char *original;
    // obtenemos la cantidad de caracteres del archivo
	fseek(src, 0, SEEK_END); // colocamos el puntero al final del archivo
	FLEN = ftell(src); // obtenemos la pos actual del cursero
	rewind(src); // colocamos el puntero al principio del archivo

    original = (u_char *) malloc(FLEN * sizeof(u_char));
    fread(original, sizeof(u_char), FLEN, src);

    fclose(src);
    return original;
}

int create_encoded_file(const u_char *original, const char *path, 
		map<u_char, string> walks) {
	int bits = 0;
	char new_name[99];
	u_char *encoded = (u_char *) malloc(FLEN * sizeof(u_char));
	for (uint i = 0; i < FLEN; i++) {
		string str = walks[original[i]];
		for (uint j = 0; j < str.size(); j++)
			(str[j] == '1') ? bit_up(encoded, bits++): bit_down(encoded, bits++);
	}

	sprintf(new_name, "%s.huff", path);
	FILE *fp = fopen_ok(new_name, "wb");
	fwrite(encoded, sizeof(u_char), ceil(bits / 8), fp);

	free(encoded);
	fclose(fp);
	return bits;
}

int nodes_amount(HuffNode *tree) {
    if (tree == NULL) return 0;
    return 1 + nodes_amount(tree->left) + nodes_amount(tree->right);
}

void preorder_serialize(HuffNode *self, FILE *fp) {
    if (self == nullptr) {
        fprintf(fp, "%hhu ", NULL_SYMBOL);
        return; 
    }
    fprintf(fp, "%hhu ", self->c);
    preorder_serialize(self->left, fp);
    preorder_serialize(self->right, fp);
}

/** Retorna putero a un nombre con extension. (str + . + ext)
 *   El puntero deberia ser liberado despues. */    
char *str_extension(const char *str, const char *ext) {
    char new_name[99];
    sprintf(new_name, "%s.%s", str, ext);
    int n = strlen(new_name); // considera el '\0' ?
    char *ans = (char *) malloc(sizeof(char) * n);
    strncpy(ans, new_name, n + 1);
    return ans;
}

void save_tree(HuffNode *tree, const char *name) {
    char *new_name = str_extension(name, BINARY_EXTENSION);
    FILE *fp = fopen_ok(new_name, "wb");
    preorder_serialize(tree, fp);
    fclose(fp);
    free(new_name);
}

int encode_file(const char *path) {
	int bits = 0;
    u_char *original = file_to_u_char_ptr(path); 

    map<u_char, uint> freq_chars = count_frequences(original);

    //cout << "Frecuencias del archivo original" << endl;
    //print_map(freq_chars);    
    HuffNode tree = build_huffman_tree(freq_chars);

    map<u_char, string> walks;
    find_codes(&tree, "", walks);
    //cout << "\nFrecuencias del archivo comprimido" << endl;
    //print_map(walks);    

	bits = create_encoded_file(original, path, walks);
    save_tree(&tree, path);
    print_tree(&tree);
	return bits;
}

void rebuild_tree(FILE *fp, HuffNode *&tree) {
    u_char symbol;
    // por que se escanea por hhu?
    if (fscanf(fp, "%hhu ", &symbol) != EOF && symbol != NULL_SYMBOL) {
        tree = new HuffNode(symbol);
        rebuild_tree(fp, tree->left);
        rebuild_tree(fp, tree->right);
    }
}

HuffNode *get_tree_from_bin(const char *path) {
    char *new_name = str_extension(path, BINARY_EXTENSION);
    FILE *fp = fopen_ok(new_name, "rb");
    HuffNode *tree;
    rebuild_tree(fp, tree);
    return tree;
}

/** Decofica el archivo.
 *  Se asume que el argumento path tiene el nombre del archivo original (sin .huff o .bin).
 */
void decode_file(const char *path) {
    HuffNode *tree = get_tree_from_bin(path);
    print_tree(tree);
}

int main(int argc, char const *argv[]) {
    //string path = "intro.pdf";
    //string path = "cpp/huffman/text.txt";
    string path = "text.txt";
    char option = 0;
    //string path = "10e3.txt";

    while (option != 'q') {
        cout << "\nSeleccione una opcion: " << endl;
        cout << "e.- codificar " << endl;
        cout << "d.- decodificar " << endl;
        cout << "q.- salir " << endl;

        cin >> option;

        switch (option) {
            case 'e': encode_file(path.c_str()); break;
            case 'd': decode_file(path.c_str()); break;
            case 'q': cout << "hasta luego" << endl; break;
            default: cout << "Opcion invalida";
        }
    }

    cout << endl;
    return 0;
}

//create_subfile("10millones.txt", "10e3.txt", 10e3);