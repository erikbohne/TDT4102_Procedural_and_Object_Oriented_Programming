#include "Matrix.h"

Matrix::Matrix(int nRows, int nColumns) : rows(nRows), columns(nColumns) {
    assert(rows >= 0);
    assert(columns >= 0);
    matrix = new double[rows*columns];
    identityMatrix = nullptr;
}

Matrix::Matrix(int nRows) : rows(nRows), columns(nRows) {
    assert(rows >= 0);
    identityMatrix = new double[rows*rows];
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < rows; ++j) {
            identityMatrix[i * rows + j] = (i == j) ? 1.0 : 0.0;
        }
    }
    matrix = nullptr;
}

Matrix::~Matrix() {
    if (matrix != nullptr) {
        delete[] matrix;
    }
    if (identityMatrix != nullptr) {
        delete[] identityMatrix;
    }
}

double Matrix::get(int row, int col) const {
    if (matrix != nullptr) {
        return matrix[row * columns + col];
    }
    if (identityMatrix != nullptr) {
        return identityMatrix[row * columns + col];
    }
    return NULL;
}

void Matrix::set(int row, int col, double value) {
    matrix[row*columns+col] = value;
}

int Matrix::getRows() const {
    return rows;
}

int Matrix::getColumns() const {
    return columns;
}

std::ostream& operator<<(std::ostream& os, const Matrix& m) {
    for(int r = 0; r < m.getRows(); r++){
        for(int c = 0; c < m.getColumns(); c++) {
            os << m.get(r, c) << " ";
        }
        os << std::endl;
    }
    return os;
}
