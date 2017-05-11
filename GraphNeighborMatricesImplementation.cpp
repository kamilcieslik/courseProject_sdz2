//
// Created by mrfarinq on 11.05.17.
//

#include "GraphNeighborMatricesImplementation.h"

GraphNghbMatricesImpl::GraphNghbMatricesImpl() {

}

GraphNghbMatricesImpl::~GraphNghbMatricesImpl() {
    for (int i = 0; i < amountOfVertices; i++) {
        delete[] array[i];
    }
}

void GraphNghbMatricesImpl::CreateNeighborMatricesForDirectedGraph() {
    array = new int *[amountOfVertices];
    for (int i = 0; i < amountOfVertices; i++) {
        array[i] = new int[amountOfVertices];
    }
    for (int i = 0; i < amountOfVertices; i++) {
        for (int j = 0; j < amountOfVertices; j++) {
            array[i][j] = 0;
        }
    }
    for (int i = 0; i < amountOfEdges; i++) {
        array[edges[i][0]][edges[i][1]] = edges[i][2];
    }
}

void GraphNghbMatricesImpl::PrintDirectedGraph() {
    for (int i = 0; i < amountOfVertices; i++) {
        for (int j = 0; j < amountOfVertices; j++) {
            std::cout << array[i][j] << " ";
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




