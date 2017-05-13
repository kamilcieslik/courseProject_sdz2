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
    AdjacencyListForGraph *adjacencyListForGraph;
    NeighborhoodMatrixForGraph *neighborhoodMatrixForGraph;
protected:
    int maximumWeightOfEdge;
    int amountOfEdgesInDirectedGraph;
    int amountOfEdgesInUndirectedGraph;
    int amountOfVertices;
    int firstVertex;
    int lastVertex;
    int **edgesOfDirectedGraph;
    int **edgesOfUndirectedGraph;
    
public:
    Graph();
    
    virtual ~Graph();
    
    int GetParamOfEdge(int whichVertex, int whichParam, std::string directOrUndirect);
    
    void CreateGraphWithRandomIntegers();
    
    void ReadGraphFromFile(std::string path);
    
    void GenerateUndirectedGraph();
    
    void SaveToFile();
};


#endif //SDIZO_2_GRAPH_H
