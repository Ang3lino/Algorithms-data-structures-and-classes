// MinHeap generico, se requiere que el operador < este definido

#ifndef __MIN_HEAP_H__
#define __MIN_HEAP_H__

#include <iostream>
#include <vector>

using namespace std;

template<typename T>
class MinHeap {

private:
    vector<T> items;
    int capacity, length; // capacity - length son los espacios desperdiciados

    /* funciones con las que obtenemos indices de interes */
    inline int leftChildIndex(const int i) { return 2 * i + 1; }
    inline int rightChildIndex(const int i) { return 2 * i + 2; }
    inline int parentIndex(const int i) { return (i - 1) / 2; }

    inline bool hasParent(const int i) { return 0 < i; }
    inline bool hasLeftChild(const int i) { return leftChildIndex(i) < length; }
    inline bool hasRightChild(const int i) { return rightChildIndex(i) < length; }

    inline T leftChild(const int i) { return items[leftChildIndex(i)]; }
    inline T rightChild(const int i) { return items[rightChildIndex(i)]; }
    inline T parent(const int i) { return items[parentIndex(i)]; }

    /** Redimensiona la capacidad del vector si es necesario */
    void ensureCapacity() {
        if (length == items.size()) {
            capacity *= 2;
            items.resize(capacity);
        }
    }

    void  bubbleUp(int current) {
        if (hasParent(current) && items[current] < parent(current)) {
            int parent = parentIndex(current);

            // se viola la propiedad del MinHeap, corregir recursivamente
            swap(items[current], items[parent]);
            bubbleUp(parent);
        }
    }

    /** Retorna -1 en caso de ser hoja */
    int minChildIndex(int p) {
        int i = -1;
        if (hasLeftChild(p)) i = leftChildIndex(p);
        if (hasRightChild(p)) 
            i = (leftChild(p) < rightChild(p)) ? i: rightChildIndex(p);
        return i; 
    }

    void bubbleDown(int index) {
        int m = minChildIndex(index); // si fuese MaxHeap obtendriamos el maximo
        if (m < 0 || items[index] < items[m]) return;
        swap(items[index], items[m]);
        bubbleDown(m);
    }

public:

    MinHeap(): capacity(2), length(0) {  }
    MinHeap(uint cap): capacity(cap), length(0) {  }

    void add(T x) {
        ensureCapacity();
        items[length] = x;
        bubbleUp(length++);
    }

    /** Heapsort: dado un vector v se devuelve un vector equivalente w ordenado 
     * ascendetemente */ 
	static vector<T> sort(const vector<T> &v) {
		MinHeap<T> *heap = new MinHeap();
		vector<T> w;
		for (int x: v) heap->add(x);
		while (!heap->empty()) w.push_back(heap->pop());	
		delete heap;
		return w;
	}

    inline T top() {  
        if (empty()) throw "top operation couldn't be performed, Empty Heap";
        return items[0]; // revolvemos la raiz
    }

    inline bool empty() { return length == 0; }

    T pop() {
        if (empty()) throw "pop operation couldn't be performed, Empty Heap";
        T returnable = items[0];
        items[0] = items[--length];
        bubbleDown(0);
        return returnable;
    }

};

#endif
