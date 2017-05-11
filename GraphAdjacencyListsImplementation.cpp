//
// Created by mrfarinq on 10.05.17.
//


#include "GraphAdjacencyListsImplementation.h"


GraphAdjListImpl::GraphAdjListImpl() {

}

GraphAdjListImpl::~GraphAdjListImpl() {
    delete[] arrayOfAdjListDirectedGraph;
};

void GraphAdjListImpl::PrintDirectedGraph() {
    int v;
    for (v = 0; v < amountOfVertices; ++v) {
        auto pointerToNodesOfAdjacencyList = arrayOfAdjListDirectedGraph[v].head;
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
    newNode->next = arrayOfAdjListDirectedGraph[vertex_to].head;
    arrayOfAdjListDirectedGraph[vertex_to].head = newNode;
}

void GraphAdjListImpl::CreateAdjacencyListsForDirectedGraph() {
    arrayOfAdjListDirectedGraph = new AdjacencyList<int>[amountOfVertices];
    for (int i = 0; i < amountOfVertices; ++i)
        arrayOfAdjListDirectedGraph[i].head = NULL;
    
    for (int i = 0; i < amountOfEdgesInDirectedGraph; i++) {
        AddEdgeForDirectedGraph(edgesOfDirectedGraph[i][1], edgesOfDirectedGraph[i][0], edgesOfDirectedGraph[i][2]);
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


