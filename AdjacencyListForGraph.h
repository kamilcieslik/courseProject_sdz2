//
// Created by mrfarinq on 13.05.17.
//

#ifndef SDIZO_2_ADJACENCYLISTFORGRAPH_H
#define SDIZO_2_ADJACENCYLISTFORGRAPH_H

#include <iostream>
#include "UsefulStructuresForAlgorithms.h"


class AdjacencyListForGraph {
private:
    template<class T>
    struct AdjacencyList {
        struct AdjacencyListNode {
            T vertex;
            T weight;
            AdjacencyListNode *next;
        };
        AdjacencyListNode *head;
    };
    
    
    int numberOfEdgesOfDirectedGraph;
    int numberOfEdgesOfUndirectedGraph;
    int amountOfVertices;
    
    AdjacencyList<int>::AdjacencyListNode *newNode;
    AdjacencyList<int> *arrayOfAdjListDirectedGraph;
    AdjacencyList<int> *arrayOfAdjListUndirectedGraph;
public:
    explicit AdjacencyListForGraph(int amountOfVertices);
    
    ~AdjacencyListForGraph();
    
    int GetVerticeDegree(int vertex);
    
    void AddEdgeForDirectedGraph(int vertex_from, int vertex_to, int vertex_weight);
    
    void AddEdgeForUndirectedGraph(int vertex_from, int vertex_to, int vertex_weight);
    
    void PrintDirectedGraph();
    
    void PrintUndirectedGraph();
    
    void KruskalsAlgorithm();
    
    void PrimsAlgorithm(int **edgesOfUndirectedGraph, int firstVertex, int amp);
    
    void DijkstrasAlgorithm();
    
    void Ford_FulkersonAlgorithm();
};


#endif //SDIZO_2_ADJACENCYLISTFORGRAPH_H
