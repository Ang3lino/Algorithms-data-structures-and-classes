
#ifndef __HUFFNODE_H__
#define __HUFFNODE_H__

#include <iostream>
#include <map>

#include "MinHeap.h"

using namespace std;

struct HuffNode {
    HuffNode *left, *right;
    uint freq;
    u_char c; // caracter

    HuffNode(): c(0), left {nullptr}, right{nullptr}, freq(0) {  }
    HuffNode(u_char character): c(character), left {nullptr}, right{nullptr}, freq(0) {  }
    HuffNode(u_char character, uint frequency): c(character), 
            left {nullptr}, right{nullptr}, freq(frequency) {  }
    HuffNode(u_char character, uint frequency, HuffNode *l, HuffNode *r): 
        c(character), left {l}, right{r}, freq(frequency) {  }

    HuffNode(map<u_char, uint> mfreq): c(0), left {nullptr}, right{nullptr}, freq(0) { 
        HuffNode *root = new HuffNode();
        MinHeap <HuffNode> heap;

    }

    bool operator < (const HuffNode &that) {
        return this->freq < that.freq; 
        //return that.freq < this->freq; 
    }

    inline bool leaf() { return left == nullptr && right == nullptr; }

};

void print_tree (HuffNode *tree, int cont) {
	if (tree == nullptr) return;
	else {
		int i;
		print_tree (tree->right, ++cont);
		for (i = 0; i < cont; i++)
			printf ("  ");
        if (tree->c == 0) cout << '_' << endl;
        else cout << tree->c << endl;
		print_tree (tree->left, ++cont);
	}
}

inline void print_tree (HuffNode *tree) { print_tree(tree, 0); }

int nodes_amount(HuffNode *tree) {
    if (tree == NULL) return 0;
    return 1 + nodes_amount(tree->left) + nodes_amount(tree->right);
}

#endif