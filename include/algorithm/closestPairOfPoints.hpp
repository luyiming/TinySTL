#ifndef CLOSEST_PAIR_OF_POINTS_HPP
#define CLOSEST_PAIR_OF_POINTS_HPP

// A divide-and-conquer program to find the smallest distance from a
// given set of points in the plane.
// O(nlogn)

#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <limits>
#include <vector>

using namespace std;

struct Point {
    double x, y;
    Point() : x(0), y(0) {}
    Point(int x, int y) : x(x), y(y) {}
    Point(const Point &rhs) : x(rhs.x), y(rhs.y) {}
    void flip() { swap(x, y); }
};

bool operator<(const Point &lhs, const Point &rhs) { return lhs.x < rhs.x; }

double nodeDistance(Point n1, Point n2) {
    return sqrt((n1.x - n2.x) * (n1.x - n2.x) + (n1.y - n2.y) * (n1.y - n2.y));
}

double bruteForceFindMinDistance(Point *Nodes, int low, int high) {
    double minDistance = std::numeric_limits<double>::max();
    for (int i = low; i <= high; i++) {
        for (int j = i + 1; j <= high; j++) {
            double d = nodeDistance(Nodes[i], Nodes[j]);
            if (d < minDistance) {
                minDistance = d;
            }
        }
    }
    return minDistance;
}

double findMinDistance(Point *Nodes, int low, int high) {
    int nodesSize = high - low + 1;
    if (nodesSize <= 4) {
        return bruteForceFindMinDistance(Nodes, low, high);
    }

    sort(Nodes + low, Nodes + high + 1);

    int xMedianIndex = (low + high) / 2;
    double xMedian = Nodes[xMedianIndex].x;

    if (Nodes[low].x == Nodes[high].x) {
        // same point
        if (Nodes[low].y == Nodes[high].y) {
            return 0.0;
        } else {
            // all points are on the same vertical line, so flip them
            for (int i = low; i <= high; i++) {
                Nodes[i].flip();
            }
            double ret = findMinDistance(Nodes, low, high);
            for (int i = low; i <= high; i++) {
                Nodes[i].flip();
            }
            return ret;
        }
    }

    // ensure both parts have nodes
    if (xMedianIndex + 1 > high) {
        xMedianIndex--;
    }
    assert(xMedianIndex >= low && xMedianIndex < high);

    double d1 = findMinDistance(Nodes, low, xMedianIndex);
    double d2 = findMinDistance(Nodes, xMedianIndex + 1, high);
    double d = d1 < d2 ? d1 : d2;

    int leftCandidatesIndex = xMedianIndex + 1,
        rightCandidatesIndex = xMedianIndex;

    do {
        leftCandidatesIndex--;
    } while (leftCandidatesIndex > low &&
             Nodes[leftCandidatesIndex].x >= xMedian - d);
    assert(leftCandidatesIndex >= low);

    do {
        rightCandidatesIndex++;
    } while (rightCandidatesIndex < high &&
             Nodes[rightCandidatesIndex].x <= xMedian + d);
    assert(rightCandidatesIndex <= high);

    for (int i = leftCandidatesIndex; i <= xMedianIndex; i++) {
        for (int j = xMedianIndex + 1; j <= rightCandidatesIndex; j++) {
            double currentD = nodeDistance(Nodes[i], Nodes[j]);
            if (currentD < d) {
                d = currentD;
            }
        }
    }

    return d;
}

#endif  // CLOSEST_PAIR_OF_POINTS_HPP
