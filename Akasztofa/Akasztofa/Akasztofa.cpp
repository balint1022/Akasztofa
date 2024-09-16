#define NOMINMAX  
#include <iostream> 
#include <vector>  
#include <string>  
#include <fstream> 
#include <cstdlib> 
#include <ctime>   
#include <algorithm>  
#include <cctype>  
#include <locale>  
#include <windows.h>  
#include <limits>  

using namespace std;

struct Akasztofa {
    vector<string> szintek;  

    Akasztofa(int maxHibak) {
        if (maxHibak == 4) {
            // Nehéz szintre, 4 hibalehetõség
            szintek = {
                "  +---+\n      |\n      |\n      |\n     ===",
                "  +---+\n  O   |\n      |\n      |\n     ===",
                "  +---+\n  O   |\n  |   |\n      |\n     ===",
                "  +---+\n  O   |\n /|\\  |\n      |\n     ===",
                "  +---+\n  O   |\n /|\\  |\n / \\  |\n     ==="
            };
        }
        else if (maxHibak == 5) {
            // Közepes szintre, 5 hibalehetõség
            szintek = {
                "  +---+\n      |\n      |\n      |\n     ===",
                "  +---+\n  O   |\n      |\n      |\n     ===",
                "  +---+\n  O   |\n  |   |\n      |\n     ===",
                "  +---+\n  O   |\n /|\\  |\n      |\n     ===",
                "  +---+\n  O   |\n /|\\  |\n /    |\n     ===",
                "  +---+\n  O   |\n /|\\  |\n / \\  |\n     ==="
            };
        }
        else {
            // Könnyû szintre, 6 hibalehetõség
            szintek = {
                "  +---+\n      |\n      |\n      |\n     ===",
                "  +---+\n  O   |\n      |\n      |\n     ===",
                "  +---+\n  O   |\n  |   |\n      |\n     ===",
                "  +---+\n  O   |\n /|   |\n      |\n     ===",
                "  +---+\n  O   |\n /|\\  |\n      |\n     ===",
                "  +---+\n  O   |\n /|\\  |\n /    |\n     ===",
                "  +---+\n  O   |\n /|\\  |\n / \\  |\n     ==="
            };
        }
    }

    
    void megjelenit(int hibak) {
        if (hibak < szintek.size()) {
            cout << szintek[hibak] << endl;  // A jelenlegi állapot megjelenítése
        }
        else {
            cout << szintek.back() << endl;  // Ha a hibák száma meghaladja a maximumot, a végállapot megjelenítése
        }
    }
};

// Tippelõ osztály
class Tippelo {
private:
    string kitalalandoSzo;  
    string tippeltSzo;  
    vector<char> tippeltBetuk;  
    int hibak;  
    int maxHibak;  
    Akasztofa akasztofa;  
    bool elhasznaltSegitseg;  

public:
    // Konstruktor
    Tippelo(string szo, int maxTipp) : akasztofa(maxTipp) {
        kitalalandoSzo = szo;
        tippeltSzo = string(szo.size(), '_');  // Kezdetben minden betû helyén aláhúzás jelenik meg
        hibak = 0;
        maxHibak = maxTipp;
        elhasznaltSegitseg = false;
    }

    // Megvizsgálja, hogy a játékos kitalálta-e a szót
    bool nyert() {
        return tippeltSzo == kitalalandoSzo;
    }

    // Megvizsgálja, hogy a játékos vesztett-e
    bool vesztett() {
        return hibak >= maxHibak;
    }

    // A jelenlegi játékállapot megjelenítése
    void jelenlegiMegjelenito() {
        cout << "---------------------------------------\n";
        akasztofa.megjelenit(hibak);  
        cout << "\nSzó: " << tippeltSzo << "\n"; 
        cout << "Az eddig tippelt betûk: ";
        for (char betu : tippeltBetuk) {
            cout << betu << " ";  
        }
        cout << "\nHibák: " << hibak << "/" << maxHibak << "\n"; 
        cout << "---------------------------------------\n";
    }

    // Betû tippelése
    void tipp(char betu) {
        betu = tolower(betu); 

        if (!isalpha(betu)) {
            cout << "Csak betût tippelhetsz!\n";
            return;
        }

        if (find(tippeltBetuk.begin(), tippeltBetuk.end(), betu) != tippeltBetuk.end()) {
            cout << "Ezt a betût már tippelted.\n";
            return;
        }

        tippeltBetuk.push_back(betu);

        bool helyesTipp = false;
        for (int i = 0; i < kitalalandoSzo.size(); i++) {
            if (kitalalandoSzo[i] == betu) {
                tippeltSzo[i] = betu;
                helyesTipp = true;
            }
        }

        if (!helyesTipp) {
            hibak++;  // Ha a tipp nem volt helyes, a hibaszám növelése
        }
    }

