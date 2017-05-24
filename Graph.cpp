//
// Created by mrfarinq on 11.05.17.
//

#include <ctgmath>
#include "Graph.h"
#include <random>
#include <fstream>

Graph::Graph() : maximumWeightOfEdge(9), amountOfEdgesInAdjacencyListOfDirectedGraph(0),
                 amountOfEdgesInDirectedGraph(0), amountOfEdgesToDoubleInUndirectedGraph(0),
                 adjacencyListForGraph(nullptr),
                 neighborhoodMatrixForGraph(nullptr), edgesOfDirectedGraph(nullptr),
                 negativeEdgeWeights(false) {
    
}

void Graph::DeleteGraph() {
    if (amountOfEdgesInDirectedGraph != 0)
        for (auto i = 0; i < amountOfEdgesInDirectedGraph; i++) {
            delete[] edgesOfDirectedGraph[i];
        }
    delete[] edgesOfDirectedGraph;
    
    delete adjacencyListForGraph;
    delete neighborhoodMatrixForGraph;
    
    adjacencyListForGraph = nullptr;
    neighborhoodMatrixForGraph = nullptr;
    
    edgesOfDirectedGraph = nullptr;
}


Graph::~Graph() {
    DeleteGraph();
}


void Graph::ReadGraphFromFile(std::string path) {
    if (adjacencyListForGraph != nullptr || neighborhoodMatrixForGraph != nullptr || edgesOfDirectedGraph != nullptr) {
        negativeEdgeWeights = false;
        DeleteGraph();
    }
    std::fstream file(path, std::ios::in);
    if (file.is_open()) {
        file >> amountOfEdgesInDirectedGraph;
        file >> amountOfVertices;
        file >> firstVertex;
        file >> lastVertex;
        if (file.fail()) throw std::logic_error("Błąd odczytu danych w pliku.");
        else {
            
            edgesOfDirectedGraph = new int *[amountOfEdgesInDirectedGraph];
            adjacencyListForGraph = new AdjacencyListForGraph(amountOfVertices);
            neighborhoodMatrixForGraph = new NeighborhoodMatrixForGraph(amountOfVertices);
            
            int vertex_from, vertex_to, edge_weight;
            for (auto i = 0; i < amountOfEdgesInDirectedGraph; i++) {
                file >> vertex_from;
                file >> vertex_to;
                file >> edge_weight;
                if (edge_weight < 0) negativeEdgeWeights = true;
                
                if (file.fail()) throw std::logic_error("Błąd odczytu danych w pliku.");
                else {
                    
                    edgesOfDirectedGraph[i] = new int[3];
                    edgesOfDirectedGraph[i][0] = vertex_from;
                    edgesOfDirectedGraph[i][1] = vertex_to;
                    edgesOfDirectedGraph[i][2] = edge_weight;
                    
                    adjacencyListForGraph->AddEdgeForDirectedGraph(vertex_from, vertex_to, edge_weight);
                    neighborhoodMatrixForGraph->AddEdgeForDirectedGraph(vertex_from, vertex_to, edge_weight);
                }
            }
            
            file.close();
            
            GenerateUndirectedGraph();
            
            PrintGraphs();
        }
    } else {
        std::cout << "Błąd otwarcia pliku.\n";
    }
}

void Graph::SaveToFile() {
    if (adjacencyListForGraph == nullptr || neighborhoodMatrixForGraph == nullptr)
        throw std::logic_error("Graf nie został zainicjalizowany.");
    std::fstream file("GraphGeneratedByProgram.txt", std::ios::out);
    if (file.good()) {
        file << amountOfEdgesInDirectedGraph << " " << amountOfVertices << " " << firstVertex << " "
             << lastVertex << "\n";
        for (auto i = 0; i < amountOfEdgesInDirectedGraph; i++)
            file << edgesOfDirectedGraph[i][0] << " " << edgesOfDirectedGraph[i][1] << " " << edgesOfDirectedGraph[i][2]
                 << "\n";
        file.close();
    }
}

