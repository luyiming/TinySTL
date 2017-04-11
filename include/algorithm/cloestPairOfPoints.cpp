// A divide and conquer program in C++ to find the smallest distance from a
// given set of points.
// O(nlogn)

#ifndef CLOSEDPAIROFPOINTS_CPP
#define CLOSEDPAIROFPOINTS_CPP

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

struct Node {
    double x, y;
    Node(int x, int y) : x(x), y(y) {}
    Node() : x(0), y(0) {}
    Node(const Node &rhs) {
        x = rhs.x;
        y = rhs.y;
    }
    void flip() { swap(x, y); }
};
bool operator<(const Node &lhs, const Node &rhs) { return lhs.x < rhs.x; }

double nodeDistance(Node n1, Node n2) {
    return sqrt((n1.x - n2.x) * (n1.x - n2.x) + (n1.y - n2.y) * (n1.y - n2.y));
}

double findMinDistance(Node *Nodes, int low, int high) {
    int nodesSize = high - low + 1;
    if (nodesSize <= 1) {
        return std::numeric_limits<double>::max();
    }
    if (nodesSize == 2) {
        return nodeDistance(Nodes[low], Nodes[high]);
    }

    sort(Nodes + low, Nodes + high + 1);

    int xMedianIndex = (low + high) / 2;
    int xMedian = Nodes[xMedianIndex].x;

    if (Nodes[low].x == Nodes[high].x) {
        // same point
        if (Nodes[low].y == Nodes[high].y) {
            return 0.0;
        }
        // flip
        for (int i = low; i <= high; i++) {
            Nodes[i].flip();
        }
        double ret = findMinDistance(Nodes, low, high);
        for (int i = low; i <= high; i++) {
            Nodes[i].flip();
        }
        return ret;
    }

    // ensure both parts have nodes
    if (xMedianIndex + 1 > high) {
        xMedianIndex--;
    }
    assert(xMedianIndex >= low && xMedianIndex < high);

    double d1 = findMinDistance(Nodes, low, xMedianIndex);
    double d2 = findMinDistance(Nodes, xMedianIndex + 1, high);
    double d = d1 < d2 ? d1 : d2;

    int leftCandidatesIndex = xMedianIndex,
        rightCandidatesIndex = xMedianIndex + 1;
    while (leftCandidatesIndex >= low) {
        if ((double)Nodes[leftCandidatesIndex].x >= (double)xMedian - d) {
            leftCandidatesIndex--;
        } else {
            break;
        }
    }
    leftCandidatesIndex--;
    if (leftCandidatesIndex < low) {
        leftCandidatesIndex = low;
    }
    while (rightCandidatesIndex <= high) {
        if ((double)Nodes[rightCandidatesIndex].x <= (double)xMedian + d) {
            rightCandidatesIndex++;
        } else {
            break;
        }
    }
    rightCandidatesIndex++;
    if (rightCandidatesIndex > high) {
        rightCandidatesIndex = high;
    }
    //  cout << "xMedianIndex: " << xMedianIndex << endl;
    //  cout << "leftCandidatesIndex: " << leftCandidatesIndex << endl;
    //  cout << "rightCandidatesIndex: " << rightCandidatesIndex << endl;

    /*
      for (int i = low; i < leftCandidatesIndex; i++) {
        if ((double)Nodes[i].x >= (double)xMedian - d) {
          cout << "1.d: " << d << endl;
          cout << "xMedian: " << xMedian << endl;
          cout << "xMedianIndex: " << xMedianIndex << endl;
          cout << "low: " << low << endl;
          cout << "high: " << high << endl;
          cout << "leftCandidatesIndex: " << leftCandidatesIndex << endl;
          cout << "rightCandidatesIndex: " << rightCandidatesIndex << endl;
          for (int j = low; j <= high; j++) {
            cout << Nodes[j].x << " ";
          }
          cout << endl;
          for (int j = low; j <= high; j++) {
            cout << Nodes[j].y << " ";
          }
          cout << endl;
          assert(0);
        }
      }
      for (int i = rightCandidatesIndex + 1; i <= high; i++) {
        if ((double)Nodes[i].x <= (double)xMedian + d) {
          cout << "2.d: " << d << endl;
          cout << "xMedian: " << xMedian << endl;
          cout << "xMedianIndex: " << xMedianIndex << endl;
          cout << "low: " << low << endl;
          cout << "high: " << high << endl;
          cout << "leftCandidatesIndex: " << leftCandidatesIndex << endl;
          cout << "rightCandidatesIndex: " << rightCandidatesIndex << endl;
          for (int j = low; j <= high; j++) {
            cout << Nodes[j].x << " ";
          }
          cout << endl;
          for (int j = low; j <= high; j++) {
            cout << Nodes[j].y << " ";
          }
          cout << endl;
          assert(0);
        }
      }
    */
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

double bruteForceMinDistance(Node *Nodes, int n) {
    double minDistance = std::numeric_limits<double>::max();
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            double currentD = nodeDistance(Nodes[i], Nodes[j]);
            if (currentD < minDistance) {
                minDistance = currentD;
            }
        }
    }
    return minDistance;
}

int main() {
    const int NodeSize = 1000;
    const int TESTNUM = 100;
    const double EPSILON = 1.0e-5;
    Node *testNodes1 = new Node[NodeSize];
    Node *testNodes2 = new Node[NodeSize];
    for (int i = 0; i < TESTNUM; i++) {
        for (int j = 0; j < NodeSize; j++) {
            testNodes1[j] = Node(rand(), rand());
            testNodes2[j] = testNodes1[j];
        }
        double d1 = bruteForceMinDistance(testNodes1, NodeSize);
        double d2 = findMinDistance(testNodes2, 0, NodeSize - 1);
        if (fabs(d1 - d2) > EPSILON) {
            printf("should be %.6f, you solve %.6f\n", d1, d2);
            for (int k = 0; k < NodeSize; k++) {
                printf("%d,%d ", int(testNodes1[k].x), int(testNodes1[k].y));
            }
            printf("\n");
            for (int k = 0; k < NodeSize; k++) {
                printf("%d,%d ", int(testNodes2[k].x), int(testNodes2[k].y));
            }
            printf("\n");
            printf("\n");
            return 1;
        }
    }

    testNodes1[0] = Node(1, 1);
    testNodes1[1] = Node(1, 1);
    assert(fabs(findMinDistance(testNodes1, 0, 1) - 0.0) < EPSILON);

    testNodes1[0] = Node(0, 1);
    testNodes1[1] = Node(0, 2);
    testNodes1[2] = Node(0, 4);
    assert(fabs(findMinDistance(testNodes1, 0, 2) - 1.0) < EPSILON);

    printf("test succeed\n");
    return 0;
}

#endif  // CLOSEDPAIROFPOINTS_CPP
