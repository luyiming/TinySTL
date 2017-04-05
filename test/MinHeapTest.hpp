#ifndef MINHEAPTEST_HPP
#define MINHEAPTEST_HPP

#include "gtest/gtest.h"
#include "MinHeap.hpp"

TEST(MinHeapTest, Zero) {
    MinHeap<int> heap;
    EXPECT_TRUE(heap.isEmpty());
    int x;
    EXPECT_FALSE(heap.remove(x));
}

TEST(MinHeapTest, InsertAndRemove) {
    MinHeap<int> heap;
    for (int i = 0; i < 10; i++) {
        heap.insert(i);
    }
    EXPECT_EQ(10, heap.size());
    for (int i = 0; i < 10; i++) {
        int x;
        EXPECT_TRUE(heap.remove(x));
        EXPECT_EQ(i, x);
        EXPECT_EQ(10 - i - 1, heap.size());
        if (i != 9)
            EXPECT_FALSE(heap.isEmpty());
    }
    EXPECT_TRUE(heap.isEmpty());
}

TEST(MinHeapTest, RandomInsertAndRemove) {
    MinHeap<int> heap;
    for (int i = 0; i < 10; i++) {
        heap.insert(i);
    }
    int x;
    heap.remove(x);
    heap.insert(-1);
    heap.remove(x);
    EXPECT_EQ(-1, x);

    heap.insert(100);
    heap.insert(-100);
    heap.insert(200);
    heap.remove(x);
    EXPECT_EQ(-100, x);
}

#endif  // MINHEAPTEST_HPP
