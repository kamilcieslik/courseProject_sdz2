//
// Created by mrfarinq on 13.05.17.
//

#ifndef SDIZO_2_NEIGHBORHOODMATRIXFORGRAPH_H
#define SDIZO_2_NEIGHBORHOODMATRIXFORGRAPH_H

#include <iostream>


class NeighborhoodMatrixForGraph {
private:
    int **arrayOfMatrixDirectedGraph;
    int amountOfVertices;
    
public:
    explicit NeighborhoodMatrixForGraph(int amountOfVertices);
    ~NeighborhoodMatrixForGraph();
    int GetWeightOfEdge(int vertex_from, int vertex_to);
    void AddEdgeForDirectedGraph(int vertex_from, int vertex_to, int vertex_weight);
    void PrintDirectedGraph();
    
    
};


#endif //SDIZO_2_NEIGHBORHOODMATRIXFORGRAPH_H
