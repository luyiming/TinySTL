#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <initializer_list>
#include <stdexcept>
#include <cassert>
#include "Iterator.hpp"
#include "Memory.hpp"

namespace TinySTL {
    
    template <typename T, typename Alloc = TinySTL::allocator<T>>
    class vector {
       public:
        using value_type      = T;
        using allocator_type  = Alloc;
        using reference       = value_type&;
        using const_reference = const value_type&;
        using pointer         = value_type*;
        using const_pointer   = const value_type*;
        using iterator        = value_type*;
        using const_iterator  = const value_type*;
        // TODO: using reverse_iterator = ??
        // TODO: using const_reverse_iterator = ??
        using difference_type = std::ptrdiff_t;
        using size_type       = std::size_t;

       public:
        // Initialize
        explicit vector(const allocator_type& alloc = allocator_type()); // default (1)

        explicit vector(size_type n);                                    // fill (2)
                 vector(size_type n, const value_type& val,
                        const allocator_type& alloc = allocator_type());

        template <typename InputIterator, typename = typename TinySTL::Iterator::iterator_traits<InputIterator>::value_type>
        vector(InputIterator first, InputIterator last,
               const allocator_type& alloc = allocator_type());  // range (3)

        vector(const vector& x, const allocator_type& alloc = allocator_type()); // copy (4)

        vector(vector&& x, const allocator_type& alloc = allocator_type()); // move (5)

        vector(std::initializer_list<value_type> il,
               const allocator_type& alloc = allocator_type());  // initializer list (6)

        ~vector();

        vector& operator=(const vector& rhs);
        
        // Iterators:
              iterator begin() noexcept       { return dbegin; }
        const_iterator begin() const noexcept { return dbegin; }
              iterator end()   noexcept       { return dend; }
        const_iterator end()   const noexcept { return dend; }
        //       reverse_iterator rbegin() noexcept;
        // const_reverse_iterator rbegin() const noexcept;
        //       reverse_iterator rend() noexcept;
        // const_reverse_iterator rend() const noexcept;
        const_iterator cbegin() const noexcept { return dbegin; }
        const_iterator cend()   const noexcept { return dend; }
        // const_reverse_iterator crbegin() const noexcept;
        // const_reverse_iterator crend() const noexcept;
        
        // Capacity
        size_type size() const noexcept     { return dend - dbegin; }
        size_type max_size() const noexcept { return (~(size_t)0); }
        void resize(size_type n);
        void resize(size_type n, const value_type& val);
        size_type capacity() const noexcept { return endOfStorage - dbegin; }
        bool empty() const noexcept         { return dend == dbegin; }
        void reserve(size_type n);
        void shrink_to_fit();

        // Element access:
              reference operator[] (size_type n)        { return dbegin[n]; }
        const_reference operator[] (size_type n) const  { return dbegin[n]; }
              reference at (size_type n);
        const_reference at (size_type n) const;
              reference front()         { return *dbegin; }
        const_reference front() const   { return *dbegin; }
              reference back()          { return *(dend - 1); }
        const_reference back() const    { return *(dend - 1); }
              pointer   data() noexcept       { return dbegin; }
        const_pointer   data() const noexcept { return dbegin; }

        // Modifiers
        template <typename InputIterator, typename = typename TinySTL::Iterator::iterator_traits<InputIterator>::value_type>
        void assign(InputIterator first, InputIterator last);  // range (1)
        void assign(size_type n, const value_type& val);       // fill  (2)
        void assign(std::initializer_list<value_type> il);     // initializer list (3)
        
        void push_back(const value_type& val);
        void push_back(value_type&& val);
        
        void pop_back();
        
        iterator insert(const_iterator position, const value_type& val);                   // single element (1)
        iterator insert(const_iterator position, size_type n, const value_type& val);      // fill (2)
        template <typename InputIterator, typename = typename TinySTL::Iterator::iterator_traits<InputIterator>::value_type>
        iterator insert(const_iterator position, InputIterator first, InputIterator last); // range (3)
        iterator insert(const_iterator position, value_type&& val);                        // move (4)
        iterator insert(const_iterator position, std::initializer_list<value_type> il);    // initializer list (5)

        iterator erase(const_iterator position);
        iterator erase(const_iterator first, const_iterator last);

        void swap(vector& x);

        void clear();

        template <class... Args>
        iterator emplace(const_iterator position, Args&&... args);

