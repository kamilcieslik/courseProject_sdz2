//
// Created by mrfarinq on 11.05.17.
//

#include <ctgmath>
#include "Graph.h"
#include <random>
#include <fstream>

Graph::Graph() : maximumWeight(9) {

}

Graph::~Graph() {
    for (int i = 0; i < 2 * amountOfEdgesInDirectedGraph; i++) {
        delete edgesOfDirectedGraph[i];
        delete edgesOfUndirectedGraph[i];
    }
    edgesOfDirectedGraph = nullptr;
    edgesOfUndirectedGraph = nullptr;
}

void Graph::CreateGraphWithRandomIntegers() {
    
    std::cout << "Podaj ilość wierzchołków: " << std::endl;
    std::cin >> amountOfVertices;
    if (amountOfVertices < 2) {
        throw std::invalid_argument("Liczba wierzchołków nie może być mniejsza od 2.");
    }
    
    int minimumAmountOfEdges, maximumAmountOfEdges;
    minimumAmountOfEdges = amountOfVertices - 1;
    maximumAmountOfEdges = ((amountOfVertices - 1) * amountOfVertices) / 2;
    
    auto minimumDensity = (int) ceil((((minimumAmountOfEdges * 100) / maximumAmountOfEdges)));
    
    double density;
    std::cout << "Podaj gęstość grafu nie mniejszą niż " << std::to_string(minimumDensity) << " %." << std::endl;
    std::cin >> density;
    if (density < minimumDensity) {
        throw std::invalid_argument(
                "Gęstość grafu nie może być mniejsza od gęstości minimalndej - " + std::to_string(minimumDensity) +
                " %.");
    }
    if (density > 100) {
        throw std::invalid_argument("Gęstość grafu nie może być większa od 100 %.");
    }
    
    amountOfEdgesInDirectedGraph = (int) ceil(maximumAmountOfEdges * (density / 100));
    amountOfEdgesInDirectedGraph *= 2;
    edgesOfDirectedGraph = new int *[amountOfEdgesInDirectedGraph];
    
    //Creating a tree.
    int *tab = new int[amountOfVertices];
    for (int i = 0; i < amountOfVertices; i++) tab[i] = i;
    
    int vertex_weight;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist_verticles(0, amountOfVertices);
    int vertex_to, vertex_from;
    vertex_from = dist_verticles(gen);
    tab[vertex_from] = -1;
    
    std::uniform_int_distribution<> dist_max_weight(1, maximumWeight);
    for (int i = 1; i < minimumAmountOfEdges + 1; i++) {
        while (true) {
            vertex_to = dist_verticles(gen);
            if (tab[vertex_to] >= 0)
                break;
        }
        
        edgesOfDirectedGraph[i - 1] = new int[3];
        edgesOfDirectedGraph[i - 1][0] = vertex_from;
        edgesOfDirectedGraph[i - 1][1] = vertex_to;
        vertex_weight = dist_max_weight(gen);
        edgesOfDirectedGraph[i - 1][2] = vertex_weight;
        tab[vertex_to] = -1;
        vertex_from = vertex_to;
    }
    bool czyJest;
    for (int i = minimumAmountOfEdges; i < (amountOfEdgesInDirectedGraph / 2); i++) {
        while (true) {
            czyJest = false;
            vertex_from = dist_verticles(gen);
            vertex_to = dist_verticles(gen);
            for (int j = 0; j < i; j++) {
                if ((edgesOfDirectedGraph[j][0] == vertex_from && edgesOfDirectedGraph[j][1] == vertex_to) ||
                    (edgesOfDirectedGraph[j][0] == vertex_to && edgesOfDirectedGraph[j][1] == vertex_from) ||
                    (vertex_to == vertex_from)) {
                    czyJest = true;
                    break;
                }
            }
            if (!czyJest) {
                edgesOfDirectedGraph[i] = new int[3];
                edgesOfDirectedGraph[i][0] = vertex_from;
                edgesOfDirectedGraph[i][1] = vertex_to;
                vertex_weight = dist_max_weight(gen);
                edgesOfDirectedGraph[i][2] = vertex_weight;
                break;
            }
        }
        
    }
    
    for (int i = (amountOfEdgesInDirectedGraph / 2); i < amountOfEdgesInDirectedGraph; i++) {
        
        while (true) {
            czyJest = false;
            vertex_from = dist_verticles(gen);
            vertex_to = dist_verticles(gen);
            for (int j = 0; j < i; j++) {
                
                if ((edgesOfDirectedGraph[j][0] == vertex_from && edgesOfDirectedGraph[j][1] == vertex_to) ||
                    (vertex_to == vertex_from)) {
                    czyJest = true;
                    break;
                }
                
            }
            if (!czyJest) {
                edgesOfDirectedGraph[i] = new int[3];
                edgesOfDirectedGraph[i][0] = vertex_from;
                edgesOfDirectedGraph[i][1] = vertex_to;
                vertex_weight = dist_max_weight(gen);
                edgesOfDirectedGraph[i][2] = vertex_weight;
                break;
            }
        }
        
    }
    firstVertex = edgesOfDirectedGraph[0][0];
    lastVertex = edgesOfDirectedGraph[amountOfVertices - 1][0];
    
    SaveToFile();
    //
    
    GenerateUndirectedGraph();
    
}

