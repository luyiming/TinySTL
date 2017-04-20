#include "GraphAdj.hpp"

#include <iostream>

using namespace std;

int main() {
    GraphAdj<int, int> g;
    if (g.isEmpty()) {
        cout << "empty graph" << endl;
    } else {
        cout << "error" << endl;
    }
    return 0;
}
