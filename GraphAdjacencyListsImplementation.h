//
// Created by mrfarinq on 10.05.17.
//

#pragma once

#include <iostream>
#include "AdjacencyList.h"
#include "AGraph.h"


class GraphAdjListImpl {
private:
    int V;
    AdjacencyList<int> *array;
    int amountOfEdges;
    int amountOfVertex;
    struct Edge {
        int vertex_from=-1;
        int vertex_to=-1;
        int weight=0;
    };

public:
    
    explicit GraphAdjListImpl(int V);
    
    ~GraphAdjListImpl();
    
    AdjacencyList<int>::AdjacencyListNode *newAdjacencyListNode(int valueOfVertex);
    
    void addEdge(int vertex_from, int vertex_to);
    
    virtual void printGraph();
    
};
