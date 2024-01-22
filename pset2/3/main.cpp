#include "std_lib_facilities.h"

// a)
double discriminant(double a, double b, double c) {
    double disc = pow(b,2) - 4*a*c;
    return disc;
}

// fra oppgave 2
double inputDouble() {
    cout << "Skriv inn et desimaltall: ";
    double value;
    cin >> value;
    return value;
}

// b)
int printRealRoots(double a, double b, double c) {
    double disc = discriminant(a, b, c);
    if (disc < 0) {
        cout << "No real roots" << endl;
        return 0;
    }

    double x1 = (-b + pow(disc, 0.5)) / (2*a);
    double x2 = (-b - pow(disc, 0.5)) / (2*a);

    if (x1 == x2) {
        cout << "x = " << x1 << endl;
    } else {
        cout << "x1 = " << x1 << " and x2 = " << x2 << endl;
    }

    return 0;
}

// c) 
void solveQuadraticEquation() {
    double a = inputDouble();
    double b = inputDouble();
    double c = inputDouble();
    printRealRoots(a,b,c);
}

int main() {
    
    cout << "a)" << endl;
    cout << discriminant(2, 16, 2) << endl;

    cout << "b)" << endl;
    printRealRoots(8, 4, -1);

    cout << "c)" << endl;
    solveQuadraticEquation();

    return 0;
}