void Graph::GenerateUndirectedGraph() {
    bool *edgeConnectingTheseVerticesAlreadyExist;
    edgeConnectingTheseVerticesAlreadyExist = new bool[amountOfEdgesInDirectedGraph];
    for (auto i = 0; i < amountOfEdgesInDirectedGraph; i++)
        edgeConnectingTheseVerticesAlreadyExist[i] = true;
    
    for (auto i = 0; i < amountOfEdgesInDirectedGraph; i++) {
        for (auto j = 0; j < i; j++) {
            if ((edgesOfDirectedGraph[i][0] == edgesOfDirectedGraph[j][0] &&
                 edgesOfDirectedGraph[i][1] == edgesOfDirectedGraph[j][1]) ||
                (edgesOfDirectedGraph[i][1] == edgesOfDirectedGraph[j][0] &&
                 edgesOfDirectedGraph[i][0] == edgesOfDirectedGraph[j][1])) {
                edgeConnectingTheseVerticesAlreadyExist[i] = true;
                break;
            }
            edgeConnectingTheseVerticesAlreadyExist[i] = false;
        }
    }
    
    int vertex_from, vertex_to, edge_weight;
    edgeConnectingTheseVerticesAlreadyExist[0] = false;
    amountOfEdgesToDoubleInUndirectedGraph = 0;
    for (auto i = 0; i < amountOfEdgesInDirectedGraph; i++) {
        if (!edgeConnectingTheseVerticesAlreadyExist[i]) {
            vertex_from = edgesOfDirectedGraph[i][0];
            vertex_to = edgesOfDirectedGraph[i][1];
            edge_weight = edgesOfDirectedGraph[i][2];
            
            adjacencyListForGraph->AddEdgeForUndirectedGraph(vertex_from, vertex_to, edge_weight);
            neighborhoodMatrixForGraph->AddEdgeForUndirectedGraph(vertex_from, vertex_to, edge_weight);
            
            amountOfEdgesToDoubleInUndirectedGraph++;
        }
    }
    
    delete[] edgeConnectingTheseVerticesAlreadyExist;
}

