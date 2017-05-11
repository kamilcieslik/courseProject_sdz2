//
// Created by mrfarinq on 10.05.17.
//

#pragma once

#include <iostream>
#include "AdjacencyList.h"
#include "Graph.h"
#include "AGraph.h"


class GraphAdjListImpl: public Graph {
private:
    AdjacencyList<int> *array;
    

public:
    
    explicit GraphAdjListImpl();
    
    ~GraphAdjListImpl();
    
    //AdjacencyList<int>::AdjacencyListNode *newAdjacencyListNode(int valueOfVertex);
    
    void addEdge(int vertex_from, int vertex_to, int vertex_weight);
    
    virtual void printGraph();
    
    void CreateAdjacencyListsOfGraph();
    
    virtual void KruskalsAlgorithm();
    virtual void PrimsAlgorithm();
    virtual void DijkstrasAlgorithm();
    virtual void Ford_FulkersonAlgorithm();
    
};
