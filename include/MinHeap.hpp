#ifndef MINHEAP_HPP
#define MINHEAP_HPP

#include <cstdlib>
#include <iostream>
#include <cassert>
#include "Memory.hpp"

namespace TinySTL {

    template <typename T>
    class MinHeap {
    public:
        using value_type = T;
        //using allocator_type = Alloc;
        using reference = value_type&;
        using const_reference = const value_type&;
        using pointer = value_type*;
        using const_pointer = const value_type*;
        using iterator = value_type*;
        using const_iterator = const value_type*;
        // TODO: using reverse_iterator = ??
        // TODO: using const_reverse_iterator = ??
        using difference_type = std::ptrdiff_t;
        using size_type = std::size_t;

    public:
        MinHeap();
        MinHeap(MinHeap<T>& rhs);
        ~MinHeap();
        MinHeap<T>& operator = (const MinHeap<T>& rhs);
        bool remove(T &x);
        void insert(const T &x);
        bool isEmpty() const;
        void clear();
        int size() const;

    private:
        T* heap = NULL;
        int currentSize;
        int maxSize;
        void siftDown(int start, int end);
        void siftUp(int start);
        const int growthFactor = 2;
        void overflowHandle();
    };

} // namespace TinySTL

namespace TinySTL {

    template <typename T>
    MinHeap<T>::MinHeap() {
        maxSize = 1;
        currentSize = 0;
        heap = new T[maxSize];
    }

    template <typename T>
    MinHeap<T>::MinHeap(MinHeap<T> &rhs) {
        maxSize = rhs.maxSize;
        currentSize = rhs.currentSize;
        heap = new T[maxSize];
        for (int i = 0; i < currentSize; ++i) {
            heap[i] = rhs.heap[i];
        }
    }

    template <typename T>
    MinHeap<T>::~MinHeap() {
        if (heap != NULL) {
            delete[] heap;
        }
    }

    template <typename T>
    void MinHeap<T>::clear() {
        currentSize = 0;
    }

    template <typename T>
    bool MinHeap<T>::isEmpty() const {
        return currentSize == 0;
    }

    template <typename T>
    void MinHeap<T>::overflowHandle() {
        assert(currentSize == maxSize);
        maxSize *= growthFactor;
        T* old_heap = heap;
        heap = new T[maxSize];
        for (int i = 0; i < currentSize; ++i) {
            heap[i] = old_heap[i];
        }
        delete[] old_heap;
    }

    template <typename T>
    MinHeap<T>& MinHeap<T>::operator = (const MinHeap<T>& rhs) {
        if (this != &rhs) {
            if (heap != NULL) {
                delete[] heap;
            }
            maxSize = rhs.maxSize;
            currentSize = rhs.currentSize;
            heap = new T[maxSize];
            for (int i = 0; i < currentSize; ++i) {
                heap[i] = rhs.heap[i];
            }
        }
        return *this;
    }

    template <typename T>
    void MinHeap<T>::siftDown(int start, int end) {
        int p = start;
        while (p < end) {
            int k = 2 * p + 1;
            if (k > currentSize)
                break;
            if (k + 1 < currentSize && heap[k] > heap[k + 1])
                k++;
            if (heap[p] < heap[k])
                break;
            T temp = heap[k];
            heap[k] = heap[p];
            heap[p] = temp;
            p = k;
        }
    }

    template <typename T>
    void MinHeap<T>::siftUp(int start) {
        int p = start;
        while (p > 0) {
            int k = (p - 1) / 2;
            if (heap[p] > heap[k])
                break;
            T temp = heap[k];
            heap[k] = heap[p];
            heap[p] = temp;
            p = k;
        }
    }

    template <typename T>
    void MinHeap<T>::insert(const T &x) {
        if (currentSize == maxSize)
            overflowHandle();
        heap[currentSize] = x;
        currentSize++;
        siftUp(currentSize - 1);
    }

    template <typename T>
    bool MinHeap<T>::remove(T &x) {
        if (currentSize == 0)
            return false;
        x = heap[0];
        heap[0] = heap[currentSize - 1];
        currentSize--;
        siftDown(0, currentSize - 1);
        return true;
    }

    template <typename T>
    int MinHeap<T>::size() const {
        return currentSize;
    }

} // namespace TinySTL

#endif // MINHEAP_HPP
