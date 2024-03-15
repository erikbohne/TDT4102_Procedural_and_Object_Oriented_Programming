#pragma once
#include <cassert>
#include <iostream>

class Matrix
{
private:
    int rows;
    int columns;
    double* matrix;
    double* identityMatrix;

public:
    Matrix(int nRows, int nColumns);
    explicit Matrix(int nRows);
    ~Matrix();

    double get(int row, int col) const;
    void set(int row, int col, double value);

    int getRows() const;
    int getColumns() const;

    friend std::ostream& operator<<(std::ostream& os, const Matrix& m);

    Matrix(const Matrix & rhs);

    Matrix& operator=(const Matrix& rhs);
};