#ifndef MATRIX_OPERATIONS_H
#define MATRIX_OPERATIONS_H

#include <vector>

class Matrix {
public:
    Matrix(size_t rows, size_t cols);
    void randomize();
    Matrix multiply(const Matrix& other) const;
    double sum() const;

private:
    size_t rows;
    size_t cols;
    std::vector<std::vector<double>> data;
};

void benchmark_matrix_ops();

#endif // MATRIX_OPERATIONS_H
