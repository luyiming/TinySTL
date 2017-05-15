#ifndef UFSET_HPP
#define UFSET_HPP

#include "Vector.hpp"

namespace TinySTL {

    class UFSet {
    public:
        using size_type = std::size_t;

    public:
        explicit UFSet(size_type n) {
            parent.assign(n, -1);
        }

        int Find(int x) const {
            while (parent[x] >= 0) {
                x = parent[x];
            }
            return x;
        }

        bool inSame(int x1, int x2) const {
            return Find(x1) == Find(x2);
        }

        void Union(int x1, int x2) {
            int root1 = Find(x1);
            int root2 = Find(x2);
            if (root1 == root2) {
                return;
            }
            if (parent[root1] < parent[root2]) {
                parent[root1] += parent[root2];
                parent[root2] = root1;
            }
            else {
                parent[root2] += parent[root1];
                parent[root1] = root2;
            }
        }

        size_type size() const { return parent.size(); }
 
    private:
        TinySTL::vector<int> parent;
    };

} // namespace TinySTL 


#endif // UFSET_HPP