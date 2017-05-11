//
// Created by mrfarinq on 11.05.17.
//

#ifndef SDIZO_2_GRAPHNEIGHBORMATRICESIMPLEMENTATION_H
#define SDIZO_2_GRAPHNEIGHBORMATRICESIMPLEMENTATION_H

#include "Graph.h"

class GraphNghbMatricesImpl: public Graph {
    int **array;


public:
    explicit GraphNghbMatricesImpl();
    
    ~GraphNghbMatricesImpl();
    
    void CreateNeighborMatricesForDirectedGraph();
    
    void PrintDirectedGraph();
    
    
    virtual void KruskalsAlgorithm();
    virtual void PrimsAlgorithm();
    virtual void DijkstrasAlgorithm();
    virtual void Ford_FulkersonAlgorithm();
};


#endif //SDIZO_2_GRAPHNEIGHBORMATRICESIMPLEMENTATION_H