void Graph::CreateGraphWithRandomIntegers() {
    if (adjacencyListForGraph != nullptr || neighborhoodMatrixForGraph != nullptr || edgesOfDirectedGraph != nullptr) {
        DeleteGraph();
        negativeEdgeWeights = false;
    }
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
    adjacencyListForGraph = new AdjacencyListForGraph(amountOfVertices);
    neighborhoodMatrixForGraph = new NeighborhoodMatrixForGraph(amountOfVertices);
    
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist_verticles(0, amountOfVertices - 1);
    std::uniform_int_distribution<> dist_weight(1, 9);
    
    bool *vertexExist = new bool[amountOfVertices];
    for (int i = 0; i < amountOfVertices; i++) vertexExist[i] = false;
    
    int vertex_to, vertex_from, edge_weight;
    vertex_from = dist_verticles(gen);
    vertexExist[vertex_from] = true;
    
    for (int i = 1; i < minimumAmountOfEdges + 1; i++) {
        while (true) {
            vertex_to = dist_verticles(gen);
            if (!vertexExist[vertex_to])
                break;
        }
        edge_weight = dist_weight(gen);
        
        edgesOfDirectedGraph[i - 1] = new int[3];
        edgesOfDirectedGraph[i - 1][0] = vertex_from;
        edgesOfDirectedGraph[i - 1][1] = vertex_to;
        edgesOfDirectedGraph[i - 1][2] = edge_weight;
        adjacencyListForGraph->AddEdgeForDirectedGraph(vertex_from, vertex_to, edge_weight);
        neighborhoodMatrixForGraph->AddEdgeForDirectedGraph(vertex_from, vertex_to, edge_weight);
        
        vertexExist[vertex_to] = true;
        vertex_from = vertex_to;
    }
    
    bool edgeConnectingTheseVerticesAlreadyExist;
    for (int i = minimumAmountOfEdges; i < (amountOfEdgesInDirectedGraph / 2); i++) {
        while (true) {
            edgeConnectingTheseVerticesAlreadyExist = false;
            vertex_from = dist_verticles(gen);
            vertex_to = dist_verticles(gen);
            for (int j = 0; j < i; j++) {
                if ((edgesOfDirectedGraph[j][0] == vertex_from && edgesOfDirectedGraph[j][1] == vertex_to) ||
                    (edgesOfDirectedGraph[j][0] == vertex_to && edgesOfDirectedGraph[j][1] == vertex_from) ||
                    (vertex_to == vertex_from)) {
                    edgeConnectingTheseVerticesAlreadyExist = true;
                    break;
                }
            }
            if (!edgeConnectingTheseVerticesAlreadyExist) {
                edge_weight = dist_weight(gen);
                
                edgesOfDirectedGraph[i] = new int[3];
                edgesOfDirectedGraph[i][0] = vertex_from;
                edgesOfDirectedGraph[i][1] = vertex_to;
                edgesOfDirectedGraph[i][2] = edge_weight;
                adjacencyListForGraph->AddEdgeForDirectedGraph(vertex_from, vertex_to, edge_weight);
                neighborhoodMatrixForGraph->AddEdgeForDirectedGraph(vertex_from, vertex_to, edge_weight);
                break;
            }
        }
        
    }
    
    for (int i = (amountOfEdgesInDirectedGraph / 2); i < amountOfEdgesInDirectedGraph; i++) {
        
        while (true) {
            edgeConnectingTheseVerticesAlreadyExist = false;
            vertex_from = dist_verticles(gen);
            vertex_to = dist_verticles(gen);
            for (int j = 0; j < i; j++) {
                
                if ((edgesOfDirectedGraph[j][0] == vertex_from && edgesOfDirectedGraph[j][1] == vertex_to) ||
                    (vertex_to == vertex_from)) {
                    edgeConnectingTheseVerticesAlreadyExist = true;
                    break;
                }
                
            }
            if (!edgeConnectingTheseVerticesAlreadyExist) {
                edge_weight = dist_weight(gen);
                
                edgesOfDirectedGraph[i] = new int[3];
                edgesOfDirectedGraph[i][0] = vertex_from;
                edgesOfDirectedGraph[i][1] = vertex_to;
                edgesOfDirectedGraph[i][2] = edge_weight;
                adjacencyListForGraph->AddEdgeForDirectedGraph(vertex_from, vertex_to, edge_weight);
                neighborhoodMatrixForGraph->AddEdgeForDirectedGraph(vertex_from, vertex_to, edge_weight);
                break;
            }
        }
        
    }
    firstVertex = edgesOfDirectedGraph[0][0];
    lastVertex = edgesOfDirectedGraph[amountOfVertices - 1][0];
    
    GenerateUndirectedGraph();
    
    PrintGraphs();
}

int Graph::getFirstVertex() {
    return firstVertex;
}

void Graph::PrintGraphs() {
    if (adjacencyListForGraph == nullptr || neighborhoodMatrixForGraph == nullptr)
        throw std::logic_error("Graf nie został zainicjalizowany.");
    
    std::cout << "Reprezentacja listowa grafu skierowanego:\n\n";
    adjacencyListForGraph->PrintDirectedGraph();
    std::cout << std::endl;
    std::cout << "Reprezentacja macierzowa grafu skierowanego:\n\n";
    neighborhoodMatrixForGraph->PrintDirectedGraph();
    std::cout << std::endl;
    std::cout << "Reprezentacja listowa grafu nieskierowanego:\n\n";
    adjacencyListForGraph->PrintUndirectedGraph();
    std::cout << std::endl;
    std::cout << "Reprezentacja macierzowa grafu nieskierowanego:\n\n";
    neighborhoodMatrixForGraph->PrintUndirectedGraph();
    
}

