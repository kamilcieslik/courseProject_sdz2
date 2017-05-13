//
// Created by mrfarinq on 11.05.17.
//

#include <ctgmath>
#include "Graph.h"
#include <random>
#include <fstream>

Graph::Graph() : maximumWeight(9), amountOfEdgesInAdjacencyListOfDirectedGraph(0) {

}

Graph::~Graph() {
    for (int i = 0; i < 2 * amountOfEdgesInDirectedGraph; i++) {
        delete edgesOfDirectedGraph[i];
        delete edgesOfUndirectedGraph[i];
    }
    edgesOfDirectedGraph = nullptr;
    edgesOfUndirectedGraph = nullptr;
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
    
    
    std::random_device r;
    std::mt19937 randomEngine(r());  //GENERATOR LICZB PSEUDOLOSOWYCH
    std::uniform_int_distribution<int> edgeWeight(1, 9);    //ROWNOMIERNY ROZKLAD PRAWDOPODOBIENSTWA
    std::uniform_int_distribution<int> randomVertice(0, amountOfVertices - 1);
    
    int src, dst, weight;
    int edgesLeft = amountOfEdgesInDirectedGraph;
    
    edgesOfDirectedGraph = new int *[amountOfEdgesInDirectedGraph];
    adjacencyListForGraph=new AdjacencyListForGraph(amountOfVertices);
    neighborhoodMatrixForGraph = new NeighborhoodMatrixForGraph(amountOfVertices);
    
    src = randomVertice(randomEngine);
    
    int i = 0;
    int j = 0;
    while (j < (amountOfVertices - 1) && edgesLeft > 0) //PIERWSZA PETLA LACZY WSZYSTKIE WIERZCHOLKI ABY GRAF BYL SPOJNY
    {
        do
        {
            dst = randomVertice(randomEngine);
        } while (adjacencyListForGraph->GetVerticeDegree(dst) > 0 || dst == src);  //LOSUJ WIERZCHOLEK DOCELOWY DOPOKI NIE WYLOSUJESZ NIEPOLOCZONEGO ZADNA KRAWEDZIA WIERZCHOLKA ALBO NIE WYLOSUJESZ 2 ROZNYCH WIERCHOLKOW
        weight = edgeWeight(randomEngine);
    
        edgesOfDirectedGraph[i] = new int[3];
        edgesOfDirectedGraph[i][0] = src;
        edgesOfDirectedGraph[i][1] = dst;
        edgesOfDirectedGraph[i][2] = weight;

        adjacencyListForGraph->AddEdgeForDirectedGraph(src, dst, weight);
        neighborhoodMatrixForGraph->AddEdgeForDirectedGraph(src, dst, weight);
        
        src = dst;
        
        --edgesLeft;
        j++;
        i++;
    }
    
    for (int j = 0; j < edgesLeft; ++j) //DRUGA PETLA DODAJE POZOSTALE - LOSOWE KRAWEDZIE
    {
        do
        {
            src = randomVertice(randomEngine);
            dst = randomVertice(randomEngine);
            weight = edgeWeight(randomEngine);
        } while (neighborhoodMatrixForGraph->GetWeightOfEdge(src, dst) > 0 || dst == src);   //LOSUJ DOPOKI WYLOSUJESZ KRAWEDZ KTORA NIE ISTNIEJE
    
        edgesOfDirectedGraph[i] = new int[3];
        edgesOfDirectedGraph[i][0] = src;
        edgesOfDirectedGraph[i][1] = dst;
        edgesOfDirectedGraph[i][2] = weight;
        
        adjacencyListForGraph->AddEdgeForDirectedGraph(src, dst, weight);
        neighborhoodMatrixForGraph->AddEdgeForDirectedGraph(src, dst, weight);
        
        i++;
    }
    adjacencyListForGraph->PrintDirectedGraph();
    neighborhoodMatrixForGraph->PrintDirectedGraph();
}








