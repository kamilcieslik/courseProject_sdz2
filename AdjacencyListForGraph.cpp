//
// Created by mrfarinq on 13.05.17.
//

#include <climits>
#include "AdjacencyListForGraph.h"

AdjacencyListForGraph::AdjacencyListForGraph(int amountOfVertices) : numberOfEdgesOfDirectedGraph(0),
                                                                     numberOfEdgesOfUndirectedGraph(0) {
    this->amountOfVertices = amountOfVertices;
    arrayOfAdjListDirectedGraph = new AdjacencyList<int>[amountOfVertices];
    arrayOfAdjListUndirectedGraph = new AdjacencyList<int>[amountOfVertices];
    for (int i = 0; i < amountOfVertices; ++i) {
        arrayOfAdjListDirectedGraph[i].head = nullptr;
        arrayOfAdjListUndirectedGraph[i].head = nullptr;
    }
}

AdjacencyListForGraph::~AdjacencyListForGraph() {
    AdjacencyList<int>::AdjacencyListNode *elem;
    
    for (auto i = 0; i < amountOfVertices; i++) {
        while (arrayOfAdjListDirectedGraph[i].head != nullptr) {
            elem = arrayOfAdjListDirectedGraph[i].head->next;
            delete arrayOfAdjListDirectedGraph[i].head;
            arrayOfAdjListDirectedGraph[i].head = elem;
        }
        
        while (arrayOfAdjListUndirectedGraph[i].head != nullptr) {
            elem = arrayOfAdjListUndirectedGraph[i].head->next;
            delete arrayOfAdjListUndirectedGraph[i].head;
            arrayOfAdjListUndirectedGraph[i].head = elem;
        }
    }
    
    
    delete[] arrayOfAdjListDirectedGraph;
    delete[] arrayOfAdjListUndirectedGraph;
    
}

void AdjacencyListForGraph::AddEdgeForDirectedGraph(int vertex_to, int vertex_from, int vertex_weight) {
    numberOfEdgesOfDirectedGraph++;
    newNode = new AdjacencyList<int>::AdjacencyListNode;
    
    newNode->vertex = vertex_from;
    newNode->weight = vertex_weight;
    newNode->next = arrayOfAdjListDirectedGraph[vertex_to].head;
    arrayOfAdjListDirectedGraph[vertex_to].head = newNode;
}

void AdjacencyListForGraph::AddEdgeForUndirectedGraph(int vertex_from, int vertex_to, int vertex_weight) {
    numberOfEdgesOfUndirectedGraph++;
    newNode = new AdjacencyList<int>::AdjacencyListNode;
    
    
    newNode->vertex = vertex_from;
    newNode->weight = vertex_weight;
    newNode->next = arrayOfAdjListUndirectedGraph[vertex_to].head;
    arrayOfAdjListUndirectedGraph[vertex_to].head = newNode;
    
    
    newNode = new AdjacencyList<int>::AdjacencyListNode;
    
    newNode->vertex = vertex_to;
    newNode->weight = vertex_weight;
    newNode->next = arrayOfAdjListUndirectedGraph[vertex_from].head;
    arrayOfAdjListUndirectedGraph[vertex_from].head = newNode;
}

int AdjacencyListForGraph::GetVerticeDegree(int vertex) {
    int degree = 0;
    if (numberOfEdgesOfDirectedGraph == 0) return degree;
    else {
        for (auto i = 0; i < numberOfEdgesOfDirectedGraph; i++) {
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
    for (auto i = 0; i < amountOfVertices; ++i) {
        auto pointerToNodesOfAdjacencyList = arrayOfAdjListDirectedGraph[i].head;
        std::cout << "Adj[" << i << "]: ";
        while (pointerToNodesOfAdjacencyList != nullptr) {
            std::cout << pointerToNodesOfAdjacencyList->vertex;
            std::cout << "(" << pointerToNodesOfAdjacencyList->weight << ")";
            pointerToNodesOfAdjacencyList = pointerToNodesOfAdjacencyList->next;
            if (pointerToNodesOfAdjacencyList != nullptr) std::cout << ", "; else std::cout << ".";
        }
        std::cout << std::endl;
    }
}

void AdjacencyListForGraph::PrintUndirectedGraph() {
    for (auto i = 0; i < amountOfVertices; ++i) {
        auto pointerToNodesOfAdjacencyList = arrayOfAdjListUndirectedGraph[i].head;
        std::cout << "Adj[" << i << "]: ";
        while (pointerToNodesOfAdjacencyList != nullptr) {
            std::cout << pointerToNodesOfAdjacencyList->vertex;
            std::cout << "(" << pointerToNodesOfAdjacencyList->weight << ")";
            pointerToNodesOfAdjacencyList = pointerToNodesOfAdjacencyList->next;
            if (pointerToNodesOfAdjacencyList != nullptr) std::cout << ", "; else std::cout << ".";
        }
        std::cout << std::endl;
    }
}

void AdjacencyListForGraph::PrimsAlgorithm(int firstVertex) {
    Heap heapForEdges(numberOfEdgesOfUndirectedGraph);
    bool *visited = new bool[amountOfVertices];
    
    for (auto i = 0; i < amountOfVertices; i++) {
        visited[i] = false;
    }
    
    int vertex = firstVertex;
    visited[vertex] = true;
    
    int weightOfMST=0;
    Edge edge;
    for (auto i = 1; i < amountOfVertices; i++) {
        
        for (auto p = arrayOfAdjListUndirectedGraph[vertex].head; p; p = p->next) { //change to while loop?
            if (!visited[p->vertex])
            {
                edge.vertex_from = vertex;
                edge.vertex_to = p->vertex;
                edge.edge_weight = p->weight;
                heapForEdges.AddEdge(edge, edge.edge_weight);
            }
        }
        do {
            edge = heapForEdges.GetEdgeFromTheBeginning();
            heapForEdges.DeleteEdgeFromTheTop();
        } while (visited[edge.vertex_to]);
    
        std::cout << "(" << edge.vertex_from << "," << edge.vertex_to << ")   " << edge.edge_weight << std::endl;
        weightOfMST+=edge.edge_weight;
        
        visited[edge.vertex_to]=true;
        vertex=edge.vertex_to;
    }
    delete[] visited;
    std::cout << "Waga MST: " << weightOfMST << std::endl;
}

