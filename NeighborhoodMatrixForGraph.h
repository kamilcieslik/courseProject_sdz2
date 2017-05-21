//
// Created by mrfarinq on 13.05.17.
//

#ifndef SDIZO_2_NEIGHBORHOODMATRIXFORGRAPH_H
#define SDIZO_2_NEIGHBORHOODMATRIXFORGRAPH_H

#include <iostream>
#include <climits>
#include "UsefulStructuresForAlgorithms.h"

class NeighborhoodMatrixForGraph {
private:
    int **arrayOfMatrixDirectedGraph;
    int **arrayOfMatrixUndirectedGraph;
    int numberOfEdgesOfDirectedGraph;
    int numberOfEdgesOfUndirectedGraph;
    int amountOfVertices;
    
    Edge *MST_Prim;
    int weightOfMST;
    
    int *shortestPaths;
    int *currentDistancesFromFirstVertex;
    int *previousVertices;
    
public:
    explicit NeighborhoodMatrixForGraph(int amountOfVertices);
    
    ~NeighborhoodMatrixForGraph();
    
    int GetWeightOfEdge(int vertex_from, int vertex_to);
    
    void AddEdgeForDirectedGraph(int vertex_from, int vertex_to, int vertex_weight);
    void AddEdgeForUndirectedGraph(int vertex_from, int vertex_to, int vertex_weight);
    
    void PrintDirectedGraph();
    
    void PrintUndirectedGraph();
    
    void KruskalsAlgorithm();
    
    void PrimsAlgorithm();
    
    void DijkstrasAlgorithm(int firstVertex);
    
    void Bellman_FordAlgorithm(int firstVertex);
    
    void PrintMST();
    
    void PrintShortestPath();
};


#endif //SDIZO_2_NEIGHBORHOODMATRIXFORGRAPH_H
