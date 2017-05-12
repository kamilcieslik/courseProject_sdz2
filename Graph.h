//
// Created by mrfarinq on 11.05.17.
//

#ifndef SDIZO_2_GRAPH_H
#define SDIZO_2_GRAPH_H

#include <iostream>

class Graph {
protected:
    int maximumWeight;
    int amountOfEdgesInDirectedGraph;
    int amountOfVertices;
    int firstVertex;
    int lastVertex;
    int **edgesOfDirectedGraph;
    
    int **edgesOfUndirectedGraph;
    
    //
    int amountOfEdgesInUndirectedGraph;
    //
    
public:
    Graph();
    
    virtual ~Graph();
    
    void CreateGraphWithRandomIntegers();
    void Graph::CreateGraphWithRandomIntegers_2();
    void ReadGraphFromFile(std::string path);
    void GenerateUndirectedGraph();
    void SaveToFile();
    virtual void KruskalsAlgorithm() = 0;
    virtual void PrimsAlgorithm() = 0;
    virtual void DijkstrasAlgorithm() =0;
    virtual void Ford_FulkersonAlgorithm() =0;
    
    int GetVerticeDegree(int vertex);
};


#endif //SDIZO_2_GRAPH_H
