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
    int A[ARRAYSIZE];

    cout << "selectSort:" << endl;
    for (int sz = 1000; sz < ARRAYSIZE; sz *= 5) {
        for (int i = 0; i < sz; i++) {
            A[i] = rand();
        }
        Profiler::start();
        selectSort(A, sz);
        Profiler::stop();
        cout << "size: " << sz << "\t";
        Profiler::dumpDuringTime(cout);
    }

    cout << "heapSort:" << endl;
    for (int sz = 1000; sz < ARRAYSIZE; sz *= 5) {
        for (int i = 0; i < sz; i++) {
            A[i] = rand();
        }
        Profiler::start();
        heapSort(A, sz);
        Profiler::stop();
        cout << "size: " << sz << "\t";
        Profiler::dumpDuringTime(cout);
    }

    cout << "sort:" << endl;
    for (int sz = 1000; sz < ARRAYSIZE; sz *= 5) {
        for (int i = 0; i < sz; i++) {
            A[i] = rand();
        }
        Profiler::start();
        sort(A, A + sz);
        Profiler::stop();
        cout << "size: " << sz << "\t";
        Profiler::dumpDuringTime(cout);
    }
    return 0;
}
