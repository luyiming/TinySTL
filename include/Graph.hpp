#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <cstdlib>

template <typename VertexType, typename EdgeType>
class Graph {
   public:
    Graph() : numEdges(0), numVertices(0) {}
    virtual ~Graph() { return; }

    virtual int getVertexPos(const VertexType &vertex) = 0;
    virtual VertexType getValue(int v)                 = 0;
    virtual EdgeType getWeight(int v1, int v2)         = 0;

    virtual void insertVertex(const VertexType &vertex)             = 0;
    virtual void insertEdge(int v1, int v2, const EdgeType &weight) = 0;
    virtual void removeVertex(int v)                                = 0;
    virtual void removeEdge(int v1, int v2)                         = 0;

    bool isEmpty() const { return numVertices == 0; }
    size_t numOfEdges() const { return numEdges; }
    size_t numOfVertices() const { return numVertices; }

    virtual int getFirstNeighbour(int v)         = 0;
    virtual int getNextNeighbour(int v1, int v2) = 0;

   protected:
    size_t numEdges;
    size_t numVertices;
};

#endif  // GRAPH_HPP
