#include <iostream>

using namespace std;

void displayMenu(const string& info, const string& alghoritm_1, const string& alghoritm_2) //Menu dla tabeli i listy.
{
    cout << endl;
    cout << info << endl;
    cout << "1. Wczytaj z pliku." << endl;
    cout << "2. Wygeneruj graf losowo." << endl;
    cout << "3. Wyświetl (macierzowo i listowo)." << endl;
    cout << "4. Algorytm - "<<alghoritm_1<<" (macierzowo i listowo)." << endl;
    cout << "5. Algorytm - "<<alghoritm_2<<" (macierzowo i listowo)." << endl;
    cout << "9. Test (pomiary)." << endl;
    cout << "0. Powrot do menu." << endl;
    cout << "Podaj opcje:";
}

void menu_mst() //Obsługa tabeli.
{
    
    string path;
    int option;
    do {
        displayMenu("*** Wyznaczanie minimalnego drzewa rozpinającego ***", "Prima", "Kruskala");
        cin >> option;
        cout << endl;
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
    
    string path;
    int option;
    do {
        displayMenu("*** Wyznaczanie najkrótszej ścieżki w grafie ***", "Dijkstry", "Forda-Bellmana");
        cin >> option;
        cout << endl;
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
        cout << endl;
        cout << "==== MENU GŁÓWNE ===" << endl;
        cout << "1. Wyznaczanie minimalnego drzewa rozpinającego." << endl;
        cout << "2. Wyznaczanie najkrótszej ścieżki w grafie." << endl;
        cout << "0. Wyjscie." << endl;
        cout << "Podaj opcje:";
        cin >> option;
        cout << endl;
        
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


