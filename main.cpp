#include <iostream>



void displayMenu(const std::string& info, const std::string& alghoritm_1, const std::string& alghoritm_2) //Menu dla tabeli i listy.
{
    std::cout << std::endl;
    std::cout << info << std::endl;
    std::cout << "1. Wczytaj z pliku." << std::endl;
    std::cout << "2. Wygeneruj graf losowo." << std::endl;
    std::cout << "3. Wyświetl (macierzowo i listowo)." << std::endl;
    std::cout << "4. Algorytm - "<<alghoritm_1<<" (macierzowo i listowo)." << std::endl;
    std::cout << "5. Algorytm - "<<alghoritm_2<<" (macierzowo i listowo)." << std::endl;
    std::cout << "9. Test (pomiary)." << std::endl;
    std::cout << "0. Powrot do menu." << std::endl;
    std::cout << "Podaj opcje:";
}

void menu_mst() //Obsługa tabeli.
{
    
    std::string path;
    int option;
    do {
        displayMenu("*** Wyznaczanie minimalnego drzewa rozpinającego ***", "Prima", "Kruskala");
        std::cin >> option;
        std::cout << std::endl;
        switch (option) {
            case 1: //Tworzenie grafu z pliku txt.
               
                break;
            case 2: //Generowanie grafu pseudolosowo.
               
                break;
            case 3: //Wyświetlanie grafu (macierzowo i listowo).
               
                break;
            case 4: //Algorytm 1. - Prima (macierzowo i listowo).
                
                break;
            
            case 5: //Algorytm 2. - Kruskala (macierzowo i listowo).
                
                break;
            
            case 9: //Test - pomiary czasowe.
               
                break;

            default:
                break;
        }
        
    } while (option != 0);
}

void menu_the_shortest_path() //Obsługa tabeli.
{
    
    std::string path;
    int option;
    do {
        displayMenu("*** Wyznaczanie najkrótszej ścieżki w grafie ***", "Dijkstry", "Forda-Bellmana");
        std::cin >> option;
        std::cout << std::endl;
        switch (option) {
            case 1: //Tworzenie grafu z pliku txt.
                
                break;
            case 2: //Generowanie grafu pseudolosowo.
                
                break;
            case 3: //Wyświetlanie grafu (macierzowo i listowo).
                
                break;
            case 4: //Algorytm 1. - Dijkstry (macierzowo i listowo).
                
                break;
            
            case 5: //Algorytm 2. - Forda-Bellmana (macierzowo i listowo).
                
                break;
            
            case 9: //Test - pomiary czasowe.
                
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


