#ifndef bst_h
#define bst_h

#include <iostream>
#include <vector>
#include <stack>

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
            BinaryNode *parent, *current = root; // empezamos estando en la raiz del arbol
            BinaryNode *toInsert = new BinaryNode(data); 
            bool lastLeft = false; // nos indicara si somos izq. o der. de nuestro padre
            while (current != nullptr) {
                parent = current;
                lastLeft = data < current->data;
                if (data < current->data) current = current->left;
                else if (data > current->data) current = current->right;
                else return root; // no permitimos duplicados
            }

            // empezamos a conectar el nuevo nodo
            toInsert->parent = parent;
            if (lastLeft) parent->left = toInsert; 
            else parent->right = toInsert;
        }
        return root;
    }

    void inorder(BinaryNode *self) {
        if (self == nullptr) return;
        inorder(self->left);
        cout << self->data << ", ";
        inorder(self->right);
    }

    BinaryNode *min(BinaryNode *root) {
        if (root != nullptr)
            while (root->left != nullptr)
                root = root->left;
        return root;
    }


    inline bool leaf(BinaryNode *node) {
        return node->right == nullptr && node->left == nullptr;
    }

    int numberOfNodes(BinaryNode *root) {
        if (root == nullptr) return 0;
        return numberOfNodes(root->left) + numberOfNodes(root->right) + 1;
    }

    void remove(BinaryNode *&self, BinaryNode *parent, const T &x) {
        if (self == nullptr) return; // no encontrado
        if (x < self->data) remove(self->left, self, x);
        else if (self->data < x) remove(self->right, self, x);
        // encontrado!
        else if (self->left != nullptr && self->right != nullptr) { // dos hijos
            self->data = min(self->right)->data;
            remove(self->right, self, self->data); // eliminamos el sucesor duplicado
        } else { // el nodo tiene a lo mas 1 hijo
            BinaryNode *old = self; // guardamos la direccion del nodo a ser borrado
            self = (self->left != nullptr) ? self->left: self->right;
            if (self != nullptr) self->parent = parent;
            delete old;
        }
    }

    void destroy(BinaryNode *&root) {
        if (root != nullptr) {
            destroy(root->left);
            destroy(root->right);
            delete root;
        }
        root = nullptr;
    }

    bool contains(const BinaryNode *self, const T x) {
        if (self == nullptr) return false;
        if (self->data == x) return true;
        if (x < self->data) return contains(self->left, x);
        else return contains(self->right, x);
    }

public:

    bool contains(const T toFind) {
        return contains(root, toFind);
    }

    inline void remove(T x) {
        remove(root, nullptr, x);
    }

    inline ~bst() { 
        destroy(root);
    }

    inline bst() { root = nullptr; } 

    bst(vector<T> v) {
        root = nullptr;
        for (T x: v) 
            root = add(root, x);
    }

    int numberOfNodes() {
        return numberOfNodes(root);
    }

    inline void add(T data) { 
        root = add(root, data); // actualizamos la nueva raiz 
    }

    inline void inorder() { inorder(root); }

    void sort(vector<T> &v) {
        for (T x: v) add(x);

        // recorrido en inorden
        stack<BinaryNode *> s;
        BinaryNode *curr = root;
        T data;
        int i = 0;
        while (true) {
            if (curr != nullptr) {
                s.push(curr);
                curr = curr->left;
            } else {
                if (s.empty()) break; // el nodo actual es nulo y la pila esta vacia
                curr = s.top();  
                s.pop();
                data = curr->data;
                v[i++] = data;
                curr = curr->right;
            }
        }
    }
};

#endif 