void Graph::PrintAllPrimsAlgorithms() {
    if (adjacencyListForGraph == nullptr || neighborhoodMatrixForGraph == nullptr)
        throw std::logic_error("Graf nie został zainicjalizowany.");
    adjacencyListForGraph->PrimsAlgorithm();
    std::cout << "MST -> algorytm Prima - listowo: " << std::endl;
    adjacencyListForGraph->PrintMST();
    neighborhoodMatrixForGraph->PrimsAlgorithm();
    std::cout << std::endl;
    std::cout << "MST -> algorytm Prima - macierzowo: " << std::endl;
    neighborhoodMatrixForGraph->PrintMST();
}

void Graph::PrintAllKruskalsAlgorithms() {
    if (adjacencyListForGraph == nullptr || neighborhoodMatrixForGraph == nullptr)
        throw std::logic_error("Graf nie został zainicjalizowany.");
    adjacencyListForGraph->KruskalsAlgorithm();
    std::cout << "MST -> algorytm Kruskala - listowo: " << std::endl;
    adjacencyListForGraph->PrintMST();
    neighborhoodMatrixForGraph->KruskalsAlgorithm();
    std::cout << std::endl;
    std::cout << "MST -> algorytm Kruskala - macierzowo: " << std::endl;
    neighborhoodMatrixForGraph->PrintMST();
}

void Graph::PrintAllDijkstrasAlgorithms() {
    if (adjacencyListForGraph == nullptr || neighborhoodMatrixForGraph == nullptr)
        throw std::logic_error("Graf nie został zainicjalizowany.");
    if (negativeEdgeWeights)
        std::cout << "Graf zawiera ujemne krawędzie.\nAlgorytm Dijkstry może nie działać prawidłowo." << std::endl;
    adjacencyListForGraph->DijkstrasAlgorithm(getFirstVertex());
    std::cout << "Shortest Path -> algorytm Dijkstry - listowo: " << std::endl;
    adjacencyListForGraph->PrintShortestPath(getFirstVertex());
    neighborhoodMatrixForGraph->DijkstrasAlgorithm(getFirstVertex());
    std::cout << "Shortest Path -> algorytm Dijkstry - macierzowo: " << std::endl;
    neighborhoodMatrixForGraph->PrintShortestPath(getFirstVertex());
}

void Graph::PrintAllBellmanFordsAlgorithms() {
    if (adjacencyListForGraph == nullptr || neighborhoodMatrixForGraph == nullptr)
        throw std::logic_error("Graf nie został zainicjalizowany.");
    adjacencyListForGraph->Bellman_FordAlgorithm(getFirstVertex());
    std::cout << "Shortest Path -> algorytm Bellmana_Forda - listowo: " << std::endl;
    adjacencyListForGraph->PrintShortestPath(getFirstVertex());
    neighborhoodMatrixForGraph->Bellman_FordAlgorithm(getFirstVertex());
    std::cout << "Shortest Path -> algorytm Bellmana_Forda - macierzowo: " << std::endl;
    neighborhoodMatrixForGraph->PrintShortestPath(getFirstVertex());
}