    // Segítség használata
    void hasznaljSegitseget() {
        if (elhasznaltSegitseg) {
            cout << "Már elhasználtad a segítséget!\n";
            return;
        }

        elhasznaltSegitseg = true;
        char segitseg = '_';
        for (int i = 0; i < kitalalandoSzo.size(); i++) {
            if (tippeltSzo[i] == '_') {
                segitseg = kitalalandoSzo[i];  // Az elsõ még nem kitalált betû felfedése
                break;
            }
        }

        cout << "Segítség: A következõ betû: " << segitseg << "\n";
        tipp(segitseg); 
    }
};

vector<string> szavak;  // Szavak tárolása

// A szavak beolvasása fájlból
void beolvasSzavak(const string& fileNev) {
    ifstream file(fileNev);

    if (!file) {
        cerr << "A fájlt nem sikerült megnyitni.\n";
        exit(1);  
    }

    string szo;
    while (file >> szo) {
        transform(szo.begin(), szo.end(), szo.begin(), ::tolower);  
        szavak.push_back(szo); 
    }

    file.close();
}

// Véletlenszerû kiválasztás
string randomSzo() {
    srand(time(0));  
    int index = rand() % szavak.size();
    return szavak[index];  
}


bool jatekInditas(int nehezsegiSzint, int& pont) {
    string szo = randomSzo();  // Véletlenszerû szó kiválasztása
    int maxHibak;

    // Nehézségi szint beállítása
    switch (nehezsegiSzint) {
    case 1:
        maxHibak = 6; // Könnyû szint
        break;
    case 2:
        maxHibak = 5; // Közepes szint
        break;
    case 3:
        maxHibak = 4; // Nehéz szint
        break;
    default:
        cout << "Nem létezõ nehézségi szint, alapértelmezett nehézségi szint a közepes.\n";
        maxHibak = 5;
    }

    Tippelo jatek(szo, maxHibak); 

    while (!jatek.nyert() && !jatek.vesztett()) {
        system("cls"); 

        jatek.jelenlegiMegjelenito();  
        cout << "Írd be a tipped, vagy nyomd meg a '?' jelet segítségért cserébe: \n";
        char tipp;
        cin >> tipp;

        if (cin.fail() || cin.peek() != '\n') {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Helytelen bemenet. Kérlek, írj be egyetlen karaktert.\n";
            continue;
        }

        if (tipp == '?') {
            jatek.hasznaljSegitseget(); 
        }
        else {
            jatek.tipp(tipp);  // Tipp beküldése
        }
    }

    if (jatek.nyert()) {
        cout << "Gratulálok! Sikeresen eltaláltad a szót: \033[0;32m" << szo << "\033[0m \n"; // a kitalálandó szó megjelenítése zöld betûszínnel (bash szín)
        pont++;
        return true;
    }
    else {
        system("cls");  
        jatek.jelenlegiMegjelenito();  
        cout << "Vége a játéknak! Ezt kellett volna kitalálnod: \033[0;31m" << szo << "\033[0m \n"; // a kitalálandó szó megjelenítése piros betûszínnel (bash szín)
        return false;
    }
}

int main() {
    int nehezsegiSzint;  
    int pont = 0;  
    bool helyes = false;
    char ujraKezd;

    setlocale(LC_ALL, ""); 

#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);  
#endif

    beolvasSzavak("szavak.txt");  
    cout << "Üdvözöllek az Akasztófa játékban ahol angol szavakat kell, hogy kitalálj! Készen állsz a kihívásra?" << endl;
    do {
        do {
            cout << "Válassz nehézségi szintet: 1. Könnyû, 2. Közepes, 3. Nehéz: ";
            cin >> nehezsegiSzint;

            
            if (cin.fail()) {
                cin.clear();  
                cin.ignore(numeric_limits<streamsize>::max(), '\n');  
                cout << "Helytelen bemenet. Kérlek, írj be egy számot.\n";  
            }
            else if (nehezsegiSzint == 1 || nehezsegiSzint == 2 || nehezsegiSzint == 3) {
                helyes = true;  
            }
            
            else {
                cout << "Helytelen választás. Kérlek próbáld újra.\n";  
            }
        } while (!helyes); 


        bool nyert = jatekInditas(nehezsegiSzint, pont);  

        cout << "Pontszámod: " << pont << "\n";  

        cout << "Szeretnél újra játszani? (y/n): \n";  
        cin >> ujraKezd;
    } while (tolower(ujraKezd) == 'y');  

    cout << "Köszönöm, hogy játszottál! A pontszámod: " << pont << "\n"; 

    return 0;  // Program vége
}