void Graph::ReadGraphFromFile(std::string path) {
    
    std::fstream file(path, std::ios::in);
    if (file.is_open()) {
        file >> amountOfEdgesInDirectedGraph;
        file >> amountOfVertices;
        file >> firstVertex;
        file >> lastVertex;
        if (file.fail()) throw std::error_condition();
        
        edgesOfDirectedGraph = new int *[amountOfEdgesInDirectedGraph];
        int vertex_from, vertex_to, vertex_weight;
        for (int i = 0; i < amountOfEdgesInDirectedGraph; i++) {
            file >> vertex_from;
            file >> vertex_to;
            file >> vertex_weight;
            
            if (file.fail()) throw std::error_condition();
            
            edgesOfDirectedGraph[i] = new int[3];
            edgesOfDirectedGraph[i][0] = vertex_from;
            edgesOfDirectedGraph[i][1] = vertex_to;
            edgesOfDirectedGraph[i][2] = vertex_weight;
        }
        
        file.close();
        GenerateUndirectedGraph();
    }
}

void Graph::SaveToFile() {
    std::fstream file("directedGraph.txt", std::ios::out);
    if (file.good()) {
        file << amountOfEdgesInDirectedGraph << " " << amountOfVertices << " " << firstVertex << " "
             << lastVertex << "\n";
        for (int i = 0; i < amountOfEdgesInDirectedGraph; i++)
            file << edgesOfDirectedGraph[i][0] << " " << edgesOfDirectedGraph[i][1] << " " << edgesOfDirectedGraph[i][2]
                 << "\n";
        file.close();
    }
}

void Graph::GenerateUndirectedGraph() {
    bool *duplicate;
    duplicate = new bool[amountOfEdgesInDirectedGraph];
    for (int i = 0; i < amountOfEdgesInDirectedGraph; i++)
        duplicate[i] = false;
    edgesOfUndirectedGraph = new int *[amountOfEdgesInDirectedGraph];
    for (int i = 0; i < amountOfEdgesInDirectedGraph; i++)
        edgesOfUndirectedGraph[i] = nullptr;
    
    for (int i = 0; i < amountOfEdgesInDirectedGraph; i++) {
        for (int j = 0; j < i; j++) {
            if ((edgesOfDirectedGraph[i][0] == edgesOfDirectedGraph[j][0] && edgesOfDirectedGraph[i][1] == edgesOfDirectedGraph[j][1]) || (edgesOfDirectedGraph[i][1] == edgesOfDirectedGraph[j][0] && edgesOfDirectedGraph[i][0] == edgesOfDirectedGraph[j][1])) {
                duplicate[i] = false;
                break;
            }
            duplicate[i] = true;
        }
    }
    
    duplicate[0] = true;
    amountOfEdgesInUndirectedGraph = 0;
    for (int i = 0; i < amountOfEdgesInDirectedGraph; i++) {
        if (duplicate[i] == true) {
            edgesOfUndirectedGraph[amountOfEdgesInUndirectedGraph] = new int[3];
            edgesOfUndirectedGraph[amountOfEdgesInUndirectedGraph][0] = edgesOfDirectedGraph[i][0];
            edgesOfUndirectedGraph[amountOfEdgesInUndirectedGraph][1] = edgesOfDirectedGraph[i][1];
            edgesOfUndirectedGraph[amountOfEdgesInUndirectedGraph][2] = edgesOfDirectedGraph[i][2];
            amountOfEdgesInUndirectedGraph++;
        }
    }
    
    delete[] duplicate;
}





