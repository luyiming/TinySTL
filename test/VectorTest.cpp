#ifndef VECTORTEST_HPP
#define VECTORTEST_HPP

#include <iostream>
#include "Vector.hpp"
#include "gtest/gtest.h"

TEST(VectorTest, Constructor) {
    TinySTL::vector<int> vec1;
    EXPECT_TRUE(vec1.empty());

    TinySTL::vector<int> vec2(100);
    EXPECT_FALSE(vec2.empty());
    EXPECT_EQ((size_t)100, vec2.size());
    for (size_t i = 0; i < 100; i++) {
        EXPECT_EQ(0, vec2.at(i));
    }
    for (size_t i = 0; i < 100; i++) {
        vec2.at(i) = (int)i;
    }
    for (size_t i = 0; i < 100; i++) {
        EXPECT_EQ((int)i, vec2.at(i));
    }

    TinySTL::vector<int> vec3(100, 1);
    for (size_t i = 0; i < 100; i++) {
        EXPECT_EQ(1, vec3.at(i));
    }

    TinySTL::vector<int> vec4(vec3);
    EXPECT_FALSE(vec4.empty());
    EXPECT_EQ((size_t)100, vec4.size());
    for (size_t i = 0; i < 100; i++) {
        EXPECT_EQ(1, vec4.at(i));
    }

    TinySTL::vector<int> vec5(vec4.begin(), vec4.end());
    EXPECT_FALSE(vec5.empty());
    EXPECT_EQ((size_t)100, vec5.size());
    for (size_t i = 0; i < 100; i++) {
        EXPECT_EQ(1, vec5.at(i));
    }

    TinySTL::vector<int> vec6{ 1,2,3,4,5,6,7,8,9,10 };
    EXPECT_FALSE(vec6.empty());
    EXPECT_EQ((size_t)10, vec6.size());
    for (size_t i = 0; i < 10; i++) {
        EXPECT_EQ(int(i + 1), vec6.at(i));
    }

    vec6.clear();
    EXPECT_TRUE(vec6.empty());

    vec6 = vec5;
    EXPECT_FALSE(vec6.empty());
    EXPECT_EQ((size_t)100, vec6.size());
    for (size_t i = 0; i < 100; i++) {
        EXPECT_EQ(1, vec6.at(i));
    }
     
    TinySTL::vector<int> vec7(TinySTL::vector<int>(100, 1));
    EXPECT_FALSE(vec7.empty());
    EXPECT_EQ((size_t)100, vec7.size());
    for (size_t i = 0; i < 100; i++) {
        EXPECT_EQ(1, vec7.at(i));
    }

    TinySTL::vector<TinySTL::vector<int>> vec8(10, vec7);
    EXPECT_FALSE(vec8.empty());
    EXPECT_EQ((size_t)10, vec8.size());
    for (size_t i = 0; i < 10; i++) {
        for (size_t j = 0; j < 100; j++) {
            EXPECT_EQ(1, vec8.at(i).at(j));
        }
    }

    TinySTL::vector<TinySTL::vector<int>> vec9 = vec8;
}

TEST(VectorTest, Resize) {
    TinySTL::vector<int> vec;
    vec.resize(100, 1);
    EXPECT_EQ(100, vec.size());
    for (size_t i = 0; i < 100; i++) {
        EXPECT_EQ(1, vec.at(i));
    }

    vec.resize(10);
    EXPECT_EQ(10, vec.size());

    vec.resize(100, 2);
    EXPECT_EQ(100, vec.size());
    for (size_t i = 10; i < 100; i++) {
        EXPECT_EQ(2, vec.at(i));
    }
}

TEST(VectorTest, Assign) {
    TinySTL::vector<int> vec1;
    vec1.assign(10, 1);
    EXPECT_EQ(vec1.size(), 10);
    for (size_t i = 0; i < 10; i++) {
        EXPECT_EQ(1, vec1.at(i));
    }

    TinySTL::vector<int> vec2(20, 2);
    vec2.assign(vec1.begin(), vec1.end());
    EXPECT_EQ(vec2.size(), 10);
    for (size_t i = 0; i < 10; i++) {
        EXPECT_EQ(1, vec2.at(i));
    }

    TinySTL::vector<int> vec3(20, 2);
    vec3.assign({ 0,1,2,3,4,5,6,7,8,9 });
    EXPECT_EQ(vec3.size(), 10);
    for (size_t i = 0; i < 10; i++) {
        EXPECT_EQ(i, vec3.at(i));
    }
}