        template <class... Args>
        void emplace_back(Args&&... args);

        // Allocator
        allocator_type get_allocator() const noexcept { return alloc; }

       private:
        void overflowHandle(size_t minSize = 1);

       private:
        // data stored in [dbegin, dend)
        // allocated buffer is [dbegin, endOfStorage)
        // free space is [dend, endOfStorage)
        T *dbegin, *dend, *endOfStorage; // abbrev. data begin, data end
        allocator_type alloc;

    };

    // Non-member function overloads
    template <class T, class Alloc>
    void swap(vector<T, Alloc>& lhs, vector<T, Alloc>& rhs);

    template <typename T, typename Alloc>
    bool operator == (const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs);
    template <typename T, typename Alloc>
    bool operator != (const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs);
    template <typename T, typename Alloc>
    bool operator <  (const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs);
    template <typename T, typename Alloc>
    bool operator <= (const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs);
    template <typename T, typename Alloc>
    bool operator >  (const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs);
    template <typename T, typename Alloc>
    bool operator >= (const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs);

}  // namespace TinySTL


namespace TinySTL {

    template <typename T, typename Alloc>
    vector<T, Alloc>::vector(const allocator_type& alloc_)
        : dbegin(nullptr),
          dend(nullptr),
          endOfStorage(nullptr),
          alloc(alloc_) {
    }

    template <typename T, typename Alloc>
    vector<T, Alloc>::vector(size_type n) {
        alloc  = allocator_type();
        if (n == 0) {
            dbegin = nullptr;
        } else {
            dbegin = alloc.allocate(n);
            TinySTL::uninitialized_fill_n(dbegin, n, value_type());
        }
        dend         = dbegin + n;
        endOfStorage = dend;
    }

    template <typename T, typename Alloc>
    vector<T, Alloc>::vector(size_type n, const value_type& val, const allocator_type& alloc_)
        : alloc(alloc_) {
        if (n == 0) {
            dbegin = nullptr;
        } else {
            dbegin = alloc.allocate(n);
            TinySTL::uninitialized_fill_n(dbegin, n, val);
        }
        dend         = dbegin + n;
        endOfStorage = dend;
    }

    template <typename T, typename Alloc>
    template <typename InputIterator, typename >
    vector<T, Alloc>::vector(InputIterator first, InputIterator last, const allocator_type& alloc_)
        : alloc(alloc_) {
        difference_type n = last - first;
        if (n == 0) {
            dbegin = nullptr;
        } else {
            dbegin = alloc.allocate(n);
            TinySTL::uninitialized_copy(first, last, dbegin);
        }
        dend         = dbegin + n;
        endOfStorage = dend;
    }

    template <typename T, typename Alloc>
    vector<T, Alloc>::vector(const vector& x, const allocator_type& alloc_)
        : alloc(alloc_) {
        difference_type allocSize = x.endOfStorage - x.dbegin;
        if (allocSize == 0) {
            dbegin = nullptr;
        } else {
            dbegin = alloc.allocate(allocSize);
            TinySTL::uninitialized_copy(x.dbegin, x.dend, dbegin);
        }
        dend         = dbegin + (x.dend - x.dbegin);
        endOfStorage = dbegin + allocSize;
    }

    template <typename T, typename Alloc>
    vector<T, Alloc>::vector(vector&& x, const allocator_type& alloc_)
        : alloc(alloc_) {
        dbegin       = x.dbegin;
        dend         = x.dbegin;
        endOfStorage = x.endOfStorage;
        // for save deallocate
        dbegin       = nullptr;
        dend         = nullptr;
        endOfStorage = nullptr;
    }

    template<typename T, typename Alloc>
    inline vector<T, Alloc>::vector(std::initializer_list<value_type> il, const allocator_type & alloc_)
        : alloc(alloc_) {
        size_type allocSize = il.size();
        if (allocSize == 0) {
            dbegin = nullptr;
        } else {
            dbegin = alloc.allocate(allocSize);
            TinySTL::uninitialized_copy(il.begin(), il.end(), dbegin);
        }
        dend         = dbegin + allocSize;
        endOfStorage = dend;
    }

    template <typename T, typename Alloc>
    vector<T, Alloc>::~vector() {
        clear();
    }

