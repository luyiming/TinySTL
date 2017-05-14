#ifndef MEMORY_HPP
#define MEMORY_HPP

#include <cstdlib>

namespace TinySTL {

    template <typename T>
    class allocator {
    public:
        using value_type        = T;
        using reference         = value_type&;
        using const_reference   = const value_type&;
        using pointer           = value_type*;
        using const_pointer     = const value_type*;
        using difference_type   = std::ptrdiff_t;
        using size_type         = std::size_t;
    
    public:
        pointer allocate(size_type n);

        void deallocate(pointer p, size_type n);

        template <typename U, typename... Args>
        void construct(U* p, Args&&... args);

        template <typename U>
        void destroy(U* p);
    };

    template <typename T>
    typename allocator<T>::pointer allocator<T>::allocate(size_type n) {
        // TODO:
        return static_cast<pointer>(malloc(sizeof(T) * n));
    }

    template <typename T>
    void allocator<T>::deallocate(pointer p, size_type n) {
        // TODO:
        if (n == 0) {
            return;
        }
    }
    
    template <typename T>
    template <typename U, typename... Args>
    void allocator<T>::construct(U* p, Args&&... args) {
        // TODO:
    }

    template <typename T>
    template <typename U>
    void allocator<T>::destroy(U* p) {
        // TODO:
    }

}  // namespace TinySTL

#endif  // MEMORY_HPP
