/**
 * @file    Vector.hpp
 * @author  Lu Yiming <luyimingchn@gmail.com>
 * @version 1.0
 * @date    2017-1-4
 */

#ifndef VECTOR_IMPL_H
#define VECTOR_IMPL_H

#include <cstdlib>
#include <cassert>
#include <iostream>

#include "Vector.hpp"

namespace TinySTL {

    template <typename T>
    vector<T>::vector() {
        currentSize = 0;
        maxSize = 1;
        data = new T[maxSize];
    }

    template <typename T>
    vector<T>::vector(size_t count, const T& value) {
        data = new T[count];
        for (size_t i = 0; i < count; ++i)
            data[i] = value;
        currentSize = count;
        maxSize = count;
    }

    template <typename T>
    vector<T>::vector(const vector<T>& rhs) {
        maxSize = rhs.maxSize;
        currentSize = rhs.currentSize;
        data = new T[maxSize];
        for (size_t i = 0; i < currentSize; ++i) {
            data[i] = rhs.data[i];;
        }
    }

    template <typename T>
    vector<T>::~vector() {
        if (data != NULL)
            delete[] data;
    }

    template <typename T>
    void vector<T>::overflowHandle(size_t minSize) {
        maxSize *= growthFactor;
        if (maxSize < minSize) {
            maxSize = minSize;
        }
        T* oldData = data;
        data = new T[maxSize];
        for (size_t i = 0; i < currentSize; i++) {
            data[i] = oldData[i];
        }
        delete[] oldData;
    }

    template <typename T>
    vector<T>& vector<T>::operator = (const vector<T>& rhs) {
        if (&rhs != this) {
            if (data != NULL) {
                delete[] data;
            }
            maxSize = rhs.maxSize;
            currentSize = rhs.currentSize;
            data = new T[maxSize];
            for (size_t i = 0; i < currentSize; ++i) {
                data[i] = rhs.data[i];;
            }
        }
        return *this;
    }

    template <typename T>
    T& vector<T>::at(size_t pos) {
        assert(pos >= 0 && pos < currentSize);
        return data[pos];
    }

    template <typename T>
    const T& vector<T>::at(size_t pos) const {
        assert(pos >= 0 && pos < currentSize);
        return data[pos];
    }

    template <typename T>
    T& vector<T>::operator[] (size_t pos) {
        assert(pos >= 0 && pos < currentSize);
        return data[pos];
    }

    template <typename T>
    const T& vector<T>::operator[] (size_t pos) const {
        assert(pos >= 0 && pos < currentSize);
        return data[pos];
    }

    template <typename T>
    T& vector<T>::front() {
        return data[0];
    }

    template <typename T>
    const T& vector<T>::front() const {
        return data[0];
    }

    template <typename T>
    T& vector<T>::back() {
        if (currentSize == 0)
            return data[0];
        else
            return data[currentSize - 1];
    }

    template <typename T>
    const T& vector<T>::back() const {
        if (currentSize == 0)
            return data[0];
        else
            return data[currentSize - 1];
    }

    template <typename T>
    bool vector<T>::empty() const {
        return 0 == currentSize;
    }

    template <typename T>
    size_t vector<T>::size() const {
        return currentSize;
    }

    template <typename T>
    size_t vector<T>::capacity() const {
        return maxSize;
    }

    template <typename T>
    void vector<T>::clear() {
        currentSize = 0;
    }

    template <typename T>
    void vector<T>::insert(size_t pos, const T& value) {
        insert(pos, 1, value);
    }

    template <typename T>
    void vector<T>::insert(size_t pos, size_t count, const T& value) {
        assert(pos >= 0 && pos <= currentSize);
        if (currentSize + count > maxSize)
            overflowHandle(currentSize + count);
        for (size_t i = currentSize + count - 1; i >= pos + count; --i) {
            data[i] = data[i - count];
        }
        for (size_t i = pos; i < pos + count; ++i) {
            data[i] = value;
        }
        currentSize += count;
    }

    template <typename T>
    void vector<T>::erase(size_t pos) {
        if (currentSize == 0)
            return;
        assert(pos >= 0 && pos < currentSize);
        for (size_t i = pos; i < currentSize - 1; ++i) {
            data[i] = data[i + 1];
        }
        currentSize--;
    }

    template <typename T>
    void vector<T>::erase(size_t first, size_t last) {
        assert(first <= last);
        assert(first >= 0 && first < currentSize);
        assert(last >= 0 && last <= currentSize);
        size_t length = last - first;
        for (size_t i = first; i < currentSize - length; ++i) {
            data[i] = data[i + length];
        }
        currentSize -= length;
    }

    template <typename T>
    void vector<T>::push_back(const T& value) {
        if (currentSize == maxSize)
            overflowHandle();
        data[currentSize++] = value;
    }

    template <typename T>
    void vector<T>::pop_back() {
        if (currentSize == 0)
            return;
        currentSize--;
    }

    template <typename T>
    bool operator == (const vector<T>& lhs, const vector<T>& rhs) {
        if (lhs.currentSize == rhs.currentSize) {
            for (size_t i = 0; i < lhs.currentSize; ++i) {
                if (lhs.data[i] != rhs.data[i])
                    return false;
            }
            return true;
        }
        else
            return false;
    }

    template <typename T>
    bool operator != (const vector<T>& lhs, const vector<T>& rhs) {
        return !(lhs == rhs);
    }

    template <typename T>
    bool operator < (const vector<T>& lhs, const vector<T>& rhs) {
        size_t length = lhs.currentSize < rhs.currentSize ? lhs.currentSize : rhs.currentSize;
        for (size_t i = 0; i < length; ++i) {
            if (lhs.data[i] < rhs.data[i])
                return true;
            else if (lhs.data[i] > rhs.data[i])
                return false;
        }
        return lhs.currentSize < rhs.currentSize;
    }

    template <typename T>
    bool operator <= (const vector<T>& lhs, const vector<T>& rhs) {
        return lhs < rhs || lhs == rhs;
    }

    template <typename T>
    bool operator > (const vector<T>& lhs, const vector<T>& rhs) {
        return !(lhs < rhs || lhs == rhs);
    }

    template <typename T>
    bool operator >= (const vector<T>& lhs, const vector<T>& rhs) {
        return !(lhs < rhs);
    }

} // namespace TinySTL

#endif // VECTOR_IMPL_H
