#include <iostream>
#include "Graph.h"

#pragma comment(linker, "/STACK:100000000")

void displayMenu(const std::string &info, const std::string &alghoritm_1,
                 const std::string &alghoritm_2) //Menu dla tabeli i listy.
{
    std::cout << std::endl;
    std::cout << info << std::endl;
    std::cout << "1. Wczytaj z pliku." << std::endl;
    std::cout << "2. Wygeneruj graf losowo." << std::endl;
    std::cout << "3. Wyświetl (macierzowo i listowo)." << std::endl;
    std::cout << "4. Algorytm - " << alghoritm_1 << " (macierzowo i listowo)." << std::endl;
    std::cout << "5. Algorytm - " << alghoritm_2 << " (macierzowo i listowo)." << std::endl;
    std::cout << "9. Test (pomiary)." << std::endl;
    std::cout << "0. Powrot do menu." << std::endl;
    std::cout << "Podaj opcje:";
}

void menu_mst() //Obsługa tabeli.
{
    
    Graph g;
    
    std::string path;
    int option;
    do {
        displayMenu("*** Wyznaczanie minimalnego drzewa rozpinającego ***", "Prima", "Kruskala");
        std::cin >> option;
        std::cout << std::endl;
        switch (option) {
            case 1: //Tworzenie grafu z pliku txt.
                std::cout << "Podaj sciezke pliku z danymi: ";
                std::cin >> path;
                g.ReadGraphFromFile(path);
                break;
                
            case 2: //Generowanie grafu pseudolosowo.
                g.CreateGraphWithRandomIntegers();
                break;
                
            case 3: //Wyświetlanie grafu (macierzowo i listowo).
                // g.PrintDirectedGraph();
                g.SaveToFile();
                break;
                
            case 4: //Algorytm 1. - Prima (macierzowo i listowo).
                g.adjacencyListForGraph->PrimsAlgorithm(0);
                std::cout << "MST -> algorytm Prima - listowo: " << std::endl;
                g.adjacencyListForGraph->PrintMST();
                g.neighborhoodMatrixForGraph->PrimsAlgorithm(0);
                std::cout << std::endl;
                std::cout << "MST -> algorytm Prima - macierzowo: " << std::endl;
                g.neighborhoodMatrixForGraph->PrintMST();
                break;
            
            case 5: //Algorytm 2. - Kruskala (macierzowo i listowo).
                g.adjacencyListForGraph->KruskalsAlgorithm(0);
                std::cout << "MST -> algorytm Kruskala - listowo: " << std::endl;
                g.adjacencyListForGraph->PrintMST();
                g.neighborhoodMatrixForGraph->KruskalsAlgorithm(0);
                std::cout << std::endl;
                std::cout << "MST -> algorytm Kruskala - macierzowo: " << std::endl;
                g.neighborhoodMatrixForGraph->PrintMST();
                break;
            
            case 9: //Test - pomiary czasowe.
                g.SaveToFile();
                break;
            
            default:
                break;
        }
        
    } while (option != 0);
}

void menu_the_shortest_path() //Obsługa tabeli.
{
    Graph g;
    std::string path;
    int option;
    do {
        displayMenu("*** Wyznaczanie najkrótszej ścieżki w grafie ***", "Dijkstry", "Forda-Bellmana");
        std::cin >> option;
        std::cout << std::endl;
        switch (option) {
            case 1: //Tworzenie grafu z pliku txt.
                std::cout << "Podaj sciezke pliku z danymi: ";
                std::cin >> path;
                g.ReadGraphFromFile(path);
                break;
                
            case 2: //Generowanie grafu pseudolosowo.
                g.CreateGraphWithRandomIntegers();
                break;
                
            case 3: //Wyświetlanie grafu (macierzowo i listowo).
                //g2.PrintDirectedGraph();
                break;
            
            case 4: //Algorytm 1. - Dijkstry (macierzowo i listowo).
                g.adjacencyListForGraph->DijkstrasAlgorithm(g.getFirstVertex());
                std::cout << "Shortest Path -> algorytm Dijkstry - listowo: " << std::endl;
                g.adjacencyListForGraph->PrintShortestPath();
                g.neighborhoodMatrixForGraph->DijkstrasAlgorithm(g.getFirstVertex());
                std::cout << "Shortest Path -> algorytm Dijkstry - macierzowo: " << std::endl;
                g.neighborhoodMatrixForGraph->PrintShortestPath();
                break;
            
            case 5: //Algorytm 2. - Bellmana-Forda (macierzowo i listowo).
                g.adjacencyListForGraph->Bellman_FordAlgorithm(g.getFirstVertex());
                std::cout << "Shortest Path -> algorytm Bellmana_Forda - listowo: " << std::endl;
                g.adjacencyListForGraph->PrintShortestPath();
                g.neighborhoodMatrixForGraph->Bellman_FordAlgorithm(g.getFirstVertex());
                std::cout << "Shortest Path -> algorytm Bellmana_Forda - macierzowo: " << std::endl;
                g.neighborhoodMatrixForGraph->PrintShortestPath();
                break;
            
            case 9: //Test - pomiary czasowe.
                g.SaveToFile();
                break;
            
            default:
                break;
        }
        
    } while (option != 0);
}

int main() {
    int option;
    do {
        std::cout << std::endl;
        std::cout << "==== MENU GŁÓWNE ===" << std::endl;
        std::cout << "1. Wyznaczanie minimalnego drzewa rozpinającego." << std::endl;
        std::cout << "2. Wyznaczanie najkrótszej ścieżki w grafie." << std::endl;
        std::cout << "0. Wyjscie." << std::endl;
        std::cout << "Podaj opcje:";
        std::cin >> option;
        std::cout << std::endl;
        
        switch (option) {
            case 1:
                menu_mst();
                break;
            
            case 2:
                menu_the_shortest_path();
                break;
            
            default:
                break;
        }
        
    } while (option != 0);
    
    return 0;
}


