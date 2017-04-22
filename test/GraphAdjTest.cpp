#ifndef GRAPHADJ_TEST_CPP
#define GRAPHADJ_TEST_CPP

#include "GraphAdj.hpp"
#include "gtest/gtest.h"

#include <cstdio>
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

TEST(GraphAdjTest, DFS) {
    GraphAdj<int> g;
    g.insertVertex(0);
    g.insertVertex(1);
    g.insertVertex(2);
    g.insertVertex(3);
    g.insertVertex(4);

    g.insertEdge(0, 1);
    g.insertEdge(1, 2);
    g.insertEdge(2, 3);
    g.insertEdge(2, 4);

    // DFS(g);
}

TEST(GraphAdjTest, Constructor) {
    GraphAdj<int, double> *g1 = new GraphAdj<int, double>();
    EXPECT_TRUE(g1->isEmpty());
    EXPECT_EQ(g1->numOfEdges(), 0);
    EXPECT_EQ(g1->numOfVertices(), 0);

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

TEST(GraphAdjTest, Insert) {
    GraphAdj<int, double> g;
    for (size_t i = 1; i <= 100; i++) {
        g.insertVertex(i);
        EXPECT_EQ(g.numOfVertices(), i);
    }
    size_t cnt = 0;
    for (size_t i = 0; i < 100; i++) {
        for (size_t j = i + 1; j < 100; j++) {
            g.insertEdge(i, j);
            EXPECT_EQ(g.check_true_edges(), ++cnt);
        }
    }
    GraphAdj<int, double> g2(g);
    EXPECT_EQ(g2.numOfVertices(), 100);
    EXPECT_EQ(g2.check_true_edges(), cnt);
}

TEST(GraphAdjTest, Remove) {
    GraphAdj<int, double> *g1 = new GraphAdj<int, double>();

    g1->insertVertex(0);
    g1->insertVertex(1);
    g1->insertVertex(2);
    g1->insertVertex(3);
    g1->insertVertex(4);
    g1->insertEdge(0, 1);
    g1->insertEdge(0, 2);
    g1->insertEdge(0, 3);
    g1->insertEdge(0, 4);
    g1->insertEdge(2, 0);
    g1->insertEdge(2, 3);
    g1->insertEdge(2, 4);

    g1->removeEdge(0, 4);
    EXPECT_EQ(g1->numOfVertices(), 5);
    EXPECT_EQ(g1->check_true_edges(), 6);

    g1->removeEdge(0, 1);
    EXPECT_EQ(g1->numOfVertices(), 5);
    EXPECT_EQ(g1->check_true_edges(), 5);

    g1->removeVertex(0);
    EXPECT_EQ(g1->numOfVertices(), 4);
    EXPECT_EQ(g1->check_true_edges(), 2);

    g1->removeVertex(0);
    g1->removeVertex(0);
    g1->removeVertex(0);
    g1->removeVertex(0);
    EXPECT_EQ(g1->numOfVertices(), 0);
    EXPECT_EQ(g1->check_true_edges(), 0);
    EXPECT_TRUE(g1->isEmpty());

    delete g1;
}
#endif  // GRAPHADJ_TEST_CPP
