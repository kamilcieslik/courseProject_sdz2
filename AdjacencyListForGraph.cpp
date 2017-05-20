//
// Created by mrfarinq on 13.05.17.
//

#include "AdjacencyListForGraph.h"

AdjacencyListForGraph::AdjacencyListForGraph(int amountOfVertices) : numberOfEdgesOfDirectedGraph(0),
                                                                     numberOfEdgesOfUndirectedGraph(0),
                                                                     MST_Prim(nullptr),
                                                                     currentDistancesFromFirstVertex(nullptr),
                                                                     previousVertices(nullptr),
                                                                     shortestPaths(nullptr) {
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
    
    delete[] MST_Prim;
    MST_Prim = nullptr;
    
    delete[] currentDistancesFromFirstVertex;
    currentDistancesFromFirstVertex = nullptr;
    
    delete[] previousVertices;
    currentDistancesFromFirstVertex = nullptr;
    
    delete[] shortestPaths;
    shortestPaths = nullptr;
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
    Heap heapForEdges;
    bool *visited = new bool[amountOfVertices];
    
    for (auto i = 0; i < amountOfVertices; i++) {
        visited[i] = false;
    }
    
    int vertex = firstVertex;
    visited[vertex] = true;
    
    weightOfMST = 0;
    if (MST_Prim != nullptr) {
        delete[] MST_Prim;
        MST_Prim = nullptr;
    }
    MST_Prim = new Edge[amountOfVertices - 1];
    Edge edge;
    for (auto i = 1; i < amountOfVertices; i++) {
        auto pointer = arrayOfAdjListUndirectedGraph[vertex].head;
        while (pointer != nullptr) {
            if (!visited[pointer->vertex]) {
                edge.vertex_from = vertex;
                edge.vertex_to = pointer->vertex;
                edge.edge_weight = pointer->weight;
                heapForEdges.AddEdge(edge, edge.edge_weight);
            }
            pointer = pointer->next;
        }
        
        do {
            edge = heapForEdges.GetEdgeFromTheBeginning();
            heapForEdges.DeleteEdgeFromTheTop();
        } while (visited[edge.vertex_to]);
        
        MST_Prim[i - 1].AddEdge(edge.vertex_from, edge.vertex_to, edge.edge_weight);
        weightOfMST += edge.edge_weight;
        
        visited[edge.vertex_to] = true;
        vertex = edge.vertex_to;
    }
    delete[] visited;
}

void AdjacencyListForGraph::KruskalsAlgorithm(int firstVertex) {
    Heap heapForEdges;
    DisjointSetDataStructure disjointSetForVertex(amountOfVertices);
    
    for (auto i = 0; i < amountOfVertices; i++) {
        disjointSetForVertex.Init(i);
    }
    
    int vertex = firstVertex;
    Edge edge;
    
    for (auto i = vertex; i < amountOfVertices; i++) {
        auto pointer = arrayOfAdjListUndirectedGraph[i].head;
        while (pointer != nullptr) {
            edge.vertex_from = i;
            edge.vertex_to = pointer->vertex;
            edge.edge_weight = pointer->weight;
            heapForEdges.AddEdge(edge, edge.edge_weight);
            
            pointer = pointer->next;
        }
    }
    
    weightOfMST = 0;
    if (MST_Prim != nullptr) {
        delete[] MST_Prim;
        MST_Prim = nullptr;
    }
    MST_Prim = new Edge[amountOfVertices - 1];
    for (auto i = 1; i < amountOfVertices; i++) {
        do {
            edge = heapForEdges.GetEdgeFromTheBeginning();
            heapForEdges.DeleteEdgeFromTheTop();
        } while (disjointSetForVertex.FindParent(edge.vertex_from) == disjointSetForVertex.FindParent(edge.vertex_to));
        
        MST_Prim[i - 1].AddEdge(edge.vertex_from, edge.vertex_to, edge.edge_weight);
        weightOfMST += edge.edge_weight;
        disjointSetForVertex.Union(edge.vertex_from, edge.vertex_to);
    }
}

void AdjacencyListForGraph::PrintMST() {
    for (auto i = 0; i < amountOfVertices - 1; i++) {
        std::cout << "(" << MST_Prim[i].vertex_from << "," << MST_Prim[i].vertex_to << ")\t\t"
                  << MST_Prim[i].edge_weight
                  << std::endl;
    }
    std::cout << "Waga MST:\t" << weightOfMST << std::endl;
}

