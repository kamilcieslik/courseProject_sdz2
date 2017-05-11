//
// Created by mrfarinq on 10.05.17.
//


#include "GraphAdjacencyListsImplementation.h"


GraphAdjListImpl::GraphAdjListImpl(int V) {
    this->V = V;
    array = new AdjacencyList<int>[V];
    for (int i = 0; i < V; ++i)
        array[i].head = NULL;
}

GraphAdjListImpl::~GraphAdjListImpl() {
    delete[] array;
};

AdjacencyList<int>::AdjacencyListNode *GraphAdjListImpl::newAdjacencyListNode(int valueOfVertex) {
    auto newNode = new AdjacencyList<int>::AdjacencyListNode;
    newNode->nodeValue = valueOfVertex;
    newNode->next = nullptr;
    return newNode;
}

void GraphAdjListImpl::addEdge(int vertex_from, int vertex_to) {
    auto newNode = newAdjacencyListNode(vertex_to);
    newNode->next = array[vertex_from].head;
    array[vertex_from].head = newNode;
    newNode = newAdjacencyListNode(vertex_from);
    newNode->next = array[vertex_to].head;
    array[vertex_to].head = newNode;
}

void GraphAdjListImpl::printGraph() {
    int v;
    for (v = 0; v < V; ++v) {
        auto pointerToNodesOfAdjacencyList = array[v].head;
        std::cout << "Adj[" << v << "]: ";
        while (pointerToNodesOfAdjacencyList != nullptr) {
            std::cout << pointerToNodesOfAdjacencyList->nodeValue;
            pointerToNodesOfAdjacencyList = pointerToNodesOfAdjacencyList->next;
            if (pointerToNodesOfAdjacencyList != nullptr) std::cout << ","; else std::cout << ".";
        }
        std::cout << std::endl;
    }
}


