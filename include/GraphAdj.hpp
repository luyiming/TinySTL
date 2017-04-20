#ifndef GRAPH_ADJ_HPP
#define GRAPH_ADJ_HPP

// Graph implemented by adjacency list

#include "Graph.hpp"

#include <cassert>
#include <cstdio>
#include <cstdlib>

template <typename VertexType, typename EdgeType>
struct Edge {
    int dest;
    EdgeType weight;
    Edge<VertexType, EdgeType> *next;
    Edge() : dest(-1), next(NULL) {}
    Edge(int dest) : dest(dest), next(NULL) {}
    Edge(int dest, int weight) : dest(dest), weight(weight), next(NULL) {}
};

template <typename VertexType, typename EdgeType>
struct Vertex {
    VertexType data;
    Edge<VertexType, EdgeType> *outEdge;
    Vertex() : outEdge(NULL) {}
    Vertex(const VertexType &v) : data(v), outEdge(NULL) {}
};

template <typename VertexType, typename EdgeType>
class GraphAdj : public Graph<VertexType, EdgeType> {
   public:
    GraphAdj();
    virtual ~GraphAdj() override;

    virtual int getVertexPos(const VertexType &vertex) override;
    virtual VertexType getValue(int v) override;
    virtual EdgeType getWeight(int v1, int v2) override;

    virtual void insertVertex(const VertexType &vertex) override;
    virtual void insertEdge(int v1, int v2, const EdgeType &weight) override;
    virtual void removeVertex(int v) override;
    virtual void removeEdge(int v1, int v2) override;

    virtual int getFirstNeighbour(int v) override;
    virtual int getNextNeighbour(int v1, int v2) override;

   private:
    Vertex<VertexType, EdgeType> *adj;
    size_t maxVertices;
    size_t numEdges;
    size_t numVertices;
   private:
    void overflowHandle();
    void print();
};

template <typename V, typename E>
GraphAdj<V, E>::GraphAdj() {
    adj = NULL;
    maxVertices = 0;
    numVertices = 0;
    numEdges = 0;
}
template <typename V, typename E>
GraphAdj<V, E>::~GraphAdj() {
    if (adj != NULL) {
        delete[] adj;
    }
}

template <typename V, typename E>
int GraphAdj<V, E>::getVertexPos(const V &vertex) {
    assert(adj != NULL);
    for (size_t i = 0; i < numVertices; i++) {
        if (adj[i].data == vertex) {
            return i;
        }
    }
    return -1;
}

template <typename V, typename E>
V GraphAdj<V, E>::getValue(int v) {
    assert(0 <= v && v < (int)numVertices);
    return adj[v].data;
}

template <typename V, typename E>
E GraphAdj<V, E>::getWeight(int v1, int v2) {
    assert(0 <= v1 && v1 < (int)numVertices);
    assert(0 <= v2 && v2 < (int)numVertices);
    Edge<V, E> *p = adj[v1].outEdge;
    while (p != NULL) {
        if (p->dest == v2) {
            return p->weight;
        }
        p = p->next;
    }
    assert(0);  // TODO: edge <v1, v2> not found
}

template <typename V, typename E>
void GraphAdj<V, E>::insertVertex(const V &vertex) {
    if (numVertices == maxVertices) {
        overflowHandle();
    }
    adj[numVertices] = Vertex<V, E>(vertex);
    numVertices++;
    return;
}

template <typename V, typename E>
void GraphAdj<V, E>::insertEdge(int v1, int v2, const E &weight) {
    assert(0 <= v1 && v1 < (int)numVertices);
    assert(0 <= v2 && v2 < (int)numVertices);
    Edge<V, E> *p = new Edge<V, E>(v2, weight);
    p->next = adj[v1].outEdge;
    adj[v1].outEdge = p;
    numEdges++;
    return;
}

template <typename V, typename E>
void GraphAdj<V, E>::removeVertex(int v) {
    // TODO
    assert(0);
    return;
}

template <typename V, typename E>
void GraphAdj<V, E>::removeEdge(int v1, int v2) {
    // TODO
    assert(0);
    return;
}

template <typename V, typename E>
int GraphAdj<V, E>::getFirstNeighbour(int v) {
    assert(0 <= v && v < numVertices);
    if (adj[v].outEdge == NULL) {
        return -1;
    } else {
        return adj[v].outEdge->dest;
    }
}

template <typename V, typename E>
int GraphAdj<V, E>::getNextNeighbour(int v1, int v2) {
    assert(0 <= v1 && v1 < (int)numVertices);
    assert(0 <= v2 && v2 < (int)numVertices);
    Edge<V, E> *p = adj[v1].outEdge;
    while (p != NULL) {
        if (p->dest == v2) {
            break;
        }
        p = p->next;
    }
    if (p->next == NULL) {
        return -1;
    } else {
        return p->next->dest;
    }
}

template <typename V, typename E>
void GraphAdj<V, E>::overflowHandle() {
    assert(numVertices == maxVertices);
    if (adj == NULL) {
        adj = new Vertex<V, E>[1];
        maxVertices = 1;
    } else {
        Vertex<V, E> *old = adj;
        maxVertices *= 2;
        adj = new Vertex<V, E>[maxVertices];
        for (size_t i = 0; i < numVertices; i++) {
            adj[i] = old[i];
        }
        numVertices = maxVertices;
        delete[] old;
    }
}

template <typename V, typename E>
void GraphAdj<V, E>::print() {
    printf("size %d\n", numVertices);
    printf("size %d\n", maxVertices);
    for (size_t i = 0; i < numVertices; i++) {
        printf("%d: ", i);
        Edge<V, E> *p = adj[i].outEdge;
        while (p != NULL) {
            printf("%d ", p->dest);
            p = p->next;
        }
        printf("\n");
    }
}

/*
void Graph::DFS() {
    int *color = new int[numVertices];
    for (int i = 0; i < numVertices; i++) {
        color[i] = 0;
    }
    DFS_aux(0, color);
    delete[] color;
}
void Graph::DFS_aux(int vertex, int *color) {
    if (color[vertex] == 0) {
        printf("%d\n", vertex);
        color[vertex] = 1;
        Edge *p = adj[vertex].edge;
        while (p != NULL) {
            DFS_aux(p->dst, color);
            p = p->next;
        }
    }
}
struct Node {
    int vertex;
    Edge *next;
    Node(int v, Edge *r) : vertex(v), next(r) {}
};
void Graph::DFS_stack() {
    int *color = new int[numVertices];
    for (int i = 0; i < numVertices; i++) {
        color[i] = 0;
    }
    stack<Node> st;

    st.push(Node(0, adj[0].edge));
    color[0] = 1;
    printf("0\n");

    while (!st.empty()) {
        int p = st.top().vertex;
        Edge *q = st.top().next;
        st.pop();
        if (q != NULL) {
            st.push(Node(p, q->next));
            color[q->dst] = 1;
            printf("%d\n", q->dst);
            st.push(Node(q->dst, adj[q->dst].edge));
        }
    }

    delete[] color;
}

int main() {
    Graph g;
    g.addVertex(0);
    g.addVertex(1);
    g.addVertex(2);
    g.addVertex(3);
    g.addVertex(4);
    g.addVertex(5);

    g.addEdge(0, 1);
    g.addEdge(1, 2);
    g.addEdge(2, 3);
    g.addEdge(2, 4);
    g.addEdge(1, 5);

    g.print();
    g.DFS();
    printf("\n");
    g.DFS_stack();
}
*/
#endif  // GRAPH_ADJ_HPP
