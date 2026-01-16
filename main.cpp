#include "matrix_operations.h"
#include <iostream>

int main() {
    std::cout << "Cross-Architecture Matrix Multiplication Benchmark" << std::endl;
    std::cout << "=================================================" << std::endl;
    std::cout << "This code uses architecture-specific SIMD optimizations:" << std::endl;
#ifdef __aarch64__
    std::cout << "- ARM64: NEON intrinsics for optimal performance" << std::endl;
#elif defined(__x86_64__)
    std::cout << "- x86-64: AVX2 intrinsics for optimal performance" << std::endl;
#else
    std::cout << "- Generic: Standard C++ implementation" << std::endl;
#endif

    benchmark_matrix_ops();

    return 0;
}