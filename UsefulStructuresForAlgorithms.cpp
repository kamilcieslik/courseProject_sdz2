//
// Created by mrfarinq on 13.05.17.
//

#include "UsefulStructuresForAlgorithms.h"

Heap::Heap() {
    arrayOfEdges = new Edge[0];
    this->numberOfEdges = 0;
}

Heap::~Heap() {
    delete[] arrayOfEdges;
    numberOfEdges = 0;
    arrayOfEdges = nullptr;
}

Edge Heap::GetEdgeFromTheBeginning() {
    return arrayOfEdges[0];
}

void Heap::AddEdge(Edge newEdge, int edge_weight) {
    
    Edge *temporaryTable;
    temporaryTable = new Edge[numberOfEdges + 1];
    for (int i = 0; i < numberOfEdges; i++) {
        temporaryTable[i] = arrayOfEdges[i];
    }
    delete[] arrayOfEdges;
    arrayOfEdges = temporaryTable;
    
    int i, j;
    i = numberOfEdges++;
    j = (i - 1) / 2;
    
    while (i && arrayOfEdges[j].edge_weight > edge_weight) {
        arrayOfEdges[i] = arrayOfEdges[j];
        i = j;
        j = (i - 1) / 2;
    }
    
    arrayOfEdges[i] = newEdge;
}

void Heap::DeleteEdgeFromTheTop() {
    if (numberOfEdges == 0) {
        throw std::underflow_error("Kopiec jest pusty.");
    }
    
    int i, j;
    Edge lastLeaf;
    
    if (numberOfEdges) {
        lastLeaf = arrayOfEdges[--numberOfEdges];
        
        i = 0;
        j = 1;
        
        while (j < numberOfEdges) {
            if ((j + 1 < numberOfEdges) && (arrayOfEdges[j + 1].edge_weight < arrayOfEdges[j].edge_weight)) j++;
            if (lastLeaf.edge_weight <= arrayOfEdges[j].edge_weight) {
                break;
            }
            arrayOfEdges[i] = arrayOfEdges[j];
            i = j;
            j = 2 * j + 1;
        }
        
        arrayOfEdges[i] = lastLeaf;
        
        Edge *temporaryTable;
        temporaryTable = new Edge[numberOfEdges];
        for (auto k = 0; k < numberOfEdges; k++) {
            temporaryTable[k] = arrayOfEdges[k];
        }
        delete[]arrayOfEdges;
        arrayOfEdges = temporaryTable;
    }
}


void Edge::AddEdge(int vertex_from, int vertex_to, int edge_weight) {
    this->vertex_from=vertex_from;
    this->vertex_to=vertex_to;
    this->edge_weight=edge_weight;
}
