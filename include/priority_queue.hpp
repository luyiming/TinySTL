#ifndef PRIORITY_QUEUE_HPP
#define PRIORITY_QUEUE_HPP

#include "Vector.hpp"
#include "Iterator.hpp"

namespace TinySTL {

    template <typename T, typename Container = TinySTL::vector<T>, typename Compare = std::less<typename Container::value_type>>
    class priority_queue {
    public:
        using value_type = T;
        using container_type = Container;
        using reference = typename container_type::reference;
        using const_reference = typename container_type::const_reference;
        using size_type = std::size_t;

    public:
        priority_queue() = default;

        template <typename InputIterator>
        priority_queue(InputIterator first, InputIterator last, const Compare& comp = Compare()) 
            : compare(comp), heap()
        {
            heap.assign(first, last);
            make_heap();
        }

        bool empty() const { return heap.empty(); }

        size_type size() const { return heap.size(); }

        const_reference top() const { return heap[0]; }

        void pop() {
            heap[0] = heap[heap.size() - 1];
            heap.pop_back();
            siftDown(0, heap.size() - 1);
        }

        void push(const value_type& val) {
            heap.push_back(val);
            siftUp(heap.size() - 1);
        }

        void push(value_type&& val) {
            heap.push_back(val);
            siftUp(heap.size() - 1);
        }

        template <typename... Args> 
        void emplace(Args&&... args) {
            heap.emplace_back(std::forward<Args>(args)...);
            siftUp(heap.size() - 1);
        }

        void clear() { heap.clear(); }

        void increaseKey(const T& k, const T& newKey) {
            int i;
            for (i = 0; i < heap.size(); i++) {
                if (heap[i] == k) {
                    heap[i] = newKey;
                    break;
                }
            }
            siftDown(i, heap.size() - 1);
        }

        void decreaseKey(const T& k, const T& newKey) {
            int i;
            for (i = 0; i < heap.size(); i++) {
                if (heap[i] == k) {
                    heap[i] = newKey;
                    break;
                }
            }
            siftUp(i);
        }

        const_reference find(const T& k) {
            int i;
            for (i = 0; i < heap.size(); i++) {
                if (heap[i] == k) {
                    return heap[i];
                }
            }
            return T();
        }

        void swap(priority_queue& x) noexcept {
            heap.swap(x);
        }

    private:
        void siftDown(size_type start, size_type end) {
            size_type p = start;
            while (p < end) {
                size_type k = 2 * p + 1;
                if (k >= heap.size())
                    break;
                if (k + 1 < heap.size() && compare(heap[k + 1], heap[k]))
                    k++;
                if (compare(heap[p], heap[k]))
                    break;
                std::swap(heap[k], heap[p]);
                p = k;
            }
        }

        void siftUp(size_type start) {
            int p = start;
            while (p > 0) {
                int k = (p - 1) / 2;
                if (compare(heap[k], heap[p]))
                    break;
                std::swap(heap[k], heap[p]);
                p = k;
            }
        }

        void make_heap() {
            int start = heap.size() / 2;
            while (start >= 0) {
                siftDown(start, heap.size() - 1);
                start--;
            }
        }

    private:
        Compare compare;
        container_type heap; // min heap
    };


} // namespace TinySTL 


#endif // PRIORITY_QUEUE_HPP