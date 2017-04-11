/**
 * @file    MinHeap.impl.hpp
 * @author  Lu Yiming <luyimingchn@gmail.com>
 * @version 1.0
 * @date    2017-1-4
 */

#ifndef MINHEAP_IMPL_HPP
#define MINHEAP_IMPL_HPP

#include "MinHeap.hpp"
#include <iostream>
#include <cassert>

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

#endif // MINHEAP_IMPL_HPP
