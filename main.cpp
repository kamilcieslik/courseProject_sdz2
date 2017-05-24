#include <iostream>
#include <fstream>
#include "Graph.h"
#include "TimeMeasurement.h"
#include "AlgorithmTest.h"


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
    std::cout << "8. Zapisz graf do pliku." << std::endl;
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
                try {
                    g.ReadGraphFromFile(path);
                } catch (std::logic_error &e) {
                    std::cout << e.what() << std::endl;
                }
                break;
            
            case 2: //Generowanie grafu pseudolosowo.
                try {
                    g.CreateGraphWithRandomIntegers();
                }
                catch (std::invalid_argument &e) {
                    std::cout << e.what() << std::endl;
                }
                break;
            
            case 3: //Wyświetlanie grafu (macierzowo i listowo w wersji skierowanej oraz nieskierowanej).
                try {
                    g.PrintGraphs();
                }
                catch (std::logic_error &e) {
                    std::cout << e.what() << std::endl;
                }
                break;
            
            case 4: //Algorytm 1. - Prima (macierzowo i listowo).
                try {
                    g.PrintAllPrimsAlgorithms();
                }
                catch (std::logic_error &e) {
                    std::cout << e.what() << std::endl;
                }
                break;
            
            case 5: //Algorytm 2. - Kruskala (macierzowo i listowo).
                try {
                    g.PrintAllKruskalsAlgorithms();
                }
                catch (std::logic_error &e) { //Cykl ujemny.
                    std::cout << e.what() << std::endl;
                }
                break;
            
            case 8: //Zapis grafu do pliku.
                try {
                    g.SaveToFile();
                }
                catch (std::logic_error &e) {
                    std::cout << e.what() << std::endl;
                }
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
                try {
                    g.CreateGraphWithRandomIntegers();
                }
                catch (std::invalid_argument &e) {
                    std::cout << e.what() << std::endl;
                }
                break;
            
            case 3: //Wyświetlanie grafu (macierzowo i listowo w wersji skierowanej oraz nieskierowanej).
                try {
                    g.PrintGraphs();
                }
                catch (std::logic_error &e) {
                    std::cout << e.what() << std::endl;
                }
                break;
            
            case 4: //Algorytm 1. - Dijkstry (macierzowo i listowo).
                try {
                    g.PrintAllDijkstrasAlgorithms();
                }
                catch (std::logic_error &e) {
                    std::cout << e.what() << std::endl;
                }
                break;
            
            case 5: //Algorytm 2. - Bellmana-Forda (macierzowo i listowo).
                try {
                    g.PrintAllBellmanFordsAlgorithms();
                }
                catch (std::logic_error &e) {
                    std::cout << e.what() << std::endl;
                }
                catch (std::underflow_error &e_2) { //Cykl ujemny.
                    std::cout << e_2.what() << std::endl;
                }
                break;
            
            case 8: //Zapis grafu do pliku.
                try {
                    g.SaveToFile();
                }
                catch (std::logic_error &e) {
                    std::cout << e.what() << std::endl;
                }
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
        std::cout << "3. Testy czasowe." << std::endl;
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
            case 3:
                int increaseAmountOfVertex;
                int numberOfIncreaseAmountOfVertex;
                int numberOfRepetitions;
                std::cout << "O ile ma się zwiększać ilość wierzchołków poczynając od 50? ";
                std::cin >> increaseAmountOfVertex;
                std::cout << "Ile razy ma się zwiększać ilość wierzchołków poczynając od 50? ";
                std::cin >> numberOfIncreaseAmountOfVertex;
                std::cout << "Podaj ilość instancji każdego zestawu danych w celu uśrednienia wyniku ";
                std::cin >> numberOfRepetitions;
                AlgorithmTest test;
                test.Test(increaseAmountOfVertex, numberOfRepetitions, numberOfIncreaseAmountOfVertex);
                break;
        }
        
    } while (option != 0);
    
    return 0;
}


