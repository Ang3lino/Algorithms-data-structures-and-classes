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
    vector<int> v = read_from_file("10e3.txt", 1e4); 
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

HuffNode *build_huffman_tree(const map<u_char, uint> mfreq) {
    MinHeap<HuffNode *> heap;
    int n = mfreq.size();
    for (auto x: mfreq) {
        heap.add(new HuffNode(x.first, x.second));
    }
    for (int i = 0; i < n - 1; i++) {
        HuffNode *z = new HuffNode();
        z->left = heap.pop();
        z->right = heap.pop();
        z->freq = z->left->freq + z->right->freq;
        heap.add(z);
    }
    HuffNode *x = heap.pop();
    return x;
}

template<typename K, typename V>
void print_map(const map<K, V> mfreq) {
    for (auto x: mfreq) 
        cout << "key: " << x.first << " value: " << x.second << "\n";
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

void find_codes(HuffNode *node, string walk, map<u_char, string> &table) {
    if (node->leaf()) 
        table[node->c] = walk;
    else {
        find_codes(node->left, walk + "0", table);
        find_codes(node->right, walk + "1", table);
    }
}

void encode_file(const char *path) {
    u_char *original = parse_file(path); 
    map<u_char, uint> freq_chars = count_frequences(original);
    HuffNode *tree = build_huffman_tree(freq_chars);

    cout << "Frecuencias del archivo original" << endl;
    print_map(freq_chars);    

    map<u_char, string> compressed;
    find_codes(tree, "", compressed);
    cout << "\nFrecuencias del archivo comprimido" << endl;
    print_map(compressed);    
}

int main(int argc, char const *argv[]) {
    string path = "10e3.txt";
    //string path = "cpp/huffman/text.txt";
    encode_file(path.c_str());

    cout << endl;
    return 0;
}

//create_subfile("10millones.txt", "10e3.txt", 10e3);