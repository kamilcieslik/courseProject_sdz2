//
// Created by mrfarinq on 13.05.17.
//

#include "AdjacencyListForGraph.h"

AdjacencyListForGraph::AdjacencyListForGraph(int amountOfVertices) {
    this->amountOfVertices = amountOfVertices;
    arrayOfAdjListDirectedGraph = new AdjacencyList<int>[amountOfVertices];
    for (int i = 0; i < amountOfVertices; ++i)
        arrayOfAdjListDirectedGraph[i].head = nullptr;
}

AdjacencyListForGraph::~AdjacencyListForGraph() {
    AdjacencyList<int>::AdjacencyListNode *elem;
    
    for (auto i = 0; i < amountOfVertices; i++) {
        while (arrayOfAdjListDirectedGraph[i].head != nullptr) {
            elem = arrayOfAdjListDirectedGraph[i].head->next;
            delete arrayOfAdjListDirectedGraph[i].head;
            arrayOfAdjListDirectedGraph[i].head = elem;
        }
    }
}

void AdjacencyListForGraph::AddEdgeForDirectedGraph(int vertex_from, int vertex_to, int vertex_weight) {
    numberOfEdges++;
    auto newNode = new AdjacencyList<int>::AdjacencyListNode;
    newNode->vertex = vertex_from;
    newNode->weight = vertex_weight;
    newNode->next = arrayOfAdjListDirectedGraph[vertex_to].head;
    arrayOfAdjListDirectedGraph[vertex_to].head = newNode;
}

int AdjacencyListForGraph::getNumberOfElements() const {
    return numberOfEdges;
}

int AdjacencyListForGraph::GetVerticeDegree(int vertex) {
    int degree = 0;
    if (numberOfEdges == 0) return degree;
    else {
        for (auto i = 0; i < numberOfEdges; i++) {
            if (arrayOfAdjListDirectedGraph[i].head != nullptr &&
                arrayOfAdjListDirectedGraph[i].head->vertex == vertex) {
                auto pointerToNodesOfAdjacencyList = arrayOfAdjListDirectedGraph[i].head;
                while (pointerToNodesOfAdjacencyList != nullptr) {
                    degree++;
                    pointerToNodesOfAdjacencyList = pointerToNodesOfAdjacencyList->next;
                }
                return degree;
            }
        }
    }
    
    return degree;
}

void AdjacencyListForGraph::PrintDirectedGraph() {
    int v;
    for (v = 0; v < amountOfVertices; ++v) {
        auto pointerToNodesOfAdjacencyList = arrayOfAdjListDirectedGraph[v].head;
        std::cout << "Adj[" << v << "]: ";
        while (pointerToNodesOfAdjacencyList != nullptr) {
            std::cout << pointerToNodesOfAdjacencyList->vertex;
            std::cout << "(" << pointerToNodesOfAdjacencyList->weight << ")";
            pointerToNodesOfAdjacencyList = pointerToNodesOfAdjacencyList->next;
            if (pointerToNodesOfAdjacencyList != nullptr) std::cout << ", "; else std::cout << ".";
        }
        std::cout << std::endl;
    }
}
