#include "GraphAdj.hpp"

#include <iostream>

using namespace std;

template <typename T, typename E>
void DFS_aux(Graph<T, E> &graph, int vertex, int *color) {
    if (color[vertex] == 0) {
        printf("%d\n", graph.getValue(vertex));
        color[vertex] = 1;
        int v = graph.getFirstNeighbour(vertex);
        while (v != -1) {
            DFS_aux(graph, v, color);
            v = graph.getNextNeighbour(vertex, v);
        }
    }
}

template <typename T, typename E>
void DFS(Graph<T, E> &graph) {
    int numVertices = graph.numOfVertices();
    int *color = new int[numVertices];
    for (int i = 0; i < numVertices; i++) {
        color[i] = 0;
    }
    DFS_aux(graph, 0, color);
    delete[] color;
}

int main() {
    GraphAdj<int> g;
    g.insertVertex(0);
    g.insertVertex(1);
    g.insertVertex(2);
    g.insertVertex(3);
    g.insertVertex(4);
    g.insertVertex(5);

    g.insertEdge(0, 1);
    g.insertEdge(1, 2);
    g.insertEdge(2, 3);
    g.insertEdge(2, 4);
    g.insertEdge(1, 5);
    g.print();

    DFS(g);
    return 0;
}
TEST(testConstructor) {
    GraphAdj<int, double> *g1 = new GraphAdj<int, double>();
    assert(g1->isEmpty());
    assert(g1->numOfEdges() == 0);
    assert(g1->numOfVertices() == 0);

    g1->insertVertex(0);
    g1->insertVertex(1);
    g1->insertVertex(2);
    g1->insertVertex(3);
    g1->insertVertex(4);
    g1->insertEdge(0, 1);
    g1->insertEdge(0, 2);
    g1->insertEdge(2, 3);
    g1->insertEdge(2, 4);
    GraphAdj<int, double> *g2 = new GraphAdj<int, double>(*g1);
    GraphAdj<int, double> g3;
    g3 = *g2;
    GraphAdj<int, double> g4(g3);

    delete g2;
    delete g1;
}
TEST(testInsertAndRemove) {
    GraphAdj<int, double> g;
    for (int i = 1; i <= 100; i++) {
        g.insertVertex(i);
        assert(g.numOfVertices() == i);
    }
    int cnt = 0;
    for (int i = 0; i < 100; i++) {
        for (int j = i + 1; j < 100; j++) {
            g.insertEdge(i, j);
            assert(g.numOfEdges() == ++cnt);
        }
    }
    GraphAdj<int, double> g2(g);
    assert(g2.numOfVertices() == 100);
    assert(g2.numOfEdges() == cnt);
}