TEST(VectorTest, PushAndPop) {
    TinySTL::vector<int> vec;
    for (int i = 0; i < 10; i++) {
        vec.push_back(i);
        EXPECT_EQ(0, vec.front());
        EXPECT_EQ(i, vec.back());
    }
    for (int i = 9; i >= 0; i--) {
        EXPECT_EQ(i, vec.back());
        vec.pop_back();
        EXPECT_EQ(i, vec.size());
    }
    EXPECT_TRUE(vec.empty());
}


TEST(VectorTest, Insert) {
    TinySTL::vector<int> vec;
    for (size_t i = 0; i < 100; i++) {
        vec.insert(vec.begin() + i, i);
    }
    EXPECT_EQ((size_t)100, vec.size());
    EXPECT_FALSE(vec.empty());
    for (size_t i = 0; i < 100; i++) {
        EXPECT_EQ((int)i, vec.at(i));
    }

    vec.insert(vec.begin() + 100, 100, 1024);
    EXPECT_EQ((size_t)200, vec.size());
    for (size_t i = 100; i < 200; i++) {
        EXPECT_EQ(1024, vec.at(i));
    }

    vec.insert(vec.begin(), 100, 2048);
    EXPECT_EQ((size_t)300, vec.size());
    for (size_t i = 0; i < 100; i++) {
        EXPECT_EQ(2048, vec.at(i));
    }
}

TEST(VectorTest, Erase) {
    TinySTL::vector<int> vec;

    for (int i = 0; i < 400; i++) {
        vec.push_back(i);
    }

    for (int i = 0; i < 100; i++) {
        EXPECT_EQ((size_t)400 - i, vec.size());
        EXPECT_EQ(i, vec.front());
        vec.erase(vec.begin());
    }

    vec.clear();
    for (int i = 0; i < 200; i++) {
        vec.push_back(i);
    }
    for (int i = 200 - 1; i > 100 - 1; i--) {
        EXPECT_EQ(i, vec.back());
        vec.pop_back();
        EXPECT_EQ((size_t)i, vec.size());
    }

    vec.erase(vec.begin() + 50, vec.end());
    EXPECT_EQ((size_t)50, vec.size());
    for (size_t i = 0; i < 50; i++) {
        EXPECT_EQ((int)i, vec.at(i));
    }
}

TEST(VectorTest, Swap) {
    TinySTL::vector<int> vec1(10, 1);
    TinySTL::vector<int> vec2(10, 2);
    swap(vec1, vec2);

    for (size_t i = 0; i < 10; i++) {
        EXPECT_EQ(vec1.at(i), 2);
        EXPECT_EQ(vec2.at(i), 1);
    }
}

TEST(VectorTest, Relation) {
    TinySTL::vector<int> vec1;
    TinySTL::vector<int> vec2(10, 1);
    EXPECT_TRUE(vec1 < vec2);

    vec1.assign(vec2.begin(), vec2.end());
    EXPECT_TRUE(vec1 == vec2);
    EXPECT_FALSE(vec1 < vec2);

    vec1.at(1) = 0;
    EXPECT_TRUE(vec1 < vec2);
    EXPECT_TRUE(vec1 != vec2);

    vec1.at(1) = 2;
    EXPECT_TRUE(vec1 > vec2);
    EXPECT_TRUE(vec1 != vec2);

    vec1.assign(5, 1);
    EXPECT_TRUE(vec1 < vec2);
    EXPECT_TRUE(vec1 != vec2);

    vec1.assign(15, 1);
    EXPECT_TRUE(vec1 > vec2);
    EXPECT_TRUE(vec1 != vec2);
}

#endif  // VECTORTEST_HPP
