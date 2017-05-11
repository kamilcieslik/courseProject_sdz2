//
// Created by mrfarinq on 10.05.17.
//


#include "GraphAdjacencyListsImplementation.h"


GraphAdjListImpl::GraphAdjListImpl() {

}

GraphAdjListImpl::~GraphAdjListImpl() {
    delete[] array;
};

void GraphAdjListImpl::PrintDirectedGraph() {
    int v;
    for (v = 0; v < amountOfVertices; ++v) {
        auto pointerToNodesOfAdjacencyList = array[v].head;
        std::cout << "Adj[" << v << "]: ";
        while (pointerToNodesOfAdjacencyList != nullptr) {
            std::cout << pointerToNodesOfAdjacencyList->vertex;
            std::cout<<"("<<pointerToNodesOfAdjacencyList->weight<<")";
            pointerToNodesOfAdjacencyList = pointerToNodesOfAdjacencyList->next;
            if (pointerToNodesOfAdjacencyList != nullptr) std::cout << ", "; else std::cout << ".";
        }
        std::cout << std::endl;
    }
}

void GraphAdjListImpl::AddEdgeForDirectedGraph(int vertex_from, int vertex_to, int vertex_weight) {
    auto newNode = new AdjacencyList<int>::AdjacencyListNode;
    newNode->vertex = vertex_from;
    newNode->weight = vertex_weight;
    newNode->next = array[vertex_to].head;
    array[vertex_to].head = newNode;
}

void GraphAdjListImpl::CreateAdjacencyListsForDirectedGraph() {
    array = new AdjacencyList<int>[amountOfVertices];
    for (int i = 0; i < amountOfVertices; ++i)
        array[i].head = NULL;
    
    for (int i = 0; i < amountOfEdges; i++) {
        AddEdgeForDirectedGraph(edges[i][1], edges[i][0], edges[i][2]);
    }
}

void GraphAdjListImpl::KruskalsAlgorithm() {

}

void GraphAdjListImpl::PrimsAlgorithm() {

}

void GraphAdjListImpl::DijkstrasAlgorithm() {

}

void GraphAdjListImpl::Ford_FulkersonAlgorithm() {

}


