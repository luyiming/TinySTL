#ifndef PRIORITY_QUEUE_HPP
#define PRIORITY_QUEUE_HPP

#include <iostream>
#include <cassert>
#include <algorithm>
#include "Vector.hpp"

namespace TinySTL {

    template<typename T>
    class priority_queue {
    public:
        const T& top() const;
        void pop();
        void push(const T &x);
        void increaseKey(const T& k, const T& newKey); // O(n) TODO: O(logn)
        void decreaseKey(const T& k, const T& newKey); // O(n) TODO: O(logn)
        T& find(const T& k);

        bool empty() const;
        void clear();
        int size() const;

    private:
        TinySTL::vector<T> heap; // min heap
        void siftDown(int start, int end);
        void siftUp(int start);
    };

    template <typename T>
    const T& priority_queue<T>::top() const {
        return heap[0];
    }

    template <typename T>
    void priority_queue<T>::pop() {
        heap[0] = heap[heap.size() - 1];
        heap.pop_back();
        siftDown(0, heap.size() - 1);
    }

    template <typename T>
    void priority_queue<T>::push(const T &x) {
        heap.push_back(x);
        siftUp(heap.size() - 1);
    }

    template <typename T>
    void priority_queue<T>::increaseKey(const T& k, const T& newKey) {
        int i;
        for (i = 0; i < heap.size(); i++) {
            if (heap[i] == k) {
                heap[i] = newKey;
                break;
            }
        }
        siftDown(i, heap.size() - 1);
    }

    template <typename T>
    void priority_queue<T>::decreaseKey(const T& k, const T& newKey) {
        int i;
        for (i = 0; i < heap.size(); i++) {
            if (heap[i] == k) {
                heap[i] = newKey;
                break;
            }
        }
        siftUp(i);
    }

    template <typename T>
    T& priority_queue<T>::find(const T& k) {
        int i;
        for (i = 0; i < heap.size(); i++) {
            if (heap[i] == k) {
                return heap[i];
            }
        }
        return T();
    }

    template <typename T>
    void priority_queue<T>::clear() {
        heap.clear();
    }

    template <typename T>
    bool priority_queue<T>::empty() const {
        return heap.empty();
    }

    template <typename T>
    int priority_queue<T>::size() const {
        return heap.size();
    }

    template <typename T>
    void priority_queue<T>::siftDown(int start, int end) {
        int p = start;
        while (p < end) {
            int k = 2 * p + 1;
            if (k >= heap.size())
                break;
            if (k + 1 < heap.size() && heap[k + 1] < heap[k])
                k++;
            if (heap[p] < heap[k])
                break;
            std::swap(heap[k], heap[p]);
            p = k;
        }
    }

    template <typename T>
    void priority_queue<T>::siftUp(int start) {
        int p = start;
        while (p > 0) {
            int k = (p - 1) / 2;
            if (heap[k] < heap[p])
                break;
            std::swap(heap[k], heap[p]);
            p = k;
        }
    }

} // namespace TinySTL 


#endif // PRIORITY_QUEUE_HPP