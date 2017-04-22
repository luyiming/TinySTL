#ifndef GRAPH_ADJ_HPP
#define GRAPH_ADJ_HPP

// Graph implemented by adjacency list

#include "Graph.hpp"

#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <iostream>

using namespace std;

template <typename VertexType, typename EdgeType>
struct Edge {
    int dest;
    EdgeType weight;
    Edge<VertexType, EdgeType> *next;
    Edge() : dest(-1), weight(EdgeType()), next(nullptr) {}
    explicit Edge(int dest, EdgeType weight = EdgeType())
        : dest(dest), weight(weight), next(nullptr) {}
};

template <typename VertexType, typename EdgeType>
struct Vertex {
    VertexType data;
    Edge<VertexType, EdgeType> *outEdge;
    Vertex() : data(VertexType()), outEdge(nullptr) {}
    explicit Vertex(const VertexType &v) : data(v), outEdge(nullptr) {}
};

template <typename VertexType, typename EdgeType = int>
class GraphAdj : public Graph<VertexType, EdgeType> {
   public:
    GraphAdj();
    GraphAdj(const GraphAdj &rhs);
    GraphAdj &operator=(const GraphAdj &rhs);
    virtual ~GraphAdj() override;

    virtual int getVertexPos(const VertexType &vertex) override;
    virtual VertexType getValue(int v) override;
    virtual EdgeType getWeight(int v1, int v2) override;

    virtual void insertVertex(const VertexType &vertex) override;
    virtual void insertEdge(int v1, int v2, const EdgeType &weight = EdgeType()) override;
    virtual void removeVertex(int v) override;
    virtual void removeEdge(int v1, int v2) override;

    virtual int getFirstNeighbour(int v) override;
    virtual int getNextNeighbour(int v1, int v2) override;

   protected:
    Vertex<VertexType, EdgeType> *adj;
    size_t maxVertices;
    using Graph<VertexType, EdgeType>::numVertices;
    using Graph<VertexType, EdgeType>::numEdges;

   private:
    void overflowHandle();

    // for debugging/testing
   public:
    size_t check_true_edges();
    void debug_print();
};

template <typename V, typename E>
GraphAdj<V, E>::GraphAdj() : Graph<V, E>() {
    adj = nullptr;
    maxVertices = 0;
}

template <typename V, typename E>
inline GraphAdj<V, E>::GraphAdj(const GraphAdj &rhs) : Graph<V, E>(rhs) {
    maxVertices = rhs.maxVertices;
    if (rhs.adj == nullptr) {
        adj = nullptr;
        // assert(maxVertices == 0);
    } else {
        adj = new Vertex<V, E>[maxVertices];
        for (size_t i = 0; i < numVertices; i++) {
            adj[i].data = rhs.adj[i].data;
            adj[i].outEdge = nullptr;
            Edge<V, E> *tail = nullptr;
            Edge<V, E> *p = rhs.adj[i].outEdge;
            while (p != nullptr) {
                Edge<V, E> *q = new Edge<V, E>(p->dest, p->weight);
                // assert(q->next == nullptr);
                if (adj[i].outEdge == nullptr) {
                    tail = q;
                    adj[i].outEdge = q;
                } else {
                    tail->next = q;
                    tail = q;
                }
                p = p->next;
            }
        }
    }
}

template <typename V, typename E>
inline GraphAdj<V, E> &GraphAdj<V, E>::operator=(const GraphAdj &rhs) {
    if (this != &rhs) {
        maxVertices = rhs.maxVertices;
        if (rhs.adj == nullptr) {
            adj = nullptr;
            // assert(maxVertices == 0);
        } else {
            adj = new Vertex<V, E>[maxVertices];
            for (size_t i = 0; i < numVertices; i++) {
                adj[i].data = rhs.adj[i].data;
                adj[i].outEdge = nullptr;
                Edge<V, E> *tail = nullptr;
                Edge<V, E> *p = rhs.adj[i].outEdge;
                while (p != nullptr) {
                    Edge<V, E> *q = new Edge<V, E>(p->dest, p->weight);
                    // assert(q->next == nullptr);
                    if (adj[i].outEdge == nullptr) {
                        tail = q;
                        adj[i].outEdge = q;
                    } else {
                        tail->next = q;
                        tail = q;
                    }
                    p = p->next;
                }
            }
        }
    }
    return *this;
}

