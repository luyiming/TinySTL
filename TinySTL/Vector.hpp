/**
 * @file    Vector.hpp
 * @author  Lu Yiming <luyimingchn@gmail.com>
 * @version 1.0
 * @date    2017-1-4
 */

#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <cstdlib>

namespace TinySTL {
    template <typename T> class vector;
    template <typename T> bool operator == (const vector<T>& lhs, const vector<T>& rhs);
    template <typename T> bool operator != (const vector<T>& lhs, const vector<T>& rhs);
    template <typename T> bool operator <  (const vector<T>& lhs, const vector<T>& rhs);
    template <typename T> bool operator <= (const vector<T>& lhs, const vector<T>& rhs);
    template <typename T> bool operator >  (const vector<T>& lhs, const vector<T>& rhs);
    template <typename T> bool operator >= (const vector<T>& lhs, const vector<T>& rhs);

    template <typename T>
    class vector {
        friend bool operator == <T> (const vector<T>& lhs, const vector<T>& rhs);
        friend bool operator == <T> (const vector<T>& lhs, const vector<T>& rhs);
        friend bool operator != <T> (const vector<T>& lhs, const vector<T>& rhs);
        friend bool operator <  <T> (const vector<T>& lhs, const vector<T>& rhs);
        friend bool operator <= <T> (const vector<T>& lhs, const vector<T>& rhs);
        friend bool operator >  <T> (const vector<T>& lhs, const vector<T>& rhs);
        friend bool operator >= <T> (const vector<T>& lhs, const vector<T>& rhs);
    public:
        using value_type        = T;
        using size_type         = std::size_t;
        using difference_type   = std::ptrdiff_t;
        using reference         = value_type&;
        using const_reference   = const value_type&;
        using pointer           = value_type*;
        using const_pointer     = const value_type*;
        using iterator          = value_type*;
        using const_iterator    = const value_type*;

        vector();
        vector(size_t count, const T& value);
        vector(const vector<T>& rhs);
        ~vector();
        vector<T>& operator = (const vector<T>& rhs);
        T& operator [] (size_t pos);
        const T& operator [] (size_t pos) const;
        T& at(size_t pos);
        const T& at(size_t pos) const;
        T& front();
        const T& front() const;
        T& back();
        const T& back() const;
        bool empty() const;
        size_t size() const;
        size_t capacity() const;
        void clear();
        void insert(size_t pos, const T& value);
        void insert(size_t pos, size_t count, const T& value);
        void erase(size_t pos);
        void erase(size_t first, size_t last);
        void push_back(const T& value);
        void pop_back();
    private:
        T *data;
        size_t currentSize, maxSize;
        const int growthFactor = 2;
        void overflowHandle(size_t minSize = 1);
    };

}

#include "detail/Vector.impl.hpp"

#endif // VECTOR_HPP
