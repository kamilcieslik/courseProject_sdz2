//
// Created by mrfarinq on 11.05.17.
//

#ifndef SDIZO_2_GRAPH_H
#define SDIZO_2_GRAPH_H

#include <iostream>
#include "AdjacencyListForGraph.h"
#include "NeighborhoodMatrixForGraph.h"

class Graph {
private:
    
    int amountOfEdgesInAdjacencyListOfDirectedGraph;
    int maximumWeightOfEdge;
    int amountOfEdgesInDirectedGraph;
    int amountOfEdgesToDoubleInUndirectedGraph;
    int amountOfVertices;
    int firstVertex;
    int lastVertex;
    int **edgesOfDirectedGraph;
    bool negativeEdgeWeights;
    
public:
    AdjacencyListForGraph *adjacencyListForGraph;
    NeighborhoodMatrixForGraph *neighborhoodMatrixForGraph;
    
    Graph();
    
    virtual ~Graph();
    
    void DeleteGraph();
    
    void CreateGraphWithRandomIntegers();
    
    void CreateGraphWithRandomIntegers(int amountOfVertices, double density);
    
    void ReadGraphFromFile(std::string path);
    
    void GenerateUndirectedGraph();
    
    void SaveToFile();
    
    int getFirstVertex();
    
    void PrintGraphs();
    
    void PrintAllPrimsAlgorithms();
    
    void PrintAllKruskalsAlgorithms();
    
    void PrintAllDijkstrasAlgorithms();
    
    void PrintAllBellmanFordsAlgorithms();
};


#endif //SDIZO_2_GRAPH_H
