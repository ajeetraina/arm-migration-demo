FROM ubuntu:22.04

# Set environment to avoid interactive prompts during package installation
ENV DEBIAN_FRONTEND=noninteractive

# Update package lists and install build tools
RUN apt-get update && apt-get install -y \
    build-essential \
    g++ \
    make \
    && apt-get clean \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app
COPY *.h *.cpp ./

# Use ARM-optimized NEON intrinsics instead of AVX2
# -march=armv8-a+simd enables NEON SIMD instructions
# -mcpu=native optimizes for the specific ARM processor if available
RUN g++ -O3 -march=armv8-a+simd -mcpu=generic -o benchmark \
    main.cpp \
    matrix_operations.cpp \
    -std=c++11

CMD ["./benchmark"]