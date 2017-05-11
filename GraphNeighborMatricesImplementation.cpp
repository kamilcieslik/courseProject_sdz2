//
// Created by mrfarinq on 11.05.17.
//

#include "GraphNeighborMatricesImplementation.h"

GraphNghbMatricesImpl::GraphNghbMatricesImpl() {

}

GraphNghbMatricesImpl::~GraphNghbMatricesImpl() {
    for (int i = 0; i < amountOfVertices; i++) {
        delete[] arrayOfMatrixDirectedGraph[i];
    }
}

void GraphNghbMatricesImpl::CreateNeighborMatricesForDirectedGraph() {
    arrayOfMatrixDirectedGraph = new int *[amountOfVertices];
    for (int i = 0; i < amountOfVertices; i++) {
        arrayOfMatrixDirectedGraph[i] = new int[amountOfVertices];
    }
    for (int i = 0; i < amountOfVertices; i++) {
        for (int j = 0; j < amountOfVertices; j++) {
            arrayOfMatrixDirectedGraph[i][j] = 0;
        }
    }
    for (int i = 0; i < amountOfEdgesInDirectedGraph; i++) {
        arrayOfMatrixDirectedGraph[edgesOfDirectedGraph[i][0]][edgesOfDirectedGraph[i][1]] = edgesOfDirectedGraph[i][2];
    }
}

void GraphNghbMatricesImpl::PrintDirectedGraph() {
    for (int i = 0; i < amountOfVertices; i++) {
        for (int j = 0; j < amountOfVertices; j++) {
            std::cout << arrayOfMatrixDirectedGraph[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

void GraphNghbMatricesImpl::KruskalsAlgorithm() {

}

void GraphNghbMatricesImpl::PrimsAlgorithm() {

}

void GraphNghbMatricesImpl::DijkstrasAlgorithm() {

}

void GraphNghbMatricesImpl::Ford_FulkersonAlgorithm() {

}




