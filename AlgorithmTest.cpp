//
// Created by mrfarinq on 22.05.17.
//

#include "AlgorithmTest.h"

AlgorithmTest::AlgorithmTest() {

}

AlgorithmTest::~AlgorithmTest() {

}

void AlgorithmTest::Test(int increaseAmountOfVertex, int numberOfRepetitions) {
    Graph g;
    TimeMeasurement t;
    std::vector<double> results;
    int firstAmountOfVertex = 50;
    int amountOfVertex = firstAmountOfVertex;
    double density = 25;
    double sum = 0;
    std::ofstream file;
    file.open("wyniki_testu.txt", std::ios::out);
    file << "Test czasów wykonywania algorytmów grafowych z dnia - " << t.currentDateTime()
         << ".\nDla każdego zestawu danych wyniki uśrednione z " << numberOfRepetitions
         << ". losowych instancji." << std::endl << std::endl << std::endl;
    
    for (auto k = 0; k < 4; k++) {
        for (auto i = 0; i < 6; i++) {
            results.push_back((double &&) amountOfVertex);
            
            //Algorytm Prima -> listowo
            sum = 0;
            
            for (auto j = 0; j < numberOfRepetitions; j++) {
                g.CreateGraphWithRandomIntegers(amountOfVertex, density);
                t.TimeStart();
                g.adjacencyListForGraph->PrimsAlgorithm();
                t.TimeStop();
                sum += t.GetTimeInSeconds();
            }
            sum = sum / numberOfRepetitions;
            results.push_back(sum);
            
            std::cout << "." << std::endl;
            
            //Algorytm Prima -> macierzowo
            sum = 0;
            
            for (auto j = 0; j < numberOfRepetitions; j++) {
                g.CreateGraphWithRandomIntegers(amountOfVertex, density);
                t.TimeStart();
                g.neighborhoodMatrixForGraph->PrimsAlgorithm();
                t.TimeStop();
                sum += t.GetTimeInSeconds();
            }
            sum = sum / numberOfRepetitions;
            results.push_back(sum);
            
            std::cout << "." << std::endl;
            
            //Algorytm Kruskala -> listowo
            sum = 0;
            
            for (auto j = 0; j < numberOfRepetitions; j++) {
                g.CreateGraphWithRandomIntegers(amountOfVertex, density);
                t.TimeStart();
                g.adjacencyListForGraph->KruskalsAlgorithm();
                t.TimeStop();
                sum += t.GetTimeInSeconds();
            }
            sum = sum / numberOfRepetitions;
            results.push_back(sum);
            
            std::cout << "." << std::endl;
            
            //Algorytm Kruskala -> macierzowo
            sum = 0;
            
            for (auto j = 0; j < numberOfRepetitions; j++) {
                g.CreateGraphWithRandomIntegers(amountOfVertex, density);
                t.TimeStart();
                g.neighborhoodMatrixForGraph->KruskalsAlgorithm();
                t.TimeStop();
                sum += t.GetTimeInSeconds();
            }
            sum = sum / numberOfRepetitions;
            results.push_back(sum);
            
            std::cout << "." << std::endl;
            
            //Algorytm Dijkstry -> listowo
            sum = 0;
            
            for (auto j = 0; j < numberOfRepetitions; j++) {
                g.CreateGraphWithRandomIntegers(amountOfVertex, density);
                t.TimeStart();
                g.adjacencyListForGraph->DijkstrasAlgorithm(g.getFirstVertex());
                t.TimeStop();
                sum += t.GetTimeInSeconds();
            }
            sum = sum / numberOfRepetitions;
            results.push_back(sum);
            
            std::cout << "." << std::endl;
            
            //Algorytm Dijkstry -> macierzowo
            sum = 0;
            
            for (auto j = 0; j < numberOfRepetitions; j++) {
                g.CreateGraphWithRandomIntegers(amountOfVertex, density);
                t.TimeStart();
                g.neighborhoodMatrixForGraph->DijkstrasAlgorithm(g.getFirstVertex());
                t.TimeStop();
                sum += t.GetTimeInSeconds();
            }
            sum = sum / numberOfRepetitions;
            results.push_back(sum);
            
            std::cout << "." << std::endl;
            
            //Algorytm Bellmana-Forda -> listowo
            sum = 0;
            
            for (auto j = 0; j < numberOfRepetitions; j++) {
                g.CreateGraphWithRandomIntegers(amountOfVertex, density);
                t.TimeStart();
                g.adjacencyListForGraph->Bellman_FordAlgorithm(g.getFirstVertex());
                t.TimeStop();
                sum += t.GetTimeInSeconds();
            }
            sum = sum / numberOfRepetitions;
            results.push_back(sum);
            
            std::cout << "." << std::endl;
            
            //Algorytm Bellmana-Forda -> macierzowo
            sum = 0;
            
            for (auto j = 0; j < numberOfRepetitions; j++) {
                g.CreateGraphWithRandomIntegers(amountOfVertex, density);
                t.TimeStart();
                g.neighborhoodMatrixForGraph->Bellman_FordAlgorithm(g.getFirstVertex());
                t.TimeStop();
                sum += t.GetTimeInSeconds();
            }
            sum = sum / numberOfRepetitions;
            results.push_back(sum);
            
            std::cout << "." << std::endl << std::endl;
            
            //Zwiększenie ilości wierzchołków
            
            amountOfVertex += increaseAmountOfVertex;
        }
        
        file << "Gęstość: " << density << std::endl;
        file
                << "Il_wierz\tPrim_listowo\tPrim_macierzowo\tKruskal_listowo\tKruskal_macierzowo\tDijkstra_listowo\tDijkstra_macierzowo\tFord_listowo\tFord_macierzowo\n";
        for (int i = 0; i < results.size(); i++) {
            file << results[i] << "\t";
            if (((i + 1) % 9) == 0) {
                file << "\n";
            }
        }
        file << std::endl;
        
        std::cout << "Gęstość: " << density << " - zrobione!";
        
        results.clear();
        
        if (density == 25) {
            density = 50;
        } else if (density == 50) {
            density = 75;
        } else if (density == 75) {
            density = 99;
        }
        
        amountOfVertex = firstAmountOfVertex;
    }
    
    file.close();
}

