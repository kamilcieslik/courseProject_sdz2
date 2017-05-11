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
    for (int i = 0; i < 2 * amountOfEdges; i++)
        delete edges[i];
    edges = nullptr;
}

void Graph::createGraphWithRandomIntegers() {
    
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
    
    amountOfEdges = (int) ceil(maximumAmountOfEdges * (density / 100));
    amountOfEdges *= 2;
    edges = new int *[amountOfEdges];
    
    //Creating a tree.
    int *tab = new int[amountOfVertices];
    for (int i = 0; i < amountOfVertices; i++) tab[i] = i;
    
    int weight;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist_verticles(0, amountOfVertices);
    int next, previous;
    previous = dist_verticles(gen);
    tab[previous] = -1;
    
    std::uniform_int_distribution<> dist_weight(1, maximumWeight);
    for (int i = 1; i < minimumAmountOfEdges + 1; i++) {
        while (true) {
            next = dist_verticles(gen);
            if (tab[next] >= 0)
                break;
        }
        
        edges[i - 1] = new int[3];
        edges[i - 1][0] = previous;
        edges[i - 1][1] = next;
        weight = dist_weight(gen);
        edges[i - 1][2] = weight;
        tab[next] = -1;
        previous = next;
    }
    bool czyJest;
    for (int i = minimumAmountOfEdges; i < (amountOfEdges / 2); i++) {
        while (true) {
            czyJest = false;
            previous = dist_verticles(gen);
            next = dist_verticles(gen);
            for (int j = 0; j < i; j++) {
                if ((edges[j][0] == previous && edges[j][1] == next) ||
                    (edges[j][0] == next && edges[j][1] == previous) || (next == previous)) {
                    czyJest = true;
                    break;
                }
            }
            if (!czyJest) {
                edges[i] = new int[3];
                edges[i][0] = previous;
                edges[i][1] = next;
                weight = dist_weight(gen);
                edges[i][2] = weight;
                break;
            }
        }
        
    }
    
    for (int i = (amountOfEdges / 2); i < amountOfEdges; i++) {
        
        while (true) {
            czyJest = false;
            previous = dist_verticles(gen);
            next = dist_verticles(gen);
            for (int j = 0; j < i; j++) {
                
                if ((edges[j][0] == previous && edges[j][1] == next) || (next == previous)) {
                    czyJest = true;
                    break;
                }
                
            }
            if (!czyJest) {
                edges[i] = new int[3];
                edges[i][0] = previous;
                edges[i][1] = next;
                weight = dist_weight(gen);
                edges[i][2] = weight;
                break;
            }
        }
        
    }
    firstVertex = edges[0][0];
    lastVertex = edges[amountOfVertices - 1][0];
    
    saveToFile();
}

void Graph::readGraphFromFile(std::string path) {
    
    std::fstream file(path, std::ios::in);
    if (file.is_open()) {
        file >> amountOfEdges;
        file >> amountOfVertices;
        file >> firstVertex;
        file >> lastVertex;
        if (file.fail()) throw std::error_condition();
        
        edges = new int *[amountOfEdges];
        int vertex_from, vertex_to, vertex_weight;
        for (int i = 0; i < amountOfEdges; i++) {
            file >> vertex_from;
            file >> vertex_to;
            file >> vertex_weight;
            
            if (file.fail()) throw std::error_condition();
            
            edges[i] = new int[3];
            edges[i][0] = vertex_from;
            edges[i][1] = vertex_to;
            edges[i][2] = vertex_weight;
        }
        
        file.close();
    }
}

void Graph::saveToFile() {
    std::fstream file("graph.txt", std::ios::out);
    if (file.good()) {
        file << amountOfEdges << " " << amountOfVertices << " " << firstVertex << " "
             << lastVertex << "\n";
        for (int i = 0; i < amountOfEdges; i++)
            file << edges[i][0] << " " << edges[i][1] << " " << edges[i][2] << "\n";
        file.close();
    }
}


