#ifndef bst_h
#define bst_h

#include <iostream>
#include <vector>
#include <new>

using namespace std;

template < typename T >
class bst {

private:
    struct BinaryNode {
        T data;
        BinaryNode *left, *right, *parent;

        // constructores con iniciadores miembro
        BinaryNode(T mdata, BinaryNode *mleft, BinaryNode *mright, BinaryNode *mparent) 
            : data{ mdata }, left{ mleft }, right{ mright }, parent { mparent } { } 

        BinaryNode(T mdata) 
            : data{ mdata }, left{ nullptr }, right{ nullptr }, parent { nullptr } { } 

        BinaryNode() 
            : left{ nullptr }, right{ nullptr }, parent { nullptr } { } 
    };

    BinaryNode *root;

    BinaryNode *add(BinaryNode *root, T data) {
        if (root == nullptr) { // no se ha insertado nada previamente
            root = new BinaryNode(data);
        } else {
            BinaryNode *parent, 
                *current = root; // al principio estamos en la raiz del arbol
            BinaryNode *toInsert = new BinaryNode(data);
            bool lastLeft = false; // nos indicara si somos izq. o der. de nuestro padre
            while (current != nullptr) {
                parent = current;
                lastLeft = data < current->data;
                if (data < current->data) current = current->left;
                else  current = current->right;
            }
            toInsert->parent = parent;
            if (lastLeft) parent->left = new BinaryNode(data); 
            else parent->right = new BinaryNode(data);
        }
        return root;
    }

    void inorder(BinaryNode *self) {
        if (self == nullptr) return ;
        inorder(self->left);
        cout << self->data << "\n";
        inorder(self->right);
    }

public:

    inline bst() { root = nullptr; } 

    inline void add(T data) { 
        root = add(root, data); // actualizamos la nueva raiz 
    }

    inline void inorder() { inorder(root); }

};

#endif 