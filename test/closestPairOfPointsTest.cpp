#ifndef CLOSEST_PAIR_OF_POINTS_TEST_CPP
#define CLOSEST_PAIR_OF_POINTS_TEST_CPP

#include "algorithm/closestPairOfPoints.hpp"
#include "gtest/gtest.h"

TEST(closestPairOfPointsTest, SinglePoint) {
    Point testNodes[] = {{0, 1}, {0, 1}};
    EXPECT_DOUBLE_EQ(findMinDistance(testNodes, 0, 0),
                     std::numeric_limits<double>::max());
}

TEST(closestPairOfPointsTest, SameLine) {
    Point testNodes[5];
    testNodes[0] = Point(0, 1);
    testNodes[1] = Point(0, 2);
    testNodes[2] = Point(0, 4);
    testNodes[3] = Point(0, 7);
    testNodes[4] = Point(0, 9);
    EXPECT_DOUBLE_EQ(findMinDistance(testNodes, 0, 2), 1.0);

    testNodes[0] = Point(1, 0);
    testNodes[1] = Point(2, 0);
    testNodes[2] = Point(4, 0);
    testNodes[3] = Point(7, 0);
    testNodes[4] = Point(9, 0);
    EXPECT_DOUBLE_EQ(findMinDistance(testNodes, 0, 2), 1.0);
}

TEST(closestPairOfPointsTest, SamePoint) {
    Point testNodes[5];
    testNodes[0] = Point(1, 1);
    testNodes[1] = Point(1, 1);
    testNodes[2] = Point(0, 0);
    testNodes[3] = Point(1, 3);
    testNodes[4] = Point(2, 5);
    EXPECT_DOUBLE_EQ(findMinDistance(testNodes, 0, 4), 0.0);
}

TEST(closestPairOfPointsTest, smallSize) {
    const int NodeSize = 10;
    const int TESTNUM = 1000;
    Point testNodes1[NodeSize], testNodes2[NodeSize];
    for (int i = 0; i < TESTNUM; i++) {
        for (int j = 0; j < NodeSize; j++) {
            testNodes1[j] = Point(rand(), rand());
            testNodes2[j] = testNodes1[j];
        }
        double d1 = bruteForceFindMinDistance(testNodes1, 0, NodeSize - 1);
        double d2 = findMinDistance(testNodes2, 0, NodeSize - 1);
        EXPECT_DOUBLE_EQ(d1, d2);
    }
}

TEST(closestPairOfPointsTest, largeSize) {
    const int NodeSize = 5000;
    const int TESTNUM = 2;
    Point testNodes1[NodeSize], testNodes2[NodeSize];
    for (int i = 0; i < TESTNUM; i++) {
        for (int j = 0; j < NodeSize; j++) {
            testNodes1[j] = Point(rand(), rand());
            testNodes2[j] = testNodes1[j];
        }
        double d1 = bruteForceFindMinDistance(testNodes1, 0, NodeSize - 1);
        double d2 = findMinDistance(testNodes2, 0, NodeSize - 1);
        EXPECT_DOUBLE_EQ(d1, d2);
    }
}

#endif  // CLOSEST_PAIR_OF_POINTS_TEST_CPP
