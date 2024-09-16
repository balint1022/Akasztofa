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
            // Neh�z szintre, 4 hibalehet�s�g
            szintek = {
                "  +---+\n      |\n      |\n      |\n     ===",
                "  +---+\n  O   |\n      |\n      |\n     ===",
                "  +---+\n  O   |\n  |   |\n      |\n     ===",
                "  +---+\n  O   |\n /|\\  |\n      |\n     ===",
                "  +---+\n  O   |\n /|\\  |\n / \\  |\n     ==="
            };
        }
        else if (maxHibak == 5) {
            // K�zepes szintre, 5 hibalehet�s�g
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
            // K�nny� szintre, 6 hibalehet�s�g
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
            cout << szintek[hibak] << endl;  // A jelenlegi �llapot megjelen�t�se
        }
        else {
            cout << szintek.back() << endl;  // Ha a hib�k sz�ma meghaladja a maximumot, a v�g�llapot megjelen�t�se
        }
    }
};

// Tippel� oszt�ly
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
        tippeltSzo = string(szo.size(), '_');  // Kezdetben minden bet� hely�n al�h�z�s jelenik meg
        hibak = 0;
        maxHibak = maxTipp;
        elhasznaltSegitseg = false;
    }

    // Megvizsg�lja, hogy a j�t�kos kital�lta-e a sz�t
    bool nyert() {
        return tippeltSzo == kitalalandoSzo;
    }

    // Megvizsg�lja, hogy a j�t�kos vesztett-e
    bool vesztett() {
        return hibak >= maxHibak;
    }

    // A jelenlegi j�t�k�llapot megjelen�t�se
    void jelenlegiMegjelenito() {
        cout << "---------------------------------------\n";
        akasztofa.megjelenit(hibak);  
        cout << "\nSz�: " << tippeltSzo << "\n"; 
        cout << "Az eddig tippelt bet�k: ";
        for (char betu : tippeltBetuk) {
            cout << betu << " ";  
        }
        cout << "\nHib�k: " << hibak << "/" << maxHibak << "\n"; 
        cout << "---------------------------------------\n";
    }

    // Bet� tippel�se
    void tipp(char betu) {
        betu = tolower(betu); 

        if (!isalpha(betu)) {
            cout << "Csak bet�t tippelhetsz!\n";
            return;
        }

        if (find(tippeltBetuk.begin(), tippeltBetuk.end(), betu) != tippeltBetuk.end()) {
            cout << "Ezt a bet�t m�r tippelted.\n";
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
            hibak++;  // Ha a tipp nem volt helyes, a hibasz�m n�vel�se
        }
    }

    // Seg�ts�g haszn�lata
    void hasznaljSegitseget() {
        if (elhasznaltSegitseg) {
            cout << "M�r elhaszn�ltad a seg�ts�get!\n";
            return;
        }

        elhasznaltSegitseg = true;
        char segitseg = '_';
        for (int i = 0; i < kitalalandoSzo.size(); i++) {
            if (tippeltSzo[i] == '_') {
                segitseg = kitalalandoSzo[i];  // Az els� m�g nem kital�lt bet� felfed�se
                break;
            }
        }

        cout << "Seg�ts�g: A k�vetkez� bet�: " << segitseg << "\n";
        tipp(segitseg); 
    }
};

vector<string> szavak;  // Szavak t�rol�sa

// A szavak beolvas�sa f�jlb�l
void beolvasSzavak(const string& fileNev) {
    ifstream file(fileNev);

    if (!file) {
        cerr << "A f�jlt nem siker�lt megnyitni.\n";
        exit(1);  
    }

    string szo;
    while (file >> szo) {
        transform(szo.begin(), szo.end(), szo.begin(), ::tolower);  
        szavak.push_back(szo); 
    }

    file.close();
}

// V�letlenszer� kiv�laszt�s
string randomSzo() {
    srand(time(0));  
    int index = rand() % szavak.size();
    return szavak[index];  
}


bool jatekInditas(int nehezsegiSzint, int& pont) {
    string szo = randomSzo();  // V�letlenszer� sz� kiv�laszt�sa
    int maxHibak;

    // Neh�zs�gi szint be�ll�t�sa
    switch (nehezsegiSzint) {
    case 1:
        maxHibak = 6; // K�nny� szint
        break;
    case 2:
        maxHibak = 5; // K�zepes szint
        break;
    case 3:
        maxHibak = 4; // Neh�z szint
        break;
    default:
        cout << "Nem l�tez� neh�zs�gi szint, alap�rtelmezett neh�zs�gi szint a k�zepes.\n";
        maxHibak = 5;
    }

    Tippelo jatek(szo, maxHibak); 

    while (!jatek.nyert() && !jatek.vesztett()) {
        system("cls"); 

        jatek.jelenlegiMegjelenito();  
        cout << "�rd be a tipped, vagy nyomd meg a '?' jelet seg�ts�g�rt cser�be: \n";
        char tipp;
        cin >> tipp;

        if (cin.fail() || cin.peek() != '\n') {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Helytelen bemenet. K�rlek, �rj be egyetlen karaktert.\n";
            continue;
        }

        if (tipp == '?') {
            jatek.hasznaljSegitseget(); 
        }
        else {
            jatek.tipp(tipp);  // Tipp bek�ld�se
        }
    }

    if (jatek.nyert()) {
        cout << "Gratul�lok! Sikeresen eltal�ltad a sz�t: \033[0;32m" << szo << "\033[0m \n"; // a kital�land� sz� megjelen�t�se z�ld bet�sz�nnel (bash sz�n)
        pont++;
        return true;
    }
    else {
        system("cls");  
        jatek.jelenlegiMegjelenito();  
        cout << "V�ge a j�t�knak! Ezt kellett volna kital�lnod: \033[0;31m" << szo << "\033[0m \n"; // a kital�land� sz� megjelen�t�se piros bet�sz�nnel (bash sz�n)
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
    cout << "�dv�z�llek az Akaszt�fa j�t�kban ahol angol szavakat kell, hogy kital�lj! K�szen �llsz a kih�v�sra?" << endl;
    do {
        do {
            cout << "V�lassz neh�zs�gi szintet: 1. K�nny�, 2. K�zepes, 3. Neh�z: ";
            cin >> nehezsegiSzint;

            
            if (cin.fail()) {
                cin.clear();  
                cin.ignore(numeric_limits<streamsize>::max(), '\n');  
                cout << "Helytelen bemenet. K�rlek, �rj be egy sz�mot.\n";  
            }
            else if (nehezsegiSzint == 1 || nehezsegiSzint == 2 || nehezsegiSzint == 3) {
                helyes = true;  
            }
            
            else {
                cout << "Helytelen v�laszt�s. K�rlek pr�b�ld �jra.\n";  
            }
        } while (!helyes); 


        bool nyert = jatekInditas(nehezsegiSzint, pont);  

        cout << "Pontsz�mod: " << pont << "\n";  

        cout << "Szeretn�l �jra j�tszani? (y/n): \n";  
        cin >> ujraKezd;
    } while (tolower(ujraKezd) == 'y');  

    cout << "K�sz�n�m, hogy j�tszott�l! A pontsz�mod: " << pont << "\n"; 

    return 0;  // Program v�ge
}
