#include "std_lib_facilities.h"

// a)
unsigned int printSum() {
    int n;
    cout << "How many integers you want to sum? ";
    cin >> n;

    unsigned int sum = 0;
    for(int i = 0; i < n; i++) {
        sum += i;
    }
    cout << "sum of " << n << " first ingtegers is " << sum << endl;

    return sum;
}

// b)
void printSumWhileNotZero() {
    unsigned int sum = 1;
    do {
        sum = printSum();
    } while(sum != 0);
}

// c) Bruker for løkke i oppgave a) siden vi skal gjennom løkken én gang med et bestemt antall iterasjoner
// i oppgave b b) brukes do while løkke siden vi skal gjennomføre noe minst en gang, og fortsette så lenge 
// uttrykket i while fortsatt er sann.

// d)
double inputDouble() {
    cout << "Skriv inn et desimaltall: ";
    double value;
    cin >> value;
    return value;
}

// e)
void convertToEuroes() {
    double NOK;
    do {
        cout << "Hvor mye NOK har du? ";
        cin >> NOK;
    } while (NOK < 0);

    double rate = 11.44;
    cout << "Du får " << (NOK / rate) << "€" << endl;
}

// f) Her bruker vi datatypen double siden vi har flytall og ikke bare heltall. Om vi hadde brukt inputInteger hadde vi fått feil 
// siden TODO

// g)
void printTable() {
    int H, W;
    do {
        cout << "Enter height: ";
        cin >> H;
        cout << "Enter width: ";
        cin >> W;
    } while(H <= 0 || W <= 0);

    int largestNumber = H * W;
    int numberWidth = to_string(largestNumber).length();

    int number = 1;
    for(int h = 0; h < H; h++) {
        for(int w = 0; w < W; w++) {
            cout << setw(numberWidth + 2) << number;
            number++;
        }
        cout << endl;
    }
}

int main() {

    cout << "a)" << endl;
    unsigned int sum = printSum();

    cout << "b)" << endl;
    printSumWhileNotZero();

    cout << "d)" << endl;
    cout << "Du skrev: " << inputDouble() << endl;

    cout << "e)" << endl;
    convertToEuroes();

    cout << "g)" << endl;
    printTable();    

    return 0;
}