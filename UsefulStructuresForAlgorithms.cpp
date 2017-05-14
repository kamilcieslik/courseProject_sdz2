//
// Created by mrfarinq on 13.05.17.
//

#include "UsefulStructuresForAlgorithms.h"

Heap::Heap(int numberOfEdges):numberOfEdges(0) {
    arrayOfEdges=new Edge[numberOfEdges];
    //this->numberOfEdges=numberOfEdges;
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
        
        arrayOfEdges[i]=lastLeaf;
        
    }
}


