#include "Matrix.h"

Matrix::Matrix(int nRows, int nColumns) : rows(nRows), columns(nColumns) {
    assert(rows > 0 && columns > 0);
    matrix = new double[rows*columns];
    std::fill_n(matrix, rows * columns, 0.0);
}

Matrix::Matrix(int nRows) : rows(nRows), columns(nRows) {
    for (int i = 0; i < rows; ++i) {
        this->set(i, i, 1.0);
    }
}

Matrix::~Matrix() {
    delete[] matrix;
}

double Matrix::get(int row, int col) const {
    return matrix[row*columns+col];
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

Matrix::Matrix(const Matrix & rhs) : rows(rhs.rows), columns(rhs.columns) {
    matrix = new double[rows*columns];
    for (int i = 0; i < rows * columns; i++) {
        matrix[i] = rhs.matrix[i];
    }
}

Matrix& Matrix::operator=(const Matrix& rhs) {
    if (this != &rhs) {
        delete[] matrix;
        rows = rhs.rows;
        columns = rhs.columns;
        matrix = new double[rows*columns];
        for (int i = 0; i < rows * columns; i++) {
            matrix[i] = rhs.matrix[i];
        }
    }
    return *this;
}

Matrix& Matrix::operator+=(const Matrix& rhs) {
    if (rows != rhs.rows || columns != rhs.columns) {
        return *this;
    }
    for (int i = 0; i < rows * columns; i++) {
        matrix[i] = matrix[i] + rhs.matrix[i];
    }
    return *this;
}

Matrix& Matrix::operator+(const Matrix& rhs) const {
    Matrix sum = *this; // kaller kopikonstruktøren automatisk
    sum += rhs;
    return sum;
}