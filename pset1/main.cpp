// This code is part of problem set 1 in the TDT4102 spring 2024 course at NTNU.

#include "std_lib_facilities.h"

// a)
int maxOfTwo(int a, int b) {
    if (a > b) {
        cout << "A is greater than B" << endl;
        return a;
    } else {
        cout << "B is greater than or equal to A" << endl;
        return b;
    }
}

// c)
int fibonacci(int n) {
    int a = 0;
    int b = 1;
    cout << "Fibonacci numbers:" << endl;
    for (int x = 1; x < n + 1; x++) {
        cout << x << " " << b << endl;
        int temp = b;
        b += a;
        a = temp;
    }
    cout << "----" << endl;
    return b;
}

// d)
int squareNumberSim(int n) {
    int totalSum = 0;
    for (int i = 1; i < n + 1; i++) {
        totalSum += i * i;
        cout << i*i << endl;
    }
    cout << totalSum << endl;
    return totalSum;
}

// e)
void triangleNumbersBelow(int n) {
    int acc = 1;
    int num = 2;
    cout << "Triangle numbers below " << n << ":" << endl;
    while (acc < n) {
        cout << acc << endl;
        acc += num;
        num += 1;
    }
    cout << endl;
}

// f)
bool isPrime(int n) {
    for (int j = 2; j < n; j++) {
        if (n % j == 0) {
            return false;
        }
    }
    return true;
}

// g)
void naivePrimeNumberSearch(int n) {
    for (int number = 2; number < n; number++) {
        if (isPrime(number)) {
            cout << number << " is a prime" << endl;
        }
    }
}

// h)
void inputAndPrintNameAndAge(void) {

    cout << "Skriv inn et navn: ";
    string name;
    getline(cin, name);
    
    cout << "Skriv inn alderen til " << name << ": ";
    string age;
    getline(cin, age);

    cout << name << " er " << age << " aar gammel." << endl;
}

int main() {
    cout << "Oppgave a)" << endl;
    cout << maxOfTwo(5, 6) << endl;
    cout << endl;

    cout << "Oppgave c)" << endl;
    cout << fibonacci(5) << endl;
    cout << endl;

    cout << "Oppgave d)" << endl;
    cout << squareNumberSim(5) << endl;
    cout << endl;

    cout << "Oppgave e)" << endl;
    triangleNumbersBelow(5);

    cout << "Oppgave f)" << endl;
    cout << "13 " << isPrime(13) << endl;
    cout << "4 " << isPrime(4) << endl;
    cout << endl;

    cout << "Oppgave g)" << endl;
    naivePrimeNumberSearch(20);

    cout << "Oppgave h)" << endl;
    inputAndPrintNameAndAge();
} 
