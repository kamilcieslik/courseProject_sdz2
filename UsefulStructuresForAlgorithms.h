//
// Created by mrfarinq on 13.05.17.
//

#ifndef SDIZO_2_USEFULSTRUCTURESFORALGORITHMS_H
#define SDIZO_2_USEFULSTRUCTURESFORALGORITHMS_H

#include <iostream>

struct Edge {
    int vertex_from;
    int vertex_to;
    int edge_weight;
};

class Heap {
private:
    int numberOfEdges;
    Edge *arrayOfEdges;
public:
    Heap(int numberOfEdges);
    
    ~Heap();
    
    Edge GetEdgeFromTheBeginning();
    
    void AddEdge(Edge newEdge, int edge_weight);
    
    void DeleteEdgeFromTheTop();
    
};


#endif //SDIZO_2_USEFULSTRUCTURESFORALGORITHMS_H
