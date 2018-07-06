#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

// bibliotecas de C
#include <assert.h> // macro assert
#include <stdio.h> // funciones fread, fwrite 
#include <stdlib.h> 

#include "MinHeap.h"
#include "HuffNode.h"

using namespace std;

uint FLEN = 0; // almacenara la cantidad de caracteres del archivo

vector<int> read_from_file(const char * path, const int n) {
    vector<int> loaded;
    ifstream stream(path); // flujo de entrada
    int temp, i = 0;
    assert(stream.is_open());
    while (i < n && stream >> temp) {
        loaded.push_back(temp);
        i++;
    }
    stream.close();
    return loaded;
}

void heapsort_test() {
    vector<int> v = read_from_file("10e3.txt", 1e3); 
    //vector<int> v = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	MinHeap<int> heap;
	vector<int> w = MinHeap<int>::sort(v);
	for (auto x: w)
		cout << x << endl;
}
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
    for (int i = 0; i < n - 1; i++) { // memoria del puntero del ultimo z de sus hijos borrada! error
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

u_char *parse_file(const char *path) {
    FILE *src = fopen(path, "rb"); // lectura en binario de src (file pointer)
	u_char *original;
    if (src == NULL) {
		printf("El archivo %s no existe\n", path);
		exit(EXIT_FAILURE);
	}
    
    // obtenemos la cantidad de caracteres del archivo
	fseek(src, 0, SEEK_END); // colocamos el puntero al final del archivo
	FLEN = ftell(src); // obtenemos la posicion actual del cursero
	rewind(src); // colocamos el puntero al principio del archivo

    original = (u_char *) malloc(FLEN * sizeof(u_char));
    fread(original, sizeof(u_char), FLEN, src);

    fclose(src);
    return original;
}


void encode_file(const char *path) {
    u_char *original = parse_file(path); 
    map<u_char, uint> freq_chars = count_frequences(original);

    cout << "Frecuencias del archivo original" << endl;
    print_map(freq_chars);    
    HuffNode tree = build_huffman_tree(freq_chars);

    map<u_char, string> compressed;
    find_codes(&tree, "", compressed);
    cout << "\nFrecuencias del archivo comprimido" << endl;
    print_map(compressed);    
}

int main(int argc, char const *argv[]) {
    string path = "text.txt";
    //string path = "cpp/huffman/text.txt";
    encode_file(path.c_str());
    //heapsort_test();

    cout << endl;
    return 0;
}

//create_subfile("10millones.txt", "10e3.txt", 10e3);
