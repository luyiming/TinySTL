#ifndef MEMORY_HPP
#define MEMORY_HPP

#include <cstdlib>
#include <limits>
#include <type_traits>
#include "Iterator.hpp"

namespace TinySTL {

    template <typename T>
    class allocator {
    public: // type definitions
        using value_type        = T;
        using reference         = value_type&;
        using const_reference   = const value_type&;
        using pointer           = value_type*;
        using const_pointer     = const value_type*;
        using difference_type   = std::ptrdiff_t;
        using size_type         = std::size_t;

        // rebind allocator to type U
        template <typename U> struct rebind {
            typedef allocator<U> other;
        };

    public:
        // nothing to do because the allocator has no state
        allocator() noexcept { }
        allocator(const allocator& alloc) noexcept { }
        template <typename U>
        allocator(const allocator<U>& alloc) noexcept { }
        ~allocator() { }

              pointer address(reference x) const noexcept       { return &x; }
        const_pointer address(const_reference x) const noexcept { return &x; }

        size_type max_size() const noexcept {
            return std::numeric_limits<std::size_t>::max() / sizeof(value_type);
        }

        pointer allocate(size_type num, allocator<void>::const_pointer hint = 0) {
        //return static_cast<pointer>(malloc(sizeof(T) * n));
            pointer ret = static_cast<pointer>(::operator new(num * sizeof(T)));
            return ret;
        }

        template <typename U, typename... Args>
        void construct(U* p, Args&&... args) {
            // placement new
            new (static_cast<void*>(p))T(std::forward<Args>(args)...)
        }

        void deallocate(pointer p, size_type n) {
            ::operator delete((void*)p);
        }

        template <typename U>
        void destroy(U* p) {
            static_cast<const_pointer>(p)->~T();
        }
    };

    template <> class allocator<void> {
    public:
        typedef void* pointer;
        typedef const void* const_pointer;
        typedef void value_type;
        template <typename U> struct rebind { typedef allocator<U> other; };
    };

    template<typename InputIterator, typename ForwardIterator>
    ForwardIterator uninitialized_copy(InputIterator first, InputIterator last,
        ForwardIterator result)
    {
        for (; first != last; ++result, ++first)
            new (static_cast<void*>(&*result))
            typename TinySTL::Iterator::iterator_traits<ForwardIterator>::value_type(*first);
        return result;
    }

    template<typename InputIterator, typename Size, typename ForwardIterator>
    ForwardIterator uninitialized_copy_n(InputIterator first, Size n, ForwardIterator result)
    {
        for (; n > 0; ++result, ++first, --n)
            new (static_cast<void*>(&*result))
            typename TinySTL::Iterator::iterator_traits<ForwardIterator>::value_type(*first);
        return result;
    }

    template < typename ForwardIterator, typename T >
    void uninitialized_fill(ForwardIterator first, ForwardIterator last, const T& x)
    {
        for (; first != last; ++first)
            new (static_cast<void*>(&*first))
            typename TinySTL::Iterator::iterator_traits<ForwardIterator>::value_type(x);
    }

    template < typename ForwardIterator, typename Size, typename T >
    ForwardIterator uninitialized_fill_n(ForwardIterator first, Size n, const T& x)
    {
        for (; n--; ++first)
            new (static_cast<void*>(&*first))
            typename TinySTL::Iterator::iterator_traits<ForwardIterator>::value_type(x);
        return first;
    }


}  // namespace TinySTL

#endif  // MEMORY_HPP
