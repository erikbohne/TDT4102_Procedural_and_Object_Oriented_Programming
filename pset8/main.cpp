#include "functions.h"
#include "Matrix.h"
#include "dummy.h"

int main() {
    // Task 1
    // createFibonacci();

    // Task 2 
    Matrix I{5, 5};
    std::cout << I;

    // Task 3
    dummyTest();

    // Task 4 and 5
    Matrix A{4, 5};
    Matrix B{4, 5};
    A += B;
    std::cout << A;
    Matrix C{4, 5};
    C = A + B;
     std::cout << C;

    return 0;
}
