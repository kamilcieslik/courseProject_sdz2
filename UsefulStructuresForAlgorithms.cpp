//
// Created by mrfarinq on 13.05.17.
//

#include "UsefulStructuresForAlgorithms.h"

Heap::Heap(int numberOfEdges) {
    arrayOfEdges=new Edge[numberOfEdges];
    this->numberOfEdges=numberOfEdges;
}

Heap::~Heap() {
    delete[] arrayOfEdges;
    numberOfEdges=0;
}

Edge Heap::GetEdgeFromTheBeginning(){
    return arrayOfEdges[0];
}

void Heap::AddEdge(Edge newEdge, int edge_weight) {
    int i, j;
    i = numberOfEdges++;
    j = (i - 1) / 2;
    
    while (i > 0 && arrayOfEdges[j].edge_weight < edge_weight) {
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
    
    int i, j, lastLeaf;
    
    if (numberOfEdges--) {
        lastLeaf = arrayOfEdges[numberOfEdges].edge_weight;
        
        i = 0;
        j = 1;
        
        while (j < numberOfEdges) {
            if (j + 1 < numberOfEdges && arrayOfEdges[j + 1].edge_weight > arrayOfEdges[j].edge_weight) j++;
            if (lastLeaf >= arrayOfEdges[j].edge_weight) {
                break;
            }
            arrayOfEdges[i] = arrayOfEdges[j];
            i = j;
            j = 2 * j + 1;
        }
        
        arrayOfEdges[i].edge_weight = lastLeaf;
        
        
        Edge *temporaryTable;
        temporaryTable = new Edge[numberOfEdges];
        for (auto k = 0; k < numberOfEdges; k++) {
            temporaryTable[k] = arrayOfEdges[k];
        }
        delete[]arrayOfEdges;
        arrayOfEdges = temporaryTable;
        
        //delete[] temporaryTable; use valgrind
    }
}


