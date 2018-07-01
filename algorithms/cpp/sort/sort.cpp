#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stack>

#include <cassert>

#include "bst.h"

using namespace std;

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

void create_subfile(const char *path, const char *name, size_t lines) {
    int i = 0;
    ifstream istream(path);
    ofstream ostream(name);
    string tmp;
    assert(istream.is_open());
    while (i++ < lines && istream >> tmp) ostream << tmp << endl;
    ostream.close();
    istream.close();
}

void swap(int &a, int &b) {
    int tmp = a;
    a = b;
    b = tmp;
}

void bubblesort(vector<int> &v) {
    size_t len = v.size();
    bool change_presented;
    for (int i = 0; i < len; i++) {
        change_presented = false;
        for (int j = 0; j < len - i - 1; j++) {
            if (v[j] > v[j + 1]) {
                swap(v[j], v[j + 1]);
                change_presented = true;
            }
        }
        if (!change_presented) return;
    }
}

void selectionsort(vector<int> &v) {
    size_t n = v.size();
    for (int i = 0; i < n; i++) {
        int minpos = i;
        for (int j = i + 1; j < n; j++) {
            if (v[j] < v[minpos]) {
                minpos = j;
            }
        }
        swap(v[i], v[minpos]);
    }
}

void insertionsort(vector<int> &v) {
    size_t n = v.size();
    for (int i = 1; i < n; i++) {
        int j = i;
        int val = v[i];
        while (j > 0 && v[j - 1] > val) {
            v[j] = v[j - 1];
            j--;
        }
        v[j] = val;
    }
}

void shellsort(vector<int> &v) {
    size_t n = v.size();
    int gap = 1;
    while (gap < n / 3) gap = gap * 3 + 1;
    while (gap > 0) {
        for (int i = gap; i < n; i++) {
            int tmp = v[i];
            int j = i;
            while (j > gap - 1 && v[j - gap] >= tmp) {
                v[j] = v[j - gap];
                j -= gap;
            }
            v[j] = tmp;
        }
        gap = (gap - 1) / 3;
    }
}

void treesort(vector<int> &v) {
    bst<int> tree(v);
    tree.sort(v);

}

void delete_node_from_bst_test() {
    //vector<int> v = { 3, 8, 0, 7, 4, 5 };
    vector<int> v = read_from_file("10millones.txt", 1e4);
    bst<int> tree(v);

    cout << "antes: " << endl;
    //tree.inorder();
    cout << "\nNumero de nodos: " << tree.numberOfNodes() << endl;

    for (int x: v) {
        cout << "\nElemento actual: " << x << endl;
        tree.remove(x);
        //tree.inorder();
        cout << endl;
    }
    cout << "despues: " << endl;
    tree.inorder();
    cout << "Numero de nodos: " << tree.numberOfNodes() << endl;
}

void sorttest() {
    vector<int> v = read_from_file("10millones.txt", 1e1);
    cout << "leidos" << endl;
    treesort(v);
    cout << "ordenados" << endl;
    for (int i = 0; i < v.size(); i++) cout << i << " " << v[i] << "\n";
}

int main(int argc, char const *argv[]) {
    vector<int> v = read_from_file("10millones.txt", 1e7);
    bst<int> tree(v);
    //for (int x: v) cout << x << ", ";
    cout << endl;
    cout << tree.contains(856834115) << endl;
    cout << tree.contains(966245083) << endl;
    cout << tree.contains(2045206161) << endl;
    return 0;
}

// create_subfile("10millones.txt", "diezmil.txt", 1e4);
//bubblesort(v);
//selectionsort(v);
//insertionsort(v);
//shellsort(v);