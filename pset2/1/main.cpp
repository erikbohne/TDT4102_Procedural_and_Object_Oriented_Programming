#include "std_lib_facilities.h"

// c
int inputInteger(void) {
    cout << "Skriv inn et tall: ";
    int integer;
    cin >> integer;
    return integer;
}

// b
void inputAndPrintInteger(void) {
    int integer = inputInteger();
    cout << "Du skrev: " << integer << endl;
}

// d
void inputIntegersAndPrintSum(void) {
    int x = inputInteger();
    int y = inputInteger();
    cout << "Summen av tallene: " << x + y << endl; 
}

// e) Valgte å bruke inputInteger() siden den spør om en int og returnerer denne, inputAndPrintInteger() returnerer ingenting

// f)
void isOdd(void) {
    for (int i = 1; i < 16; i++) {
        cout << i << " er et oddetall? " << ((i % 2 != 0) ? "true" : "false") << endl;
    }
}

int main() {

    // a
    cout << "Velg funksjon:" << endl;
    cout << "0) Avslutt" << endl;
    cout << "1) Skriv inn tall" << endl;
    cout << "2) TODO" << endl;
    cout << "3) TODO" << endl;
    cout << "Angi valg (0-3)" << endl;

    int choice;
    cin >> choice;

    switch(choice) {
        case 0: 
            cout << "Avslutter..." << endl;
            break;
        case 1: 
            inputAndPrintInteger();
            break;
        case 2: 
            inputIntegersAndPrintSum();
            break;
        case 3: 
            isOdd();
            break;
        default:
            cout << "Valget ditt er ikke tilgengelig.";
    }

    return 0;
}