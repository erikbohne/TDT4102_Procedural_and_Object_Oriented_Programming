#include "std_lib_facilities.h"
#include "tests.h"

int main() {

    cout << "0) Avslutt" << endl;
    cout << "1) testCallByValue()" << endl;

    cout << "Hvilken funkjson vil du teste? ";
    int num;
    cin >> num;

    switch (num) {
        case 0:
            cout << "Avslutter..." << endl;
            break;
        case 1:
            testCallByValue();
            break;
        default:
            cout << "Ugyldig input" << endl;
            break;
    }
    return 0;
}

