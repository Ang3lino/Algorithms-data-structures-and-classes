#include <iostream>
#include <fstream>
#include <string>
#include <vector>

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

void bst_search() {
    vector<int> v = read_from_file("10millones.txt", 1e5);
    bst<int> tree(v);
    //for (int x: v) cout << x << ", ";
    cout << endl;
    cout << tree.contains(856834115) << endl;
    cout << tree.contains(966245083) << endl;
    cout << tree.contains(2045206161) << endl;
}

bool linear_search(const vector<int> &v, int x) {
    for (int value: v) if (value == x) return true;
    return false;
}

void lineartest() {
    vector<int> v = read_from_file("10millones.txt", 1e4);
    for (int x: v) cout << x << ", ";
    cout << endl;
    cout << linear_search(v, 1234) << endl;
    cout << linear_search(v, 1226985352) << endl;
}

inline bool binary_search(const vector<int> &v, const int findable) {
    return bin_search(v, findable, 0, v.size() - 1);
} 
    
bool bin_search(const vector<int> &v, const int x, int left, int right) {
    if (left > right) return false;
    int i = (right - left) / 2;
    if (v[i] == x) return true;
    if (x < v[i]) return bin_search(v, x, left, right - i); 
    else return bin_search(v, x, left + i, right); 
}

int main(int argc, char const *argv[]) {
    vector<int> v = read_from_file("10millones.txt", 1e4);
    bst<int> tree;
    tree.sort(v);
    tree.inorder();
    return 0;
}
    //create_subfile("10millones.txt", "10e3.txt", 10e3);