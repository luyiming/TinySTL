/**
 * @file    MinHeap.hpp
 * @author  Lu Yiming <luyimingchn@gmail.com>
 * @version 1.0
 * @date    2017-1-4
 */

#ifndef MINHEAP_HPP
#define MINHEAP_HPP

#include <cstdlib>

template<typename T>
class MinHeap {
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

#include "detail/MinHeap.impl.hpp"

#endif // MINHEAP_HPP
