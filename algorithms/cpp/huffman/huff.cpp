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


#include "MinHeap.h"
#include "HuffNode.h"

using namespace std;

uint FLEN = 0; // almacenara la cantidad de caracteres del archivo

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
        mfreq[source[i]] = 0;
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

u_char *file_to_u_char_ptr(const char *path) {
    FILE *src = fopen(path, "rb"); // lectura en binario de src (file pointer)
	u_char *original;
    if (src == NULL) {
		printf("El archivo %s no existe\n", path);
		exit(EXIT_FAILURE);
	}
    
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
	char new_name[999];
	u_char *encoded = (u_char *) malloc(FLEN * sizeof(u_char));
	for (uint i = 0; i < FLEN; i++) {
		string str = walks[original[i]];
		for (uint j = 0; j < str.size(); j++)
			(str[j] == '1') ? bit_up(encoded, bits++): bit_down(encoded, bits++);
	}

	sprintf(new_name, "%s.huff", path);
	FILE *fp = fopen(new_name, "wb");
	fwrite(encoded, sizeof(u_char), ceil(bits / 8), fp);

	free(encoded);
	fclose(fp);
	return bits;
}

int encode_file(const char *path) {
	int bits = 0;
    u_char *original = file_to_u_char_ptr(path); 

    map<u_char, uint> freq_chars = count_frequences(original);

    cout << "Frecuencias del archivo original" << endl;
    print_map(freq_chars);    
    HuffNode tree = build_huffman_tree(freq_chars);

    map<u_char, string> walks;
    find_codes(&tree, "", walks);
    cout << "\nFrecuencias del archivo comprimido" << endl;
    print_map(walks);    

	bits = create_encoded_file(original, path, walks);
	return bits;
}

int main(int argc, char const *argv[]) {
    //string path = "intro.pdf";
    //string path = "cpp/huffman/text.txt";
    string path = "text.txt";
    //string path = "10e3.txt";
    encode_file(path.c_str());
    //heapsort_test();

    cout << endl;
    return 0;
}

//create_subfile("10millones.txt", "10e3.txt", 10e3);
