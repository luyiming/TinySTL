#include "Algorithm.hpp"
#include "Profiler.hpp"

int main() {
    const int NodeSize = 10000;
    const int TESTNUM = 2;
    Point testNodes1[NodeSize], testNodes2[NodeSize];
    for (int i = 0; i < TESTNUM; i++) {
        for (int j = 0; j < NodeSize; j++) {
            testNodes1[j] = Point(rand(), rand());
            testNodes2[j] = testNodes1[j];
        }

        cout << "brute force:\t";
        Profiler::start();
        bruteForceFindMinDistance(testNodes1, 0, NodeSize - 1);
        Profiler::stop();
        Profiler::dumpDuringTime(cout);

        cout << "nlogn:\t\t";
        Profiler::start();
        findMinDistance(testNodes2, 0, NodeSize - 1);
        Profiler::stop();
        Profiler::dumpDuringTime(cout);
    }
    return 0;
}
