// Cola de prioridad generica minima

#ifndef __MIN_HEAP_H__
#define __MIN_HEAP_H__

#include <iostream>
#include <vector>


template<typename T>
class MinHeap {
using namespace std;

private:
    vector<T> items;
    int capacity, lastIndex; // capacity - lastIndex son los espacios desperdiciados

    /* funciones con las que obtenemos indices de interes */
    inline int leftChildIndex(const int i) { return 2 * i + 1; }
    inline int rightChildIndex(const int i) { return 2 * i + 2; }
    inline int parentIndex(const int i) { return (i - 1) / 2; }

    inline bool hasParent(const int i) { return parentIndex(i) >= 0; }
    inline bool hasLeftChild(const int i) { return leftChildIndex(i) < lastIndex; }
    inline bool hasRightChild(const int i) { return rightChildIndex(i) < lastIndex; }

    void ensureCapacity() {
        if (lastIndex == items.size()) {
            capacity *= 2;
            items.resize(capacity);
        }
    }

    void  bubbleUp(int current) {
        if (!hasParent(current)) return;
        int parent = parentIndex(current);
        if (items[current] < items[parent]) {

            // se viola la propiedad del MinHeap, corregir recursivamente
            swap(items[current], items[parent]);
            bubbleUp(parent);
        }
    }

    int maxChildIndex(int pos) {
        if (hasLeftChild(pos) && hasRightChild(pos)) {
            int l = leftChildIndex(pos), r = rightChildIndex(pos);
            return (items[l] < items[r]) ? r: l;
        }
        if (hasLeftChild(pos)) return leftChildIndex(pos);
        if (hasRightChild(pos)) return rightChildIndex(pos);
        return -1; // no tiene hijos
    }

    void bubbleDown(int current) {
        int childIndex = maxChildIndex(current);
        if (childIndex < 0) return; // no tiene hijos, alto
        if (items[current] < items[childIndex]) {
            swap(items[current], items[childIndex]);
            bubbleDown(childIndex);
        }
    }

public:

    MinHeap(): capacity(2), lastIndex(0) {  }
    MinHeap(uint cap): capacity(cap), lastIndex(0) {  }

    void add(T x) {
        ensureCapacity();
        items[lastIndex++] = x;
        bubbleUp(capacity);
    }

    inline T top() { return items[0]; }

    inline bool empty() { return lastIndex == 0; }
    
    T pop() {
        if (empty()) return nullptr;
        swap(items[0], items[lastIndex--]);
        bubbleDown(0);
        return items[0];
    }

};

#endif