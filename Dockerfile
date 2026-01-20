# ARM64-Optimized Multi-Architecture Dockerfile
FROM ubuntu:22.04

# Set environment to avoid interactive prompts during package installation
ENV DEBIAN_FRONTEND=noninteractive

# Set ARM-optimized build environment
ENV CC=gcc
ENV CXX=g++

# Update package lists and install build tools
RUN apt-get update && apt-get install -y \
    build-essential \
    g++ \
    make \
    && apt-get clean \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app
COPY *.h *.cpp ./

# ARM64-Optimized compilation with advanced performance flags
# -O3: Maximum optimization level
# -march=armv8-a+simd: Enable ARM NEON SIMD instructions for vectorization
# -mcpu=generic: Optimize for general ARM64 processors 
# -flto=auto: Link-time optimization with parallel processing (major performance boost)
# -ffast-math: Aggressive math optimizations for improved performance
# -funroll-loops: Unroll loops for better instruction-level parallelism
# -ftree-vectorize: Enable automatic vectorization
# -fomit-frame-pointer: Reduce function call overhead
RUN g++ -O3 -march=armv8-a+simd -mcpu=generic -flto=auto \
    -ffast-math -funroll-loops -ftree-vectorize -fomit-frame-pointer \
    -o benchmark \
    main.cpp \
    matrix_operations.cpp \
    -std=c++11

CMD ["./benchmark"]