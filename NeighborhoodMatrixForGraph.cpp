//
// Created by mrfarinq on 13.05.17.
//

#include "NeighborhoodMatrixForGraph.h"

NeighborhoodMatrixForGraph::NeighborhoodMatrixForGraph(int amountOfVertices) : numberOfEdgesOfDirectedGraph(0),
                                                                               numberOfEdgesOfUndirectedGraph(0),
                                                                               MST_Prim(nullptr),
                                                                               currentDistancesFromFirstVertex(nullptr),
                                                                               previousVertices(nullptr),
                                                                               shortestPaths(nullptr) {
    this->amountOfVertices = amountOfVertices;
    arrayOfMatrixDirectedGraph = new int *[amountOfVertices];
    arrayOfMatrixUndirectedGraph = new int *[amountOfVertices];
    
    for (auto i = 0; i < amountOfVertices; i++) {
        arrayOfMatrixDirectedGraph[i] = new int[amountOfVertices];
        arrayOfMatrixUndirectedGraph[i] = new int[amountOfVertices];
    }
    
    for (auto i = 0; i < amountOfVertices; i++) {
        for (auto j = 0; j < amountOfVertices; j++) {
            arrayOfMatrixDirectedGraph[i][j] = 0;
            arrayOfMatrixUndirectedGraph[i][j] = 0;
        }
    }
}