void AdjacencyListForGraph::DijkstrasAlgorithm(int firstVertex) {
    HeapForVertices heapForVertices;
    
    if (currentDistancesFromFirstVertex != nullptr) {
        delete[] currentDistancesFromFirstVertex;
        currentDistancesFromFirstVertex = nullptr;
        
        delete[] previousVertices;
        previousVertices = nullptr;
        
        delete[] shortestPaths;
        shortestPaths = nullptr;
    }
    currentDistancesFromFirstVertex = new int[amountOfVertices];
    previousVertices = new int[amountOfVertices];
    shortestPaths = new int[amountOfVertices];
    
    Vertex vertex_st;
    for (auto v = 0; v < amountOfVertices; v++) {
        currentDistancesFromFirstVertex[v] = INT_MAX;
        previousVertices[v] = INT_MIN;
        vertex_st.AddVertex(v, currentDistancesFromFirstVertex[v]);
        heapForVertices.AddVertex(vertex_st, vertex_st.distanceFromFirstVertex);
    }
    
    int vertex = firstVertex;
    currentDistancesFromFirstVertex[vertex] = 0;
    heapForVertices.changeDistanceFromFirstVertex(vertex, 0);
    
    while (heapForVertices.getAmountOfVertices() != 0) {
        vertex_st = heapForVertices.GetVertexFromTheBeginning();
        heapForVertices.DeleteVertexFromTheTop();
        auto pointer = arrayOfAdjListDirectedGraph[vertex_st.vertex].head;
        while (pointer != nullptr) {
            int v = pointer->vertex;
            
            if (currentDistancesFromFirstVertex[vertex_st.vertex] != INT_MAX &&
                pointer->weight + currentDistancesFromFirstVertex[vertex_st.vertex] <
                currentDistancesFromFirstVertex[v]) {
                currentDistancesFromFirstVertex[v] =
                        currentDistancesFromFirstVertex[vertex_st.vertex] + pointer->weight;
                heapForVertices.changeDistanceFromFirstVertex(v, currentDistancesFromFirstVertex[v]);
                previousVertices[v] = vertex_st.vertex;
            }
            pointer = pointer->next;
        }
    }
}

void AdjacencyListForGraph::Bellman_FordAlgorithm(int firstVertex) {
    if (currentDistancesFromFirstVertex != nullptr) {
        delete[] currentDistancesFromFirstVertex;
        currentDistancesFromFirstVertex = nullptr;
        
        delete[] previousVertices;
        previousVertices = nullptr;
        
        delete[] shortestPaths;
        shortestPaths = nullptr;
    }
    currentDistancesFromFirstVertex = new int[amountOfVertices];
    previousVertices = new int[amountOfVertices];
    shortestPaths = new int[amountOfVertices];
    
    for (auto v = 0; v < amountOfVertices; v++) {
        currentDistancesFromFirstVertex[v] = INT_MAX;
        previousVertices[v] = INT_MIN;
    }
    
    int vertex = firstVertex;
    currentDistancesFromFirstVertex[vertex] = 0;
    
    bool test;
    
    for (auto i = 1; i < amountOfVertices; i++) {
        test = true;
        for (auto u = 0; u < amountOfVertices; u++)
            for (auto pv = arrayOfAdjListDirectedGraph[u].head; pv; pv = pv->next)
                if (currentDistancesFromFirstVertex[pv->vertex] > currentDistancesFromFirstVertex[u] + pv->weight) {
                    test = false;
                    currentDistancesFromFirstVertex[pv->vertex] = currentDistancesFromFirstVertex[u] + pv->weight;
                    previousVertices[pv->vertex] = u;
                }
    }
    
    if (test == false) {
        for (auto u = 0; u < amountOfVertices; u++)
            for (auto pv = arrayOfAdjListDirectedGraph[u].head; pv; pv = pv->next)
                if (currentDistancesFromFirstVertex[pv->vertex] > currentDistancesFromFirstVertex[u] + pv->weight) {
                    throw std::underflow_error("Kopiec jest pusty.");
                } // ujemny cykl!!
        
    }
    
    int numberOfPredecessors = 0;
    for (auto i = 0; i < amountOfVertices; i++) {
        
        std::cout << i << ": ";
         for (auto j = i; j > -1; j = previousVertices[j]) shortestPaths[numberOfPredecessors++] = j;
         while (numberOfPredecessors) {
             if (numberOfPredecessors == 1) {
                 std::cout << shortestPaths[--numberOfPredecessors] << ".";
             } else {
                 std::cout << shortestPaths[--numberOfPredecessors] << " <- ";
             }
         }
        std::cout << " Koszt: " << currentDistancesFromFirstVertex[i] << std::endl;
    }
    
}

void AdjacencyListForGraph::PrintShortestPath() {
    int numberOfPredecessors = 0;
    for (auto i = 0; i < amountOfVertices; i++) {
        
        std::cout << i << ": ";
        for (auto j = i; j > -1; j = previousVertices[j]) shortestPaths[numberOfPredecessors++] = j;
        while (numberOfPredecessors) {
            if (numberOfPredecessors == 1) {
                std::cout << shortestPaths[--numberOfPredecessors] << ".";
            } else {
                std::cout << shortestPaths[--numberOfPredecessors] << " <- ";
            }
        }
        std::cout << " Koszt: " << currentDistancesFromFirstVertex[i] << std::endl;
    }
}
