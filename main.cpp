#include "matrix_operations.h"
#include <iostream>

int main() {
    std::cout << "AVX2 Matrix Multiplication Benchmark" << std::endl;
    std::cout << "=====================================" << std::endl;
    std::cout << "This code uses x86-64 AVX2 intrinsics" << std::endl;
    std::cout << "and will NOT compile on ARM without migration." << std::endl;

    benchmark_matrix_ops();

    return 0;
}
