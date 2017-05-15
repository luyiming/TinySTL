#include "priority_queue.hpp"
#include "gtest/gtest.h"

#include <functional>
#include <iostream>

TEST(PriorityQueueTest, test1) {
    TinySTL::priority_queue<int> pq;
    EXPECT_TRUE(pq.empty());

    for (int i = 10; i >= 0; i--) {
        pq.push(i);
    }

    EXPECT_EQ(11, pq.size());

    for (int i = 0; i <= 10; i++) {
        EXPECT_EQ(i, pq.top());
        pq.pop();
    }
    EXPECT_TRUE(pq.empty());
}

TEST(PriorityQueueTest, test2) {
    TinySTL::vector<int> vec = { 1,3,2,4,0 };

    TinySTL::priority_queue<int> pq1(vec.begin(), vec.end());
    EXPECT_EQ(pq1.size(), vec.size());
    for (size_t i = 0; i < vec.size(); i++) {
        EXPECT_EQ(pq1.top(), i);
        pq1.pop();
    }
    EXPECT_TRUE(pq1.empty());

    TinySTL::priority_queue<int, TinySTL::vector<int>, std::greater<int>> 
        pq2(vec.begin(), vec.end());
    EXPECT_EQ(pq2.size(), vec.size());
    for (size_t i = 0; i < vec.size(); i++) {
        EXPECT_EQ(pq2.top(), vec.size() - i - 1);
        pq2.pop();
    }
    EXPECT_TRUE(pq2.empty());
}
