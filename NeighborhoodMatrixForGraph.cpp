//
// Created by mrfarinq on 13.05.17.
//

#include "NeighborhoodMatrixForGraph.h"

NeighborhoodMatrixForGraph::NeighborhoodMatrixForGraph(int amountOfVertices) : numberOfEdgesOfDirectedGraph(0),
                                                                               numberOfEdgesOfUndirectedGraph(0) {
    this->amountOfVertices = amountOfVertices;
    arrayOfMatrixDirectedGraph = new int *[amountOfVertices];
    arrayOfMatrixUndirectedGraph = new int *[amountOfVertices];
    
    for (int i = 0; i < amountOfVertices; i++) {
        arrayOfMatrixDirectedGraph[i] = new int[amountOfVertices];
        arrayOfMatrixUndirectedGraph[i] = new int[amountOfVertices];
    }
    
    for (int i = 0; i < amountOfVertices; i++) {
        for (int j = 0; j < amountOfVertices; j++) {
            arrayOfMatrixDirectedGraph[i][j] = 0;
            arrayOfMatrixUndirectedGraph[i][j] = 0;
        }
    }
}

NeighborhoodMatrixForGraph::~NeighborhoodMatrixForGraph() {
    for (int i = 0; i < amountOfVertices; i++) {
        delete[] arrayOfMatrixDirectedGraph[i];
        delete[] arrayOfMatrixUndirectedGraph[i];
    }
    delete[] arrayOfMatrixDirectedGraph;
    delete[] arrayOfMatrixUndirectedGraph;
    arrayOfMatrixDirectedGraph = nullptr;
    arrayOfMatrixUndirectedGraph = nullptr;
}

void NeighborhoodMatrixForGraph::AddEdgeForDirectedGraph(int vertex_from, int vertex_to, int edge_weight) {
    numberOfEdgesOfDirectedGraph++;
    arrayOfMatrixDirectedGraph[vertex_from][vertex_to] = edge_weight;
}

void NeighborhoodMatrixForGraph::AddEdgeForUndirectedGraph(int vertex_from, int vertex_to, int edge_weight) {
    numberOfEdgesOfUndirectedGraph++;
    arrayOfMatrixUndirectedGraph[vertex_from][vertex_to] = edge_weight;
    arrayOfMatrixUndirectedGraph[vertex_to][vertex_from] = edge_weight;
}

int NeighborhoodMatrixForGraph::GetWeightOfEdge(int vertex_from, int vertex_to) {
    return arrayOfMatrixDirectedGraph[vertex_from][vertex_to];
}

void NeighborhoodMatrixForGraph::PrintDirectedGraph() {
    std::cout << "Reprezentacja macierzowa grafu skierowanego:\n\n";
    for (int i = 0; i < amountOfVertices; i++) {
        for (int j = 0; j < amountOfVertices; j++) {
            std::cout << arrayOfMatrixDirectedGraph[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

void NeighborhoodMatrixForGraph::PrintUndirectedGraph() {
    std::cout << "Reprezentacja macierzowa grafu nieskierowanego:\n\n";
    for (int i = 0; i < amountOfVertices; i++) {
        for (int j = 0; j < amountOfVertices; j++) {
            std::cout << arrayOfMatrixUndirectedGraph[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