template <typename V, typename E>
GraphAdj<V, E>::~GraphAdj() {
    if (adj != nullptr) {
        for (size_t i = 0; i < numVertices; i++) {
            Edge<V, E> *p = nullptr;
            Edge<V, E> *q = adj[i].outEdge;
            while (q != nullptr) {
                p = q;
                q = q->next;
                delete p;
            }
        }
        delete[] adj;
    }
}

template <typename V, typename E>
int GraphAdj<V, E>::getVertexPos(const V &vertex) {
    assert(adj != nullptr);
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
    while (p != nullptr) {
        if (p->dest == v2) {
            return p->weight;
        }
        p = p->next;
    }
    assert(0);  // TODO: edge <v1, v2> not found
    return E();
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
    assert(0 <= v && v < (int)numVertices);
    int cnt = 0;

    // remove vertex v
    Edge<V, E> *p = nullptr;
    Edge<V, E> *q = adj[v].outEdge;
    while (q != nullptr) {
        cnt++;
        p = q;
        q = q->next;
        delete p;
    }
    adj[v] = adj[numVertices - 1];
    numVertices--;

    // remove edges concerning vertex v
    for (size_t i = 0; i < numVertices; i++) {
        p = nullptr;
        q = adj[i].outEdge;
        while (q != nullptr) {
            if (q->dest == v) {
                cnt++;
                if (p == nullptr) {
                    adj[i].outEdge = q->next;
                    p = q;
                    q = q->next;
                    delete p;
                    p = nullptr;
                } else {
                    p->next = q->next;
                    delete q;
                    q = p->next;
                }
            } else {
                p = q;
                q = q->next;
            }
        }
    }
    numEdges -= cnt;
    return;
}

template <typename V, typename E>
void GraphAdj<V, E>::removeEdge(int v1, int v2) {
    assert(0 <= v1 && v1 < (int)numVertices);
    assert(0 <= v2 && v2 < (int)numVertices);
    Edge<V, E> *p = nullptr;
    Edge<V, E> *q = adj[v1].outEdge;
    while (q != nullptr) {
        if (q->dest == v2) {
            break;
        }
        p = q;
        q = q->next;
    }
    if (q == nullptr) {
        assert(0);  // TODO: edge <v1, v2> not found
        return;
    }
    if (p == nullptr) {  // first edge
        adj[v1].outEdge = q->next;
        delete q;
    } else {
        p->next = q->next;
        delete q;
    }
    numEdges--;
    return;
}

template <typename V, typename E>
int GraphAdj<V, E>::getFirstNeighbour(int v) {
    assert(0 <= v && v < (int)numVertices);
    if (adj[v].outEdge == nullptr) {
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
    while (p != nullptr) {
        if (p->dest == v2) {
            break;
        }
        p = p->next;
    }
    if (p == nullptr || p->next == nullptr) {
        return -1;
    } else {
        return p->next->dest;
    }
}

template <typename V, typename E>
void GraphAdj<V, E>::overflowHandle() {
    assert(numVertices == maxVertices);
    if (adj == nullptr) {
        adj = new Vertex<V, E>[1];
        maxVertices = 1;
    } else {
        Vertex<V, E> *old = adj;
        maxVertices *= 2;
        adj = new Vertex<V, E>[maxVertices];
        for (size_t i = 0; i < numVertices; i++) {
            adj[i] = old[i];
        }
        delete[] old;
    }
}

template <typename V, typename E>
size_t GraphAdj<V, E>::check_true_edges() {
    int cnt = 0;
    for (size_t i = 0; i < numVertices; i++) {
        Edge<V, E> *p = adj[i].outEdge;
        while (p != nullptr) {
            cnt++;
            p = p->next;
        }
    }
    return cnt;
}

template <typename V, typename E>
void GraphAdj<V, E>::debug_print() {
    printf("numVertices ");
    cout << numVertices << endl;
    printf("numEdges    ");
    cout << numEdges << endl;
    printf("maxVertices ");
    cout << maxVertices << endl;
    for (size_t i = 0; i < numVertices; i++) {
        cout << i;
        printf("(%d): ", adj[i].data);
        Edge<V, E> *p = adj[i].outEdge;
        while (p != nullptr) {
            printf("%d ", p->dest);
            p = p->next;
        }
        printf("\n");
    }
}

/*
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
        if (q != nullptr) {
            st.push(Node(p, q->next));
            color[q->dst] = 1;
            printf("%d\n", q->dst);
            st.push(Node(q->dst, adj[q->dst].edge));
        }
    }

    delete[] color;
}
*/
#endif  // GRAPH_ADJ_HPP