    template <typename T, typename Alloc>
    vector<T, Alloc>& vector<T, Alloc>::operator=(const vector& x) {
        if (&x != this) {
            if (dbegin != nullptr) {
                for (T* p = dbegin; p != dend; ++p) {
                    alloc.destroy(p);
                }
                alloc.deallocate(dbegin, dend - dbegin);
            }
            alloc                     = x.alloc;
            difference_type allocSize = x.endOfStorage - x.dbegin;
            if (allocSize > 0) {
                dbegin = alloc.allocate(allocSize);
                TinySTL::uninitialized_copy(x.dbegin, x.dend, dbegin);
            } else {
                dbegin = nullptr;
            }
            dend         = dbegin + (x.dend - x.dbegin);
            endOfStorage = dbegin + allocSize;
        }
        return *this;
    }

    template <typename T, typename Alloc>
    void vector<T, Alloc>::resize(size_type n) {
        size_type currentSize = size();
        size_type maxSize     = capacity();
        if (n <= currentSize) {
            for (T* p = dbegin + n; p != dend; ++p) {
                alloc.destroy(p);
            }
            dend = dbegin + n;
        } else if (n <= maxSize) {
            TinySTL::uninitialized_fill(dend, dbegin + n, value_type());
            dend = dbegin + n;
        } else {
            T* oldBegin = dbegin;
            T* oldEnd   = dend;
            dbegin      = alloc.allocate(n);
            TinySTL::uninitialized_copy_n(oldBegin, currentSize, dbegin);
            TinySTL::uninitialized_fill(dbegin + currentSize, dbegin + n, value_type());
            dend         = dbegin + n;
            endOfStorage = dend;
            for (T* p = oldBegin; p != oldEnd; ++p) {
                alloc.destroy(p);
            }
            alloc.deallocate(oldBegin, maxSize);
        }
    }

    template <typename T, typename Alloc>
    void vector<T, Alloc>::resize(size_type n, const value_type& val) {
        size_type currentSize = size();
        size_type maxSize     = capacity();
        if (n <= currentSize) {
            for (T* p = dbegin + n; p != dend; ++p) {
                alloc.destroy(p);
            }
            dend = dbegin + n;
        } else if (n <= maxSize) {
            TinySTL::uninitialized_fill(dend, dbegin + n, val);
            dend = dbegin + n;
        } else {
            T* oldBegin = dbegin;
            T* oldEnd   = dend;
            dbegin      = alloc.allocate(n);
            TinySTL::uninitialized_copy_n(oldBegin, currentSize, dbegin);
            TinySTL::uninitialized_fill(dbegin + currentSize, dbegin + n, val);
            dend         = dbegin + n;
            endOfStorage = dend;
            for (T* p = oldBegin; p != oldEnd; ++p) {
                alloc.destroy(p);
            }
            alloc.deallocate(oldBegin, maxSize);
        }
    }

    template <typename T, typename Alloc>
    void vector<T, Alloc>::reserve(size_type n) {
        size_type currentSize = size();
        size_type maxSize     = capacity();
        if (n > maxSize) {
            T* oldBegin = dbegin;
            T* oldEnd   = dend;
            dbegin      = alloc.allocate(n);
            if (currentSize > 0) {
                TinySTL::uninitialized_copy_n(oldBegin, currentSize, dbegin);
            }
            dend         = dbegin + currentSize;
            endOfStorage = dbegin + n;
            if (currentSize > 0) {
                for (T* p = oldBegin; p != oldEnd; ++p) {
                    alloc.destroy(p);
                }
                alloc.deallocate(oldBegin, maxSize);
            }
        }
    }

    template <typename T, typename Alloc>
    void vector<T, Alloc>::shrink_to_fit() {
        return;
    }

    template <typename T, typename Alloc>
    typename vector<T, Alloc>::reference vector<T, Alloc>::at(size_type n) {
        if (n >= size()) {
            throw std::out_of_range("index is out of range");
        }
        return dbegin[n];
    }

    template <typename T, typename Alloc>
    typename vector<T, Alloc>::const_reference vector<T, Alloc>::at(size_type n) const {
        if (n >= size()) {
            throw std::out_of_range("index is out of range");
        }
        return dbegin[n];
    }

    template <typename T, typename Alloc>
    template <class InputIterator, typename >
    void vector<T, Alloc>::assign(InputIterator first, InputIterator last) {
        size_type n = last - first;
        if (n > capacity()) {
            overflowHandle(n);
        }
        for (iterator p = dbegin; p != dend; p++) {
            alloc.destroy(p);
        }
        TinySTL::uninitialized_copy(first, last, dbegin);
        dend = dbegin + n;
    }

