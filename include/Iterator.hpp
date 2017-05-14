#ifndef ITERATOR_HPP
#define ITERATOR_HPP

namespace TinySTL {
    namespace Iterator {

        struct input_iterator_tag {};
        struct output_iterator_tag {};
        struct forward_iterator_tag {};
        struct bidirectional_iterator_tag {};
        struct random_access_iterator_tag {};

        template <typename Category,            // iterator::iterator_category
            typename T,                         // iterator::value_type
            typename Distance = std::ptrdiff_t, // iterator::difference_type
            typename Pointer = T *,             // iterator::pointer
            typename Reference = T &            // iterator::reference
        >
        struct iterator {
        public:
            using iterator_category = Category;
            using value_type        = T;
            using difference_type   = Distance;
            using pointer           = Pointer;
            using reference         = Reference;
        };

        // ALIAS TEMPLATE void_t
        template<typename... Types>
        using void_t = void;
     
        // TEMPLATE CLASS iterator_traits
        template<typename, typename = void>
        struct iterator_traits_base
        {	// empty for non-iterators
        };

        template<typename Iter>
        struct iterator_traits_base<Iter, void_t<
            typename Iter::iterator_category,
            typename Iter::value_type,
            typename Iter::difference_type,
            typename Iter::pointer,
            typename Iter::reference
        > >
        {	// defined if Iter::* types exist
            using iterator_category = typename Iter::iterator_category;
            using value_type        = typename Iter::value_type;
            using difference_type   = typename Iter::difference_type;
            using pointer           = typename Iter::pointer;
            using reference         = typename Iter::reference;
        };

        template<typename Iter>
        struct iterator_traits
            : iterator_traits_base<Iter>
        {	// get traits from iterator Iter, if possible
        };

        template<typename T>
        struct iterator_traits<T *>
        {	// get traits from pointer
            using iterator_category = random_access_iterator_tag;
            using value_type        = T;
            using difference_type   = ptrdiff_t;
            using pointer           = T *;
            using reference         = T&;
        };

        template<typename T>
        struct iterator_traits<const T *>
        {	// get traits from const pointer
            using iterator_category = random_access_iterator_tag;
            using value_type        = T;
            using difference_type   = ptrdiff_t;
            using pointer           = const T *;
            using reference         = const T&;
        };
        
    }  // namespace Iterator
}  // namespace TinySTL

#endif  // ITERATOR_HPP
