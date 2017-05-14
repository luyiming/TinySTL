/**
 * @file    Vector.hpp
 * @author  Lu Yiming <luyimingchn@gmail.com>
 * @version 1.0
 * @date    2017-1-4
 */

#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <initializer_list>
#include <memory>
#include <stdexcept>
#include "Iterator.hpp"

namespace TinySTL {

    template <typename T, typename Alloc = std::allocator<T>>
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
        template <class InputIterator, typename = typename TinySTL::Iterator::iterator_traits<InputIterator>::value_type>
        void assign(InputIterator first, InputIterator last);  // range (1)
        void assign(size_type n, const value_type& val);       // fill  (2)
        void assign(std::initializer_list<value_type> il);     // initializer list (3)
        
        void push_back(const value_type& val);
        void push_back(value_type&& val);
        
        void pop_back();
        
        iterator insert(const_iterator position, const value_type& val);                   // single element (1)
        iterator insert(const_iterator position, size_type n, const value_type& val);      // fill (2)
        template <class InputIterator, typename = typename TinySTL::Iterator::iterator_traits<InputIterator>::value_type>
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

#include "detail/Vector.impl.hpp"

#endif  // VECTOR_HPP
