//
// Created by mrfarinq on 13.05.17.
//

#ifndef SDIZO_2_ADJACENCYLISTFORGRAPH_H
#define SDIZO_2_ADJACENCYLISTFORGRAPH_H

#include <iostream>
#include <climits>
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
    
    Edge *MST_Prim;
    int weightOfMST;
    
    int *shortestPaths;
    int *currentDistancesFromFirstVertex;
    int *previousVertices;
    
public:
    explicit AdjacencyListForGraph(int amountOfVertices);
    
    ~AdjacencyListForGraph();
    
    int GetVertexDegree(int vertex);
    
    void AddEdgeForDirectedGraph(int vertex_from, int vertex_to, int vertex_weight);
    
    void AddEdgeForUndirectedGraph(int vertex_from, int vertex_to, int vertex_weight);
    
    void PrintDirectedGraph();
    
    void PrintUndirectedGraph();
    
    void PrimsAlgorithm();
    
    void KruskalsAlgorithm();
    
    void DijkstrasAlgorithm(int firstVertex);
    
    void Bellman_FordAlgorithm(int firstVertex);
    
    void PrintMST();
    
    void PrintShortestPath(int firstVertex);
};


#endif //SDIZO_2_ADJACENCYLISTFORGRAPH_H
