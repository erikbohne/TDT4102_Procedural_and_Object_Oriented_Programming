#include "Stopwatch.h"
#include <vector>
#include <iostream>

// Utdelt kode til oppgave 3

void setDiagonalValue(std::vector<std::vector<double>>& matrix, double newValue){
    for (int row = 0; row < matrix.size(); row++){
        for (int col = 0; col < matrix.size(); col++){
            bool isDiagonal = (row == col);
            if (isDiagonal){
                matrix.at(row).at(col) = newValue;
            }
        }
    }
}

double sumMatrix(std::vector<std::vector<double>> matrix){
    double sum;
    for (int col = 0; col < matrix.size(); col++){
        for (int row = 0; row < matrix.size(); row++){
            double value = matrix.at(row).at(col);
            sum += value;            
        }
    }
    return sum;
}

void optimizationTask() {
    
    const int matrixSize = 10000;

    // Create a matrix with zeros
    std::vector<std::vector<double>> matrix;
    
    for (int i = 0; i < matrixSize; i++){
        std::vector<double> column;
        for (int j = 0; j < matrixSize; j++){
            column.push_back(0.0);
        }
        matrix.push_back(column);
    }

    // Set all elements on the diagonal to 0.41
    setDiagonalValue(matrix, 0.41);
    
    // Sum all elements in the matrix
    double total = sumMatrix(matrix);

    double coolerNumber = total + 2;
    std::cout << "TDT" << coolerNumber << std::endl;
}