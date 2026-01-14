# ARM64-compatible base image
FROM rockylinux:9

# Install build essentials using dnf (not yum)
RUN dnf update -y && \
    dnf groupinstall -y "Development Tools" && \
    dnf install -y gcc-c++ cmake make && \
    dnf clean all

# Set working directory
WORKDIR /app

# Copy source files
COPY . .

# Compile with ARM64 optimizations
RUN g++ -std=c++17 -march=armv8-a+simd -O3 -o matrix_demo \
    main.cpp matrix_operations.cpp

# Run the application
CMD ["./matrix_demo"]