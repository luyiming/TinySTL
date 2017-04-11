#include <algorithm>
#include <iostream>
#include "Profiler.hpp"

using namespace std;

class MaxHeap {
   private:
    int *heap;
    int heapSize;
    int maxSize;
    int parent(int k) { return (k - 1) / 2; }
    int leftChild(int k) { return 2 * k + 1; }
    int rightChild(int k) { return 2 * k + 2; }

    void overflowHandle() {
        if (heapSize == 0) {
            heap = new int[1];
            heapSize = 1;
        } else {
            int *tmp = heap;
            heap = new int[2 * heapSize];
            for (int i = 0; i < heapSize; i++) {
                heap[i] = tmp[i];
            }
            heapSize *= 2;
            delete[] tmp;
        }
    }

   public:
    MaxHeap() {
        heap = NULL;
        heapSize = maxSize = 0;
    }

    MaxHeap(int n) {
        heap = new int[n];
        maxSize = n;
        heapSize = 0;
    }

    void insert(int k) {
        heap[heapSize++] = k;
        siftUp(heapSize - 1);
    }

    void siftUp(int start) {
        int q = start;
        int p;
        while (q > 0) {
            p = parent(q);
            if (heap[p] < heap[q]) {
                swap(heap[p], heap[q]);
                q = p;
            } else {
                break;
            }
        }
    }

    void siftDown() {
        int p = 0, q;
        while (leftChild(p) < heapSize) {
            q = leftChild(p);
            if (rightChild(p) < heapSize &&
                heap[leftChild(p)] < heap[rightChild(p)]) {
                q = rightChild(p);
            }
            if (heap[p] >= heap[q]) {
                break;
            }
            swap(heap[p], heap[q]);
            p = q;
        }
    }

    int promote(int start, int currentHeight, int stopHeight) {
        int p = start, q;
        while (currentHeight > stopHeight && leftChild(p) < heapSize) {
            q = leftChild(p);
            if (rightChild(p) < heapSize &&
                heap[leftChild(p)] < heap[rightChild(p)]) {
                q = rightChild(p);
            }
            swap(heap[p], heap[q]);
            p = q;
            currentHeight--;
        }
        return p;
    }
    void accerlerated_siftDown() {
        int height = 1;
        int p = heapSize - 1;
        while (p > 0) {
            p = parent(p);
            height++;
        }
        int stopPoint = 0;
        while (height > 1) {
            stopPoint = promote(stopPoint, height, height / 2);
            height /= 2;
            if (heap[stopPoint] > heap[parent(stopPoint)]) {
                siftUp(stopPoint);
                break;
            }
        }
    }

    int popMax() {
        int tmp = heap[0];
        heap[0] = heap[--heapSize];
        accerlerated_siftDown();
        return tmp;
    }

    int &top() { return heap[0]; }
    bool isEmpty() { return heapSize == 0; }
    int size() { return heapSize; }
};

void heapSort(int *A, int n) {
    MaxHeap heap(n);
    for (int i = 0; i < n; i++) {
        heap.insert(A[i]);
    }
    int index = 0;
    while (!heap.isEmpty()) {
        A[index++] = heap.popMax();
    }
}

void test(int n) {
    for (int i = 0; i <= n; i++) {
        cout << "*";
    }
    cout << endl;
}

void selectSort(int *A, int n) {
    for (int i = 0; i < n; i++) {
        int minIndex = i;
        for (int j = i + 1; j < n; j++) {
            if (A[j] < A[minIndex]) {
                minIndex = j;
            }
        }
        swap(A[minIndex], A[i]);
    }
}

#define ARRAYSIZE 100000
int main() {
    Profiler profiler;
    profiler.AlgorithmProfiler(test);
    int A[ARRAYSIZE];

    for (int sz = 1000; sz < ARRAYSIZE; sz *= 5) {
        for (int i = 0; i < sz; i++) {
            A[i] = rand();
        }
        profiler.start(sz);
        selectSort(A, sz);
        profiler.stop();
    }
    profiler.dump();

    Profiler profiler2;
    for (int sz = 1000; sz < ARRAYSIZE; sz *= 5) {
        for (int i = 0; i < sz; i++) {
            A[i] = rand();
        }
        profiler2.start(sz);
        heapSort(A, sz);
        profiler2.stop();
    }
    profiler2.dump();

    Profiler profiler3;
    for (int sz = 1000; sz < ARRAYSIZE; sz *= 5) {
        for (int i = 0; i < sz; i++) {
            A[i] = rand();
        }
        profiler3.start(sz);
        sort(A, A + sz);
        profiler3.stop();
    }
    profiler3.dump();
    return 0;
}
