//
// Created by mrfarinq on 11.05.17.
//

#ifndef SDIZO_2_GRAPH_H
#define SDIZO_2_GRAPH_H

#include <iostream>

class Graph {
private:
    int maximumWeight;
    int amountOfEdges;
    int amountOfVertices;
    int firstVertex;
    int lastVertex;
    int **edges;
    
public:
    Graph();
    
    ~Graph();
    
    void createGraphWithRandomIntegers();
    void readGraphFromFile(std::string path);
    void saveToFile();
};


#endif //SDIZO_2_GRAPH_H
