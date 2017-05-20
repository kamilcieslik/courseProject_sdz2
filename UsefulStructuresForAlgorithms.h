//
// Created by mrfarinq on 13.05.17.
//

#ifndef SDIZO_2_USEFULSTRUCTURESFORALGORITHMS_H
#define SDIZO_2_USEFULSTRUCTURESFORALGORITHMS_H

#include <iostream>
#include <climits>

struct Edge {
    int vertex_from = 0;
    int vertex_to = 0;
    int edge_weight = 0;
    
    void AddEdge(int vertex_from, int vertex_to, int edge_weight);
};

class Heap {
private:
    int numberOfEdges;
    Edge *arrayOfEdges;
public:
    Heap();
    
    ~Heap();
    
    Edge GetEdgeFromTheBeginning();
    
    void AddEdge(Edge newEdge, int edge_weight);
    
    void DeleteEdgeFromTheTop();
    
    int getAmountOfEdges();
    
};

struct Vertex {
    int vertex = 0;
    int distanceFromFirstVertex=0;
    
    void AddVertex(int vertex, int distanceFromFirstVertex);
};

class HeapForVertices {
private:
    int numberOfVertices;
    Vertex *arrayOfVertices;
public:
    HeapForVertices();
    
    ~HeapForVertices();
    
    Vertex GetVertexFromTheBeginning();
    
    void AddVertex(Vertex newVertex, int vertex_distanceFromFirstVertex);
    
    void DeleteVertexFromTheTop();
    
    int getAmountOfVertices();
    
    void changeDistanceFromFirstVertex(int vertex, int vertex_distanceFromFirstVertex);
    
    bool isIn(int vertex);
    
};

class DisjointSetDataStructure {
private:
    struct NodeOfDisjointSetDataStructure {
        int parent;
        int rank;
    };
    NodeOfDisjointSetDataStructure *disjointSetTree;
public:
    DisjointSetDataStructure(int numberOfNodes);
    
    ~DisjointSetDataStructure();
    
    void Init(int vertex);
    
    int FindParent(int vertex);
    
    void Union(int vertex_from, int vertex_to);
};

#endif //SDIZO_2_USEFULSTRUCTURESFORALGORITHMS_H
