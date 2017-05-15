#include "priority_queue.hpp"
#include "gtest/gtest.h"

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

