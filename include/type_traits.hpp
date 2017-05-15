#ifndef TYPE_TRAITS_HPP
#define TYPE_TRAITS_HPP

namespace TinySTL {

    // ALIAS TEMPLATE void_t
    template<typename... Types>
    using void_t = void;

    template <bool, typename T = void>
    struct enable_if
    {};

    template <typename T>
    struct enable_if<true, T> {
        using type = T;
    };

    template <bool B, typename T = void>
    using enable_if_t = typename enable_if<B, T>::type;

    template <typename T>
    struct is_integral {
        static constexpr bool value = false;
    };

    template <>
    struct is_integral<int> {
        static constexpr bool value = true;
    };

    template <typename T>
    struct is_pointer {
        static constexpr bool value = false;
    };

    template <typename T>
    struct is_pointer<T*> {
        static constexpr bool value = true;
    };

    template <typename T>
    struct is_pointer<const T*> {
        static constexpr bool value = true;
    };

}  // namespace TinySTL

#endif  // TYPE_TRAITS_HPP
