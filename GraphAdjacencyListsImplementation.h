//
// Created by mrfarinq on 10.05.17.
//

#pragma once

#include <iostream>
#include "AdjacencyList.h"
#include "AGraph.h"


class GraphAdjListImpl : public AGraph {
private:
    int V;
    AdjacencyList<int> *array;
public:
    
    explicit GraphAdjListImpl(int V);
    
    GraphAdjListImpl(const GraphAdjListImpl &other);
    
    GraphAdjListImpl &operator=(const GraphAdjListImpl &other);
    
    ~GraphAdjListImpl();
    
    AdjacencyList<int>::AdjacencyListNode *newAdjacencyListNode(int valueOfVertex);
    
    void addEdge(int vertex_from, int vertex_to);
    
    virtual void printGraph();
    
    virtual void createGraphWithRandomIntegers(int numberOfElements);
    
    virtual void readFromFile(std::string path);
    
};
