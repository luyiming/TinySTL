#include "UFSet.hpp"
#include "gtest/gtest.h"

TEST(UFSetTest, test1) {
    TinySTL::UFSet sets(10);

    EXPECT_FALSE(sets.inSame(0, 1));
    EXPECT_FALSE(sets.inSame(2, 3));
    EXPECT_FALSE(sets.inSame(0, 2));

    sets.Union(0, 1);
    sets.Union(2, 3);
    EXPECT_TRUE(sets.inSame(0, 1));
    EXPECT_TRUE(sets.inSame(2, 3));
    EXPECT_FALSE(sets.inSame(0, 2));

    sets.Union(0, 2);
    EXPECT_TRUE(sets.inSame(0, 2));
}


