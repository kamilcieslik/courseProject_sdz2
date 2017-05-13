//
// Created by mrfarinq on 13.05.17.
//

#include <climits>
#include "AdjacencyListForGraph.h"
#include "list"

AdjacencyListForGraph::AdjacencyListForGraph(int amountOfVertices) : numberOfEdgesOfDirectedGraph(0),
                                                                     numberOfEdgesOfUndirectedGraph(0) {
    this->amountOfVertices = amountOfVertices;
    arrayOfAdjListDirectedGraph =  new AdjacencyList<int>[amountOfVertices];
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
    
    delete newNode;
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
    std::cout << "Reprezentacja listowa grafu skierowanego:\n\n";
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
    std::cout << "Reprezentacja listowa grafu nieskierowanego:\n\n";
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

void AdjacencyListForGraph::PrimsAlgorithm(int **edgesOfUndirectedGraph) {
    /*//int V = graph->V;// Get the number of vertices in graph AMOUNT OF GRTAPH
    int parent[amountOfVertices];   // Array to store constructed MST
    int key[amountOfVertices];      // Key values used to pick minimum weight edge in cut
    
    // minHeap represents set E
    struct MinHeap* minHeap = createMinHeap(V);
    
    // Initialize min heap with all vertices. Key value of
    // all vertices (except 0th vertex) is initially infinite
    for (int v = 1; v < amountOfVertices; ++v)
    {
        parent[v] = -1;
        key[v] = INT_MAX;
        minHeap->array[v] = newMinHeapNode(v, key[v]);
        minHeap->pos[v] = v;
    }
    
    // Make key value of 0th vertex as 0 so that it
    // is extracted first
    key[0] = 0;
    minHeap->array[0] = newMinHeapNode(0, key[0]);
    minHeap->pos[0]   = 0;
    
    // Initially size of min heap is equal to V
    minHeap->size = amountOfVertices;
    
    // In the followin loop, min heap contains all nodes
    // not yet added to MST.
    while (!isEmpty(minHeap))
    {
        // Extract the vertex with minimum key value
        struct MinHeapNode* minHeapNode = extractMin(minHeap);
        int u = minHeapNode->v; // Store the extracted vertex number
        
        // Traverse through all adjacent vertices of u (the extracted
        // vertex) and update their key values
        struct AdjListNode* pCrawl = graph->array[u].head;
        while (pCrawl != NULL)
        {
            int v = pCrawl->dest;
            
            // If v is not yet included in MST and weight of u-v is
            // less than key value of v, then update key value and
            // parent of v
            if (isInMinHeap(minHeap, v) && pCrawl->weight < key[v])
            {
                key[v] = pCrawl->weight;
                parent[v] = u;
                decreaseKey(minHeap, v, key[v]);
            }
            pCrawl = pCrawl->next;
        }
    }
    
    // print edges of MST
    printArr(parent, V);*/
}