void Graph::CreateGraphWithRandomIntegers(int amountOfVertices, double density) {
    if (adjacencyListForGraph != nullptr || neighborhoodMatrixForGraph != nullptr || edgesOfDirectedGraph != nullptr) {
        DeleteGraph();
        negativeEdgeWeights = false;
    }
    this->amountOfVertices = amountOfVertices;
    if (amountOfVertices < 2) {
        throw std::invalid_argument("Liczba wierzchołków nie może być mniejsza od 2.");
    }
    
    int minimumAmountOfEdges, maximumAmountOfEdges;
    minimumAmountOfEdges = amountOfVertices - 1;
    maximumAmountOfEdges = ((amountOfVertices - 1) * amountOfVertices) / 2;
    
    auto minimumDensity = (int) ceil((((minimumAmountOfEdges * 100) / maximumAmountOfEdges)));
    
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
    adjacencyListForGraph = new AdjacencyListForGraph(amountOfVertices);
    neighborhoodMatrixForGraph = new NeighborhoodMatrixForGraph(amountOfVertices);
    
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist_verticles(0, amountOfVertices - 1);
    std::uniform_int_distribution<> dist_weight(1, 9);
    
    bool *vertexExist = new bool[amountOfVertices];
    for (int i = 0; i < amountOfVertices; i++) vertexExist[i] = false;
    
    int vertex_to, vertex_from, edge_weight;
    vertex_from = dist_verticles(gen);
    vertexExist[vertex_from] = true;
    
    for (int i = 1; i < minimumAmountOfEdges + 1; i++) {
        while (true) {
            vertex_to = dist_verticles(gen);
            if (!vertexExist[vertex_to])
                break;
        }
        edge_weight = dist_weight(gen);
        
        edgesOfDirectedGraph[i - 1] = new int[3];
        edgesOfDirectedGraph[i - 1][0] = vertex_from;
        edgesOfDirectedGraph[i - 1][1] = vertex_to;
        edgesOfDirectedGraph[i - 1][2] = edge_weight;
        adjacencyListForGraph->AddEdgeForDirectedGraph(vertex_from, vertex_to, edge_weight);
        neighborhoodMatrixForGraph->AddEdgeForDirectedGraph(vertex_from, vertex_to, edge_weight);
        
        vertexExist[vertex_to] = true;
        vertex_from = vertex_to;
    }
    
    bool edgeConnectingTheseVerticesAlreadyExist;
    for (int i = minimumAmountOfEdges; i < (amountOfEdgesInDirectedGraph / 2); i++) {
        while (true) {
            edgeConnectingTheseVerticesAlreadyExist = false;
            vertex_from = dist_verticles(gen);
            vertex_to = dist_verticles(gen);
            for (int j = 0; j < i; j++) {
                if ((edgesOfDirectedGraph[j][0] == vertex_from && edgesOfDirectedGraph[j][1] == vertex_to) ||
                    (edgesOfDirectedGraph[j][0] == vertex_to && edgesOfDirectedGraph[j][1] == vertex_from) ||
                    (vertex_to == vertex_from)) {
                    edgeConnectingTheseVerticesAlreadyExist = true;
                    break;
                }
            }
            if (!edgeConnectingTheseVerticesAlreadyExist) {
                edge_weight = dist_weight(gen);
                
                edgesOfDirectedGraph[i] = new int[3];
                edgesOfDirectedGraph[i][0] = vertex_from;
                edgesOfDirectedGraph[i][1] = vertex_to;
                edgesOfDirectedGraph[i][2] = edge_weight;
                adjacencyListForGraph->AddEdgeForDirectedGraph(vertex_from, vertex_to, edge_weight);
                neighborhoodMatrixForGraph->AddEdgeForDirectedGraph(vertex_from, vertex_to, edge_weight);
                break;
            }
        }
        
    }
    
    for (int i = (amountOfEdgesInDirectedGraph / 2); i < amountOfEdgesInDirectedGraph; i++) {
        
        while (true) {
            edgeConnectingTheseVerticesAlreadyExist = false;
            vertex_from = dist_verticles(gen);
            vertex_to = dist_verticles(gen);
            for (int j = 0; j < i; j++) {
                
                if ((edgesOfDirectedGraph[j][0] == vertex_from && edgesOfDirectedGraph[j][1] == vertex_to) ||
                    (vertex_to == vertex_from)) {
                    edgeConnectingTheseVerticesAlreadyExist = true;
                    break;
                }
                
            }
            if (!edgeConnectingTheseVerticesAlreadyExist) {
                edge_weight = dist_weight(gen);
                
                edgesOfDirectedGraph[i] = new int[3];
                edgesOfDirectedGraph[i][0] = vertex_from;
                edgesOfDirectedGraph[i][1] = vertex_to;
                edgesOfDirectedGraph[i][2] = edge_weight;
                adjacencyListForGraph->AddEdgeForDirectedGraph(vertex_from, vertex_to, edge_weight);
                neighborhoodMatrixForGraph->AddEdgeForDirectedGraph(vertex_from, vertex_to, edge_weight);
                break;
            }
        }
        
    }
    firstVertex = edgesOfDirectedGraph[0][0];
    lastVertex = edgesOfDirectedGraph[amountOfVertices - 1][0];
    
    GenerateUndirectedGraph();
}










