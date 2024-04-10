#include "Stopwatch.h"
#include <vector>
#include <iostream>

// Utdelt kode til oppgave 3

void setDiagonalValue(std::vector<std::vector<double>>& matrix, double newValue) {
    int minDimension = std::min(matrix.size(), matrix.empty() ? 0 : matrix[0].size());
    for (int i = 0; i < minDimension; ++i) {
        matrix[i][i] = newValue;
    }
}


double sumMatrix(const std::vector<std::vector<double>>& matrix) {
    double sum = 0.0;
    for (const auto& row : matrix) {
        for (double value : row) {
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
        column.resize(matrixSize, 0.0);
        matrix.push_back(column);
    }

    // Set all elements on the diagonal to 0.41
    setDiagonalValue(matrix, 0.41);
    
    // Sum all elements in the matrix
    double total = sumMatrix(matrix);

    double coolerNumber = total + 2;
    std::cout << "TDT" << coolerNumber << std::endl;
}