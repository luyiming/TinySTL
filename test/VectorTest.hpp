#include "gtest/gtest.h"

#include "Vector.hpp"

TEST(VectorTest, Misc) {
    TinySTL::vector<int> vec;
    EXPECT_TRUE(vec.empty());
    EXPECT_EQ((size_t)0, vec.size());

    TinySTL::vector<int> vec2(100, 1);
    EXPECT_FALSE(vec2.empty());
    EXPECT_EQ((size_t)100, vec2.size());
    for (size_t i = 0; i < 100; i++)
        vec2.at(i) = (int)i;
    for (size_t i = 0; i < 100; i++) {
        EXPECT_EQ(vec2[i], vec2.at(i));
        EXPECT_EQ((int)i, vec2.at(i));
    }

    TinySTL::vector<int> vec3(vec2);
    EXPECT_FALSE(vec3.empty());
    EXPECT_EQ((size_t)100, vec3.size());
    for (size_t i = 0; i < 100; i++) {
        EXPECT_EQ((int)i, vec3.at(i));
    }

    vec3.clear();
    EXPECT_TRUE(vec3.empty());
    EXPECT_EQ((size_t)0, vec3.size());

    vec2 = vec3;
    EXPECT_TRUE(vec2.empty());
    EXPECT_EQ((size_t)0, vec2.size());
}

TEST(VectorTest, FrontBack) {
    TinySTL::vector<int> vec;
    for (int i = 0; i < 100; i++) {
        vec.push_back(i);
        EXPECT_EQ(0, vec.front());
        EXPECT_EQ(i, vec.back());
    }
    for (int i = 0; i < 100; i++) {
        EXPECT_EQ(i, vec.front());
        EXPECT_EQ(99, vec.back());
        vec.erase(0);
    }
}

TEST(VectorTest, InsertPush) {
    TinySTL::vector<int> vec;

    for (size_t i = 0; i < 100; i++) {
        vec.insert(i, i);
    }
    EXPECT_EQ((size_t)100, vec.size());
    EXPECT_FALSE(vec.empty());
    for (size_t i = 0; i < 100; i++) {
        EXPECT_EQ((int)i, vec.at(i));
        EXPECT_EQ((int)i, vec[i]);
    }

    vec.insert(100, 100, 1024);
    EXPECT_EQ((size_t)200, vec.size());
    EXPECT_FALSE(vec.empty());
    for (size_t i = 100; i < 200; i++) {
        EXPECT_EQ(1024, vec.at(i));
        EXPECT_EQ(1024, vec[i]);
    }

    vec.insert(0, 100, 2048);
    EXPECT_EQ((size_t)300, vec.size());
    EXPECT_FALSE(vec.empty());
    for (size_t i = 0; i < 100; i++) {
        EXPECT_EQ(2048, vec.at(i));
        EXPECT_EQ(2048, vec[i]);
    }

    for (int i = 0; i < 100; i++) {
        vec.push_back(i);
    }
    EXPECT_EQ((size_t)400, vec.size());
    EXPECT_FALSE(vec.empty());
    for (size_t i = 300; i < 400; i++) {
        EXPECT_EQ((int)i - 300, vec.at(i));
        EXPECT_EQ((int)i - 300, vec[i]);
    }
}

TEST(VectorTest, ErasePop) {
    TinySTL::vector<int> vec;

    for (int i = 0; i < 400; i++) {
        vec.push_back(i);
    }

    EXPECT_EQ((size_t)400, vec.size());
    EXPECT_FALSE(vec.empty());

    for (int i = 0; i < 100; i++) {
        EXPECT_EQ((size_t)400 - i, vec.size());
        EXPECT_EQ(i, vec.front());
        EXPECT_EQ(vec.front(), vec.at(0));
        vec.erase(0);
    }

    vec.clear();
    for (int i = 0; i < 200; i++) {
        vec.push_back(i);
    }
    for (int i = 200 - 1; i > 100 - 1; i--) {
        EXPECT_EQ(i, vec.back());
        EXPECT_EQ(vec.back(), vec.at(vec.size() - 1));
        vec.pop_back();
        EXPECT_EQ((size_t)i, vec.size());
    }

    vec.erase(50, vec.size());
    EXPECT_EQ((size_t)50, vec.size());
    for (size_t i = 0; i < 50; i++) {
        EXPECT_EQ((int)i, vec.at(i));
    }
}