    template <typename T, typename Alloc>
    void vector<T, Alloc>::assign(size_type n, const value_type& val) {
        if (n > capacity()) {
            overflowHandle(n);
        }
        for (iterator p = dbegin; p != dend; p++) {
            alloc.destroy(p);
        }
        TinySTL::uninitialized_fill_n(dbegin, n, val);
        dend = dbegin + n;
    }

    template <typename T, typename Alloc>
    void vector<T, Alloc>::assign(std::initializer_list<value_type> il) {
        size_type n = il.size();
        if (n > capacity()) {
            overflowHandle(n);
        }
        for (iterator p = dbegin; p != dend; p++) {
            alloc.destroy(p);
        }
        TinySTL::uninitialized_copy(il.begin(), il.end(), dbegin);
        dend = dbegin + n;
    }

    template <typename T, typename Alloc>
    void vector<T, Alloc>::push_back(const value_type& val) {
        if (dend == endOfStorage) {
            overflowHandle();
        }
        *dend = val;
        dend++;
    }

    template <typename T, typename Alloc>
    void vector<T, Alloc>::push_back(value_type&& val) {
        if (dend == endOfStorage) {
            overflowHandle();
        }
        *dend = std::move(val);
        dend++;
    }

    template <typename T, typename Alloc>
    void vector<T, Alloc>::pop_back() {
        if (size() == 0) {
            return;
        }
        dend--;
        alloc.destroy(dend);
    }

    template <typename T, typename Alloc>
    typename vector<T, Alloc>::iterator
    vector<T, Alloc>::insert(const_iterator position, const value_type& val) {
        return insert(position, 1, val);
    }

    template <typename T, typename Alloc>
    typename vector<T, Alloc>::iterator
    vector<T, Alloc>::insert(const_iterator position, size_type n, const value_type& val) {
        size_type currentSize = size();
        size_type maxSize     = capacity();
        size_type pos         = position - begin();
        if (currentSize + n > maxSize) {
            overflowHandle(currentSize + n);
        }
        for (size_type i = currentSize + n - 1; i >= pos + n; --i) {
            dbegin[i] = dbegin[i - n];
        }
        for (size_type i = pos; i < pos + n; ++i) {
            dbegin[i] = val;
        }
        dend += n;
        return dbegin + pos + n - 1;
    }

    template <typename T, typename Alloc>
    template <typename InputIterator, typename >
    typename vector<T, Alloc>::iterator
    vector<T, Alloc>::insert(const_iterator position, InputIterator first, InputIterator last) {
        size_type currentSize = size();
        size_type maxSize     = capacity();
        size_type pos         = position - begin();
        size_type n           = last - first;
        if (currentSize + n > maxSize) {
            overflowHandle(currentSize + n);
        }
        for (int i = currentSize + n - 1; i >= pos + n; --i) {
            dbegin[i] = dbegin[i - n];
        }
        TinySTL::uninitialized_copy(first, last, dbegin + pos);
        dend += n;
        return dbegin + pos + n - 1;
    }

    template <typename T, typename Alloc>
    typename vector<T, Alloc>::iterator
    vector<T, Alloc>::insert(const_iterator position, value_type&& val) {
        size_type currentSize = size();
        size_type maxSize     = capacity();
        size_type pos         = position - begin();
        if (currentSize + 1 > maxSize) {
            overflowHandle(currentSize + 1);
        }
        for (int i = currentSize; i >= pos + 1; --i) {
            dbegin[i] = dbegin[i - 1];
        }
        dbegin[pos] = std::move(val);
        dend++;
        return dbegin + pos;
    }

    template <typename T, typename Alloc>
    typename vector<T, Alloc>::iterator
    vector<T, Alloc>::insert(const_iterator position, std::initializer_list<value_type> il) {
        size_type currentSize = size();
        size_type maxSize     = capacity();
        size_type pos         = position - begin();
        size_type n           = il.size();
        if (currentSize + n > maxSize) {
            overflowHandle(currentSize + n);
        }
        for (int i = currentSize + n - 1; i >= pos + n; --i) {
            dbegin[i] = dbegin[i - n];
        }
        TinySTL::uninitialized_copy(il.begin(), il.end(), dbegin + pos);
        dend += n;
        return dbegin + pos + n - 1;
    }

