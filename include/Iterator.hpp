#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include <cstdlib>

namespace TinySTL {
namespace Iterator {

    struct input_iterator_tag {};
    struct output_iterator_tag {};
    struct forward_iterator_tag {};
    struct bidirectional_iterator_tag {};
    struct random_access_iterator_tag {};

    template <class Category,                    // Iterator::iterator_category
              class T,                           // Iterator::value_type
              class Distance  = std::ptrdiff_t,  // Iterator::difference_type
              class Pointer   = T *,             // Iterator::pointer
              class Reference = T &              // Iterator::reference
              >
    class iterator {
       public:
        using iterator_category = Category;
        using value_type        = T;
        using difference_type   = Distance;
        using pointer           = Pointer;
        using reference         = Reference;
    };

}  // namespace Iterator
}  // namespace TinySTL

#endif  // ITERATOR_HPP
