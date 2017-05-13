//
// Created by mrfarinq on 13.05.17.
//

#ifndef SDIZO_2_ADJACENCYLISTFORGRAPH_H
#define SDIZO_2_ADJACENCYLISTFORGRAPH_H

#include <iostream>


class AdjacencyListForGraph {
private:
    template<class T>
    struct AdjacencyList {
        struct AdjacencyListNode {
            T vertex;
            T weight;
            AdjacencyListNode *next= nullptr;
        };
        AdjacencyListNode *head= nullptr;
    };
    
    int numberOfEdges;
    int amountOfVertices;
    
    AdjacencyList<int> *arrayOfAdjListDirectedGraph;
public:
    explicit AdjacencyListForGraph(int amountOfVertices);
    ~AdjacencyListForGraph();
    
    int getNumberOfElements() const;
    
    int GetVerticeDegree(int vertex);
    void AddEdgeForDirectedGraph(int vertex_from, int vertex_to, int vertex_weight);
    void PrintDirectedGraph();
};


#endif //SDIZO_2_ADJACENCYLISTFORGRAPH_H
