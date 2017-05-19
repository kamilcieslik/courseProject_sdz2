//
// Created by mrfarinq on 13.05.17.
//

#include "NeighborhoodMatrixForGraph.h"

NeighborhoodMatrixForGraph::NeighborhoodMatrixForGraph(int amountOfVertices) : numberOfEdgesOfDirectedGraph(0),
                                                                               numberOfEdgesOfUndirectedGraph(0),
                                                                               MST_Prim(nullptr) {
    this->amountOfVertices = amountOfVertices;
    arrayOfMatrixDirectedGraph = new int *[amountOfVertices];
    arrayOfMatrixUndirectedGraph = new int *[amountOfVertices];
    
    for (int i = 0; i < amountOfVertices; i++) {
        arrayOfMatrixDirectedGraph[i] = new int[amountOfVertices];
        arrayOfMatrixUndirectedGraph[i] = new int[amountOfVertices];
    }
    
    for (int i = 0; i < amountOfVertices; i++) {
        for (int j = 0; j < amountOfVertices; j++) {
            arrayOfMatrixDirectedGraph[i][j] = 0;
            arrayOfMatrixUndirectedGraph[i][j] = 0;
        }
    }
}

NeighborhoodMatrixForGraph::~NeighborhoodMatrixForGraph() {
    for (int i = 0; i < amountOfVertices; i++) {
        delete[] arrayOfMatrixDirectedGraph[i];
        delete[] arrayOfMatrixUndirectedGraph[i];
    }
    delete[] arrayOfMatrixDirectedGraph;
    delete[] arrayOfMatrixUndirectedGraph;
    arrayOfMatrixDirectedGraph = nullptr;
    arrayOfMatrixUndirectedGraph = nullptr;
    
    delete[] MST_Prim;
    MST_Prim = nullptr;
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

int NeighborhoodMatrixForGraph::GetWeightOfEdge(int vertex_from, int vertex_to) {
    return arrayOfMatrixDirectedGraph[vertex_from][vertex_to];
}

void NeighborhoodMatrixForGraph::PrintDirectedGraph() {
    for (int i = 0; i < amountOfVertices; i++) {
        for (int j = 0; j < amountOfVertices; j++) {
            std::cout << arrayOfMatrixDirectedGraph[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

void NeighborhoodMatrixForGraph::PrintUndirectedGraph() {
    for (int i = 0; i < amountOfVertices; i++) {
        for (int j = 0; j < amountOfVertices; j++) {
            std::cout << arrayOfMatrixUndirectedGraph[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

void NeighborhoodMatrixForGraph::PrimsAlgorithm(int firstVertex) {
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
        for (int j = 0; j < amountOfVertices; j++) {
            if (arrayOfMatrixUndirectedGraph[vertex][j] != 0 && arrayOfMatrixUndirectedGraph[vertex][j] < 11 &&
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

void NeighborhoodMatrixForGraph::KruskalsAlgorithm(int firstVertex) {
    Heap heapForEdges;
    DisjointSetDataStructure disjointSetForVertex(amountOfVertices);
    
    for (auto i = 0; i < amountOfVertices; i++) {
        disjointSetForVertex.Init(i);
    }
    
    int vertex = firstVertex;
    Edge edge;
    
    for (int i = vertex; i < amountOfVertices; i++) {
        for (int j = 0; j < amountOfVertices; j++) {
            if (arrayOfMatrixUndirectedGraph[i][j] != 0 && arrayOfMatrixUndirectedGraph[i][j] < 11) {
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
        std::cout << "(" << MST_Prim[i].vertex_from << "," << MST_Prim[i].vertex_to << ")\t\t" << MST_Prim[i].edge_weight
                  << std::endl;
    }
    std::cout << "Waga MST:\t" << weightOfMST << std::endl;
}




