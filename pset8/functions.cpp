#include "functions.h"

void fillInFibonacciNumbers(int* result, int length) {
    if(length > 0) result[0] = 0; 
    if(length > 1) result[1] = 1;
    for(int i = 2; i < length; i++) {
        result[i] = result[i - 1] + result[i - 2];
    }
}

void printArray(int* arr, int length) {
    for(int i = 0; i < length; i++){
        std::cout << arr[i] << std::endl;
    }
}

void createFibonacci() {
    int length;
    std::cout << "How many numbers do you want to generate? ";
    std::cin >> length;

    int* fibonacciArray = new int[length];
    fillInFibonacciNumbers(fibonacciArray, length);
    printArray(fibonacciArray, length);

    delete[] fibonacciArray;
}