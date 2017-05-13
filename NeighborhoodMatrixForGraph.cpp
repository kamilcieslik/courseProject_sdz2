//
// Created by mrfarinq on 13.05.17.
//

#include "NeighborhoodMatrixForGraph.h"

NeighborhoodMatrixForGraph::NeighborhoodMatrixForGraph(int amountOfVertices) {
    this->amountOfVertices=amountOfVertices;
    arrayOfMatrixDirectedGraph = new int *[amountOfVertices];
    
    for (int i = 0; i < amountOfVertices; i++) {
        arrayOfMatrixDirectedGraph[i] = new int[amountOfVertices];
    }
    
    for (int i = 0; i < amountOfVertices; i++) {
        for (int j = 0; j < amountOfVertices; j++) {
            arrayOfMatrixDirectedGraph[i][j] = 0;
        }
    }
    
}

NeighborhoodMatrixForGraph::~NeighborhoodMatrixForGraph() {
    for (int i = 0; i < amountOfVertices; i++) {
        delete[] arrayOfMatrixDirectedGraph[i];
    }
}

void NeighborhoodMatrixForGraph::AddEdgeForDirectedGraph(int vertex_from, int vertex_to, int edge_weight) {
        arrayOfMatrixDirectedGraph[vertex_from][vertex_to] = edge_weight;
}

int NeighborhoodMatrixForGraph::GetWeightOfEdge(int vertex_from, int vertex_to) {
    return arrayOfMatrixDirectedGraph[vertex_from][vertex_to];
}

void NeighborhoodMatrixForGraph::PrintDirectedGraph() {
    for (int i = 0; i < amountOfVertices; i++) {
        for (int j = 0; j < amountOfVertices; j++) {
            std::cout << arrayOfMatrixDirectedGraph[i][j] << " ";
        }
        std::cout << std::endl;
    }
}
