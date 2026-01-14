#include <iostream>
#include <chrono>
#include "matrix_operations.h"

int main() {
    const size_t N = 512;
    
    std::cout << "ARM64 Matrix Multiplication Demo" << std::endl;
    std::cout << "Matrix size: " << N << "x" << N << std::endl;

    Matrix a(N, N), b(N, N);
    
    std::cout << "Initializing matrices..." << std::endl;
    a.randomize();
    b.randomize();

    std::cout << "Starting matrix multiplication..." << std::endl;
    auto start = std::chrono::high_resolution_clock::now();
    
    Matrix c = a.multiply(b);
    
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    
    std::cout << "Matrix multiplication completed in: " << duration.count() << " ms" << std::endl;
    std::cout << "Result matrix dimensions: " << c.getRows() << "x" << c.getCols() << std::endl;

    return 0;
}