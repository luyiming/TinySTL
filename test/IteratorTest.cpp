#include <algorithm>
#include <iostream>
#include "Iterator.hpp"
#include "gtest/gtest.h"

using namespace TinySTL::Iterator;

template <typename T>
class test_iterator : public iterator<random_access_iterator_tag, T> {
   public:
    using pointer = typename iterator<random_access_iterator_tag, T>::pointer;
    using reference =
        typename iterator<random_access_iterator_tag, T>::reference;
    using difference_type =
        typename iterator<random_access_iterator_tag, T>::difference_type;

   private:
    using iterator = test_iterator<T>;
    pointer pos;

   public:
    test_iterator() : pos(nullptr) {}
    test_iterator(pointer v) : pos(v) {}
    ~test_iterator() {}

    iterator operator++(int) { return pos++; }
    iterator& operator++() {
        ++pos;
        return *this;
    }
    iterator operator--(int) { return pos--; }
    iterator& operator--() {
        --pos;
        return *this;
    }
    reference operator*() const { return *pos; }
    pointer operator->() const { return pos; }

    iterator operator+(difference_type v) const { return pos + v; }
    iterator operator-(difference_type v) const { return pos - v; }
    difference_type operator-(const iterator& rhs) const {
        return pos - rhs.pos;
    }
    bool operator==(const iterator& rhs) const { return pos == rhs.pos; }
    bool operator<(const iterator& rhs) const { return pos < rhs.pos; }
    bool operator!=(const iterator& rhs) const { return pos != rhs.pos; }
};

class A {
    int a[10] = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};

   public:
    using iterator       = test_iterator<int>;
    using const_iterator = test_iterator<const int>;

   public:
    iterator begin() { return iterator(a); }
    iterator end() { return iterator(a + 10); }
    void func() { std::cout << "A::func()" << std::endl; }

   public:
    friend std::ostream& operator<<(std::ostream& os, const A& rhs);
};

std::ostream& operator<<(std::ostream& os, const A& rhs) {
    os << rhs.a;
    return os;
}

TEST(IteratorTest, Test1) {
    A a;
    for (auto it = a.begin(); it != a.end(); it++) {
        std::cout << *it << std::endl;
    }
    test_iterator<A> it2(&a);
    it2->func();
}
