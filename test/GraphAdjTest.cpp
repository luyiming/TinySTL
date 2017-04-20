#include "GraphAdj.hpp"

#include <iostream>

using namespace std;

template<typename T, typename E>
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

template<typename T, typename E>
void DFS(Graph<T,E> &graph) {
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
