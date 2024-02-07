#include "std_lib_facilities.h"
#include "tests.h"
#include "mastermind.h"
#include "masterVisual.h"

int main() {

    cout << "0) Avslutt" << endl;
    cout << "1) testCallByValue()" << endl;
    cout << "2) testCallByValueRef()" << endl;
    cout << "3) testSwapNumbers()" << endl;
    cout << "4) testStudentStruct()" << endl;
    cout << "5) testRandomizeString()" << endl;
    cout << "6) testString()" << endl;
    cout << "7) testReadInputToString()" << endl;
    cout << "8) testCountChar()" << endl;
    cout << "9) Play Mastermind" << endl;
    cout << "10) Play Visual Mastermind" << endl;
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
        case 2:
            testCallByReference();
            break;
        case 3:
            testSwapNumbers();
            break;
        case 4:
            testStudentStruct();
            break;
        case 5:
            testRandomizeString();
            break;
        case 6:
            testString();
            break;
        case 7:
            testReadInputToString();
            break;
        case 8:
            testCountChar();
            break;
        case 9:
            playMastermind();
            break;
        case 10:
            playMastermindVisual();
            break;
        default:
            cout << "Ugyldig input" << endl;
            break;
    }
    return 0;
}