    template <typename T, typename Alloc>
    typename vector<T, Alloc>::iterator
    vector<T, Alloc>::erase(const_iterator position) {
        size_type currentSize = size();
        size_type pos         = position - begin();
        if (currentSize == 0) {
            return nullptr;
        }
        alloc.destroy(dbegin + pos);
        for (size_type i = pos; i < currentSize - 1; ++i) {
            dbegin[i] = dbegin[i + 1];
        }
        dend--;
        return dbegin + pos;
    }

    template <typename T, typename Alloc>
    typename vector<T, Alloc>::iterator
    vector<T, Alloc>::erase(const_iterator first, const_iterator last) {
        assert(first >= dbegin);
        assert(first <= last);
        assert(last <= dend);
        if (first == last) {
            return dbegin + (first - dbegin);
        }
        size_type length = last - first;
        for (const_iterator p = first; p != last; p++) {
            alloc.destroy(p);
        }
        for (int i = first - dbegin, j = last - dbegin; j < dend - dbegin; ++i, ++j) {
            dbegin[i] = dbegin[j];
        }
        dend -= length;
        return dbegin + (first - dbegin);
    }

    template <typename T, typename Alloc>
    void vector<T, Alloc>::swap(vector& x) {
        std::swap(alloc, x.alloc);
        std::swap(dbegin, x.dbegin);
        std::swap(dend, x.dend);
        std::swap(endOfStorage, x.endOfStorage);
    }

    template <typename T, typename Alloc>
    void vector<T, Alloc>::clear() {
        if (dbegin != nullptr) {
            for (T* p = dbegin; p != dend; ++p) {
                alloc.destroy(p);
            }
            alloc.deallocate(dbegin, dend - dbegin);
        }
        dbegin = dend = endOfStorage = nullptr;
    }

    template <typename T, typename Alloc>
    template <class... Args>
    typename vector<T, Alloc>::iterator
    vector<T, Alloc>::emplace(const_iterator position, Args&&... args) {
        size_type currentSize = size();
        size_type maxSize     = capacity();
        size_type pos         = position - begin();
        if (currentSize + 1 > maxSize) {
            overflowHandle(currentSize + 1);
        }
        for (int i = currentSize; i >= pos + 1; --i) {
            dbegin[i] = dbegin[i - 1];
        }
        alloc.construct(dbegin + pos, std::forward<Args>(args)...);
        dend++;
        return dbegin + pos;
    }

    template <typename T, typename Alloc>
    template <class... Args>
    void vector<T, Alloc>::emplace_back(Args&&... args) {
        if (dend == endOfStorage) {
            overflowHandle();
        }
        alloc.construct(dend, std::forward<Args>(args)...);
        dend++;
    }

    template <typename T, typename Alloc>
    void vector<T, Alloc>::overflowHandle(size_t minSize) {
        size_type currentSize = size();
        size_type allocSize   = 2 * currentSize;
        if (allocSize == 0) {
            allocSize = 1;
        }
        if (allocSize < minSize) {
            allocSize = minSize;
        }
        // std::cout << "alloc size: " << allocSize << std::endl;
        reserve(allocSize);
    }

    template <class T, class Alloc>
    void swap(vector<T, Alloc>& lhs, vector<T, Alloc>& rhs) {
        lhs.swap(rhs);
    }

    template <typename T, typename Alloc>
    bool operator==(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) {
        if (lhs.size() == rhs.size()) {
            for (size_t i = 0; i < lhs.size(); ++i) {
                if (lhs[i] != rhs[i])
                    return false;
            }
            return true;
        } else
            return false;
    }

    template <typename T, typename Alloc>
    bool operator!=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) {
        return !(lhs == rhs);
    }

    template <typename T, typename Alloc>
    bool operator<(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) {
        size_t length = lhs.size() < rhs.size() ? lhs.size() : rhs.size();
        for (size_t i = 0; i < length; ++i) {
            if (lhs[i] < rhs[i])
                return true;
            else if (lhs[i] > rhs[i])
                return false;
        }
        return lhs.size() < rhs.size();
    }

    template <typename T, typename Alloc>
    bool operator<=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) {
        return lhs < rhs || lhs == rhs;
    }

    template <typename T, typename Alloc>
    bool operator>(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) {
        return !(lhs < rhs || lhs == rhs);
    }

    template <typename T, typename Alloc>
    bool operator>=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) {
        return !(lhs < rhs);
    }

}  // namespace TinySTL

#endif  // VECTOR_HPP
