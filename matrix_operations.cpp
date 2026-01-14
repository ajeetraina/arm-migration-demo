#include "matrix_operations.h"
#include <iostream>
#include <random>
#include <chrono>
#include <stdexcept>
#include <arm_neon.h>  // ARM NEON intrinsics

Matrix::Matrix(size_t r, size_t c) : rows(r), cols(c) {
    data.resize(rows, std::vector<double>(cols, 0.0));
}

void Matrix::randomize() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, 10.0);

    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < cols; j++) {
            data[i][j] = dis(gen);
        }
    }
}

void Matrix::print() const {
    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < cols; j++) {
            std::cout << data[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

Matrix Matrix::multiply(const Matrix& other) const {
    if (cols != other.rows) {
        throw std::runtime_error("Invalid matrix dimensions for multiplication");
    }

    Matrix result(rows, other.cols);

    // ARM64 optimized using NEON for double-precision
    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < other.cols; j++) {
            // Initialize sum vectors to zero (NEON processes 2 doubles at a time)
            float64x2_t sum_vec1 = vdupq_n_f64(0.0);
            float64x2_t sum_vec2 = vdupq_n_f64(0.0);
            size_t k = 0;

            // Process 4 elements at a time using two NEON vectors (2x2 doubles)
            for (; k + 3 < cols; k += 4) {
                // Load first 2 elements from matrix A
                float64x2_t a_vec1 = vld1q_f64(&data[i][k]);
                
                // Load second 2 elements from matrix A  
                float64x2_t a_vec2 = vld1q_f64(&data[i][k + 2]);
                
                // Manually create vectors for matrix B elements
                double b_arr1[2] = {other.data[k][j], other.data[k + 1][j]};
                double b_arr2[2] = {other.data[k + 2][j], other.data[k + 3][j]};
                
                float64x2_t b_vec1 = vld1q_f64(b_arr1);
                float64x2_t b_vec2 = vld1q_f64(b_arr2);
                
                // Multiply and accumulate
                sum_vec1 = vaddq_f64(sum_vec1, vmulq_f64(a_vec1, b_vec1));
                sum_vec2 = vaddq_f64(sum_vec2, vmulq_f64(a_vec2, b_vec2));
            }

            // Sum the results from both NEON vectors
            float64x2_t final_sum = vaddq_f64(sum_vec1, sum_vec2);
            
            // Extract and sum the elements horizontally
            double sum_arr[2];
            vst1q_f64(sum_arr, final_sum);
            double sum = sum_arr[0] + sum_arr[1];

            // Handle remaining elements
            for (; k < cols; k++) {
                sum += data[i][k] * other.data[k][j];
            }

            result.data[i][j] = sum;
        }
    }

    return result;
}