NeighborhoodMatrixForGraph::~NeighborhoodMatrixForGraph() {
    for (auto i = 0; i < amountOfVertices; i++) {
        delete[] arrayOfMatrixDirectedGraph[i];
        delete[] arrayOfMatrixUndirectedGraph[i];
    }
    delete[] arrayOfMatrixDirectedGraph;
    delete[] arrayOfMatrixUndirectedGraph;
    arrayOfMatrixDirectedGraph = nullptr;
    arrayOfMatrixUndirectedGraph = nullptr;
    
    delete[] MST_Prim;
    MST_Prim = nullptr;
    
    delete[] currentDistancesFromFirstVertex;
    currentDistancesFromFirstVertex = nullptr;
    
    delete[] previousVertices;
    currentDistancesFromFirstVertex = nullptr;
    
    delete[] shortestPaths;
    shortestPaths = nullptr;
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

void NeighborhoodMatrixForGraph::PrintDirectedGraph() {
    std::cout << "W/K\t";
    for (auto i = 0; i < amountOfVertices; i++) {
        std::cout << i << ".\t";
    }
    std::cout << "\v" << std::endl;
    for (auto i = 0; i < amountOfVertices; i++) {
        for (auto j = 0; j < amountOfVertices; j++) {
            if (j == 0) {
                if (arrayOfMatrixDirectedGraph[i][j] < 0) {
                    std::cout << i << ".\t\b" << arrayOfMatrixDirectedGraph[i][j];
                } else {
                    std::cout << i << ".\t" << arrayOfMatrixDirectedGraph[i][j];
                }
            } else {
                if (arrayOfMatrixDirectedGraph[i][j] < 0) {
                    std::cout << "\t\b" << arrayOfMatrixDirectedGraph[i][j];
                } else {
                    std::cout << "\t" << arrayOfMatrixDirectedGraph[i][j];
                }
            }
        }
        std::cout << "\v" << std::endl;
    }
}

void NeighborhoodMatrixForGraph::PrintUndirectedGraph() {
    std::cout << "W/K\t";
    for (auto i = 0; i < amountOfVertices; i++) {
        std::cout << i << ".\t";
    }
    std::cout << "\v" << std::endl;
    for (auto i = 0; i < amountOfVertices; i++) {
        for (auto j = 0; j < amountOfVertices; j++) {
            if (j == 0) {
                if (arrayOfMatrixUndirectedGraph[i][j] < 0) {
                    std::cout << i << ".\t\b" << arrayOfMatrixUndirectedGraph[i][j];
                } else {
                    std::cout << i << ".\t" << arrayOfMatrixUndirectedGraph[i][j];
                }
            } else {
                if (arrayOfMatrixUndirectedGraph[i][j] < 0) {
                    std::cout << "\t\b" << arrayOfMatrixUndirectedGraph[i][j];
                } else {
                    std::cout << "\t" << arrayOfMatrixUndirectedGraph[i][j];
                }
            }
        }
        std::cout << "\v" << std::endl;
    }
}

void NeighborhoodMatrixForGraph::PrimsAlgorithm() {
    Heap heapForEdges(numberOfEdgesOfUndirectedGraph);
    bool *visited = new bool[amountOfVertices];
    
    for (auto i = 0; i < amountOfVertices; i++) {
        visited[i] = false;
    }
    
    int vertex = 0;
    visited[vertex] = true;
    
    weightOfMST = 0;
    if (MST_Prim != nullptr) {
        delete[] MST_Prim;
        MST_Prim = nullptr;
    }
    MST_Prim = new Edge[amountOfVertices - 1];
    Edge edge;
    for (auto i = 1; i < amountOfVertices; i++) {
        for (auto j = 0; j < amountOfVertices; j++) {
            if (arrayOfMatrixUndirectedGraph[vertex][j] != 0 &&
                !visited[j]) {
                edge.vertex_from = vertex;
                edge.vertex_to = j;
                edge.edge_weight = arrayOfMatrixUndirectedGraph[vertex][j];
                heapForEdges.AddEdge(edge, edge.edge_weight);
            }
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

void NeighborhoodMatrixForGraph::KruskalsAlgorithm() {
    Heap heapForEdges(numberOfEdgesOfUndirectedGraph);
    DisjointSetDataStructure disjointSetForVertex(amountOfVertices);
    
    for (auto i = 0; i < amountOfVertices; i++) {
        disjointSetForVertex.Init(i);
    }
    
    int vertex = 0;
    Edge edge;
    
    for (auto i = vertex; i < amountOfVertices; i++) {
        for (auto j = 0; j < amountOfVertices; j++) {
            if (arrayOfMatrixUndirectedGraph[i][j] != 0) {
                edge.vertex_from = i;
                edge.vertex_to = j;
                edge.edge_weight = arrayOfMatrixUndirectedGraph[i][j];
                heapForEdges.AddEdge(edge, edge.edge_weight);
            }
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

void NeighborhoodMatrixForGraph::PrintMST() {
    for (auto i = 0; i < amountOfVertices - 1; i++) {
        std::cout << "(" << MST_Prim[i].vertex_from << "," << MST_Prim[i].vertex_to << ")\t\t"
                  << MST_Prim[i].edge_weight
                  << std::endl;
    }
    std::cout << "Waga MST:\t" << weightOfMST << std::endl;
}

void NeighborhoodMatrixForGraph::DijkstrasAlgorithm(int firstVertex) {
    HeapForVertices heapForVertices(amountOfVertices);
    
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
        for (auto j = 0; j < amountOfVertices; j++) {
            if (arrayOfMatrixDirectedGraph[vertex_st.vertex][j] != 0) {
                int v = j;
                if (currentDistancesFromFirstVertex[vertex_st.vertex] != INT_MAX &&
                    arrayOfMatrixDirectedGraph[vertex_st.vertex][j] +
                    currentDistancesFromFirstVertex[vertex_st.vertex] <
                    currentDistancesFromFirstVertex[v]) {
                    currentDistancesFromFirstVertex[v] =
                            currentDistancesFromFirstVertex[vertex_st.vertex] +
                            arrayOfMatrixDirectedGraph[vertex_st.vertex][j];
                    heapForVertices.changeDistanceFromFirstVertex(v, currentDistancesFromFirstVertex[v]);
                    previousVertices[v] = vertex_st.vertex;
                }
                
            }
        }
    }
};

void NeighborhoodMatrixForGraph::Bellman_FordAlgorithm(int firstVertex) {
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
        currentDistancesFromFirstVertex[v] = INT_MAX - 1000;
        previousVertices[v] = INT_MIN;
    }
    
    int vertex = firstVertex;
    currentDistancesFromFirstVertex[vertex] = 0;
    
    bool withoutChange;
    bool exitBF = false;
    for (auto i = 1; i < amountOfVertices; i++) {
        if (exitBF) break;
        withoutChange = true;
        for (auto j = 0; j < amountOfVertices; j++) {
            for (auto k = 0; k < amountOfVertices; k++) {
                if (arrayOfMatrixDirectedGraph[j][k] != 0) {
                    if (currentDistancesFromFirstVertex[k] >
                        currentDistancesFromFirstVertex[j] + arrayOfMatrixDirectedGraph[j][k]) {
                        withoutChange = false;
                        currentDistancesFromFirstVertex[k] =
                                currentDistancesFromFirstVertex[j] + arrayOfMatrixDirectedGraph[j][k];
                        previousVertices[k] = j;
                    }
                }
            }
        }
        if (withoutChange) exitBF = true;
    }
    
    if (!exitBF) {
        for (auto j = 0; j < amountOfVertices; j++) {
            for (auto k = 0; k < amountOfVertices; k++) {
                if (arrayOfMatrixDirectedGraph[j][k] != 0) {
                    if (currentDistancesFromFirstVertex[k] >
                        currentDistancesFromFirstVertex[j] + arrayOfMatrixDirectedGraph[j][k]) {
                        throw std::underflow_error("Cykl ujemny.");
                    }
                }
            }
        }
    }
}

void NeighborhoodMatrixForGraph::PrintShortestPath(int firstVertex) {
    std::cout << "Start = " << firstVertex << std::endl;
    int numberOfPredecessors = 0;
    for (auto i = 0; i < amountOfVertices; i++) {
        
        std::cout << i << ":\t";
        std::cout << " Koszt: " << currentDistancesFromFirstVertex[i] <<"\t";
        for (auto j = i; j > -1; j = previousVertices[j]) shortestPaths[numberOfPredecessors++] = j;
        while (numberOfPredecessors) {
            if (numberOfPredecessors == 1) {
                std::cout << shortestPaths[--numberOfPredecessors] << ".";
            } else {
                std::cout << shortestPaths[--numberOfPredecessors] << " -> ";
            }
        }
        std::cout<<std::endl;
    }
}
