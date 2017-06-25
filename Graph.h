//
// Created by mrfarinq on 11.05.17.
//
// Program do zadania nr 2. SDiZO - Badanie efektywności algorytmów dla problemów MST oraz SP.
//
// Klasa Graph: metody do generowania spójnego skierowanego grafu, tworzenia grafu nieskierowanego,
// wczytywania grafu z pliku txt oraz wywoływanie metod drukujących wyniki poszczególnych algorytmów.
// Ponadto w klasie znajdują się obiekty będące instancjami reprezentacji macierzowej oraz list sąsiedztwa:
//  - NeighborhoodMatrixForGraph,
//  - AdjacencyListForGraph.
// Znajdują się tam metody pobierające krawędzie grafu skierowanego, nieskierowanego i generujące odpowiednie
// reprezentacje wymagane w założeniach projektu oraz funkcje odpowiadające za poszczególne algorytmy.
//
// W klasie UsefulStructuresForAlgorithms znajdują się struktury kolejki krawędzi bazującej na przerobionym
// kopcu z projektu nr 1. (maksymalny na minimalny), kolejka dla wierzchołków dla algorytmu Dijkstry oraz
// implementacja zbiorów rozłącznych dla algorytmu Kruskala.
//
// Klasa TimeMeasurement powstala w celu odseparowania kodu zwiazanego z testami od glownej funkcji main.
//

#ifndef SDIZO_2_GRAPH_H
#define SDIZO_2_GRAPH_H

#include <iostream>
#include "AdjacencyListForGraph.h"
#include "NeighborhoodMatrixForGraph.h"

class Graph {
private:
    
    int amountOfEdgesInAdjacencyListOfDirectedGraph;
    int maximumWeightOfEdge;
    int amountOfEdgesInDirectedGraph;
    int amountOfEdgesToDoubleInUndirectedGraph;
    int amountOfVertices;
    int firstVertex;
    int lastVertex;
    int **edgesOfDirectedGraph;
    bool negativeEdgeWeights;

public:
    AdjacencyListForGraph *adjacencyListForGraph;
    NeighborhoodMatrixForGraph *neighborhoodMatrixForGraph;
    
    Graph();
    
    virtual ~Graph();
    
    void DeleteGraph();
    
    void CreateGraphWithRandomIntegers();
    
    void CreateGraphWithRandomIntegers(int amountOfVertices, double density);
    
    void ReadGraphFromFile(std::string path);
    
    void GenerateUndirectedGraph();
    
    void SaveToFile();
    
    int getFirstVertex();
    
    void PrintGraphs();
    
    void PrintAllPrimsAlgorithms();
    
    void PrintAllKruskalsAlgorithms();
    
    void PrintAllDijkstrasAlgorithms();
    
    void PrintAllBellmanFordsAlgorithms();
};


#endif //SDIZO_2_GRAPH_H
