#include "Stack.hpp"
#include "gtest/gtest.h"

TEST(StackTest, test1) {
    TinySTL::stack<int> st;
    EXPECT_TRUE(st.empty());

    for (int i = 0; i <= 10; i++) {
        EXPECT_EQ(st.size(), i);
        st.push(i);
    }

    for (int i = 10; i >= 0; i--) {
        EXPECT_EQ(st.top(), i);
        st.pop();
    }

    EXPECT_TRUE(st.empty());
}

TEST(StackTest, test2) {
    TinySTL::vector<int> vec = { 1,2,3,4,5 };
    TinySTL::stack<int> st(vec);
    EXPECT_EQ(st.size(), 5);

    for (int i = 5; i > 0; i--) {
        EXPECT_EQ(st.top(), i);
        st.pop();
    }

    EXPECT_TRUE(st.empty());
}

class Item {
public:
    int k;
    Item(int n) :k(n) {}
    bool operator<(const Item& rhs) const { return k > rhs.k; }
};

TEST(StackTest, test3) {
    TinySTL::stack<Item> st;
    EXPECT_TRUE(st.empty());

    for (int i = 0; i <= 10; i++) {
        EXPECT_EQ(st.size(), i);
        st.push(Item(i));
    }

    for (int i = 10; i >= 0; i--) {
        EXPECT_EQ(st.top().k, i);
        st.pop();
    }

    EXPECT_TRUE(st.empty());
}