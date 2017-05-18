//
// Created by mrfarinq on 13.05.17.
//

#ifndef SDIZO_2_USEFULSTRUCTURESFORALGORITHMS_H
#define SDIZO_2_USEFULSTRUCTURESFORALGORITHMS_H

#include <iostream>

struct Edge {
    int vertex_from=0;
    int vertex_to=0;
    int edge_weight=0;
    void AddEdge(int vertex_from, int vertex_to, int edge_weight);
};

class Heap {
private:
    int numberOfEdges;
    Edge *arrayOfEdges;
public:
    Heap();
    
    ~Heap();
    
    Edge GetEdgeFromTheBeginning();
    
    void AddEdge(Edge newEdge, int edge_weight);
    
    void DeleteEdgeFromTheTop();
    
};


#endif //SDIZO_2_USEFULSTRUCTURESFORALGORITHMS_H
