#ifndef STACK_HPP
#define STACK_HPP

#include "Vector.hpp"

namespace TinySTL {

    template <typename T, typename Container = TinySTL::vector<T> >
    class stack {
    public:
        using value_type = T;
        using container_type = Container;
        using reference = typename container_type::reference;
        using const_reference = typename container_type::const_reference;
        using size_type = std::size_t;

    public:
        explicit stack(const container_type& ctnr)
            :data(ctnr)
        { }

        explicit stack(container_type&& ctnr = container_type())
            :data(ctnr)
        { }
        
        bool empty() const { return data.empty(); }

        size_type size() const { return data.size(); }

              value_type& top()       { return data.back(); }
        const value_type& top() const { return data.back(); }

        void push(const value_type& val) { data.push_back(val); }
        void push(value_type&& val)      { data.push_back(val); }

        template <class... Args>
        void emplace(Args&&... args) { data.emplace_back(std::forward<Args>(args)...); }

        void pop() { data.pop_back(); }

        void swap(stack& x) noexcept { data.swap(x); }

    private:
        container_type data;
    };

} // namespace TinySTL 


#endif // STACK_HPP