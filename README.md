# ARM64 Migration Demo - Matrix Multiplication with AVX2

This repository contains a sample C++ application that demonstrates ARM64 migration using Docker MCP Toolkit and the Arm MCP Server. The code is intentionally written with x86-specific AVX2 intrinsics to showcase automated migration workflows.

## What's in This Repository

- **matrix_operations.h/cpp** - Matrix multiplication implementation using AVX2 intrinsics
- **main.cpp** - Benchmark driver
- **Dockerfile** - CentOS 6 based build (x86-only, with EOL mirror workarounds)

## The Migration Challenge

This code won't work on ARM without modification:

1. \`centos:6\` base image has no ARM64 support
2. \`-mavx2\` compiler flag is x86-specific
3. All \`_mm256_*\` intrinsics are Intel/AMD-only
4. AVX2 processes 4 doubles per operation; ARM NEON processes 2

## Prerequisites

Before starting the migration:

- Docker Desktop with MCP Toolkit enabled
- VS Code with GitHub Copilot
- Arm MCP Server, GitHub MCP Server, and Sequential Thinking MCP Server installed
- Git configured with your GitHub credentials

## How to Use This Demo

### Step 1: Clone This Repository

\`\`\`bash
git clone https://github.com/YOUR_USERNAME/arm-migration-demo.git
cd arm-migration-demo
\`\`\`

### Step 2: Open in VS Code

\`\`\`bash
code .
\`\`\`

### Step 3: Configure MCP Servers

Create \`.vscode/settings.json\`:

\`\`\`json
{
  "github.copilot.chat.mcp.servers": {
    "arm-mcp": {
      "command": "docker",
      "args": ["mcp", "connect", "arm"]
    },
    "github-mcp": {
      "command": "docker",
      "args": ["mcp", "connect", "github"]
    },
    "sequential-thinking": {
      "command": "docker",
      "args": ["mcp", "connect", "sequential-thinking"]
    }
  }
}
\`\`\`

### Step 4: Run the Migration

Open GitHub Copilot Chat in VS Code and paste this prompt:

\`\`\`
You are an ARM64 migration assistant using Docker MCP Toolkit.

WORKFLOW:
1. Image Analysis: Use check_image to verify base image ARM64 support
2. Code Scanning: Run migrate_ease_scan to find x86-specific code
3. Intrinsic Conversion: Use knowledge_base_search to find NEON equivalents
4. Performance Analysis: Use mca to predict ARM vs x86 performance
5. Pull Request: Create PR with all changes using GitHub MCP

CONVERSION RULES:
- AVX2 (256-bit) → NEON (128-bit): process half the data per operation
- __m256d → float64x2_t
- _mm256_loadu_pd() → vld1q_f64()
- _mm256_add_pd() → vaddq_f64()
- _mm256_mul_pd() → vmulq_f64()
- NEON lane indices must be compile-time constants

DOCKERFILE UPDATES:
- centos:6 → rockylinux:9 (ARM64 support)
- Remove -mavx2, add -march=armv8-a+simd
- Update package manager (yum → dnf)

Now migrate this application to ARM64. Scan the code, convert intrinsics, 
update the Dockerfile, predict performance, and create a pull request.
\`\`\`

### Step 5: Review the Migration

GitHub Copilot will:
1. Analyze the Docker image architecture
2. Scan code for x86 dependencies
3. Convert AVX2 intrinsics to ARM NEON
4. Update the Dockerfile to Rocky Linux 9
5. Predict performance improvements
6. Create a pull request with all changes

### Step 6: Test on ARM

Once the PR is created, test on an ARM system:

\`\`\`bash
# On Apple Silicon Mac or AWS Graviton instance
git fetch origin feature/arm64-migration
git checkout feature/arm64-migration

# Build and run
g++ -O2 -march=native -o benchmark \\
    matrix_operations.cpp main.cpp -std=c++11

./benchmark
\`\`\`

## Expected Results

- **Performance**: ~16% faster on AWS Graviton3 vs x86 Skylake
- **Cost Savings**: ~32% reduction on AWS EC2 (Graviton vs x86 instances)
- **Migration Time**: 5-10 minutes vs 6-8 hours manual migration

## What Gets Changed

The automated migration will:

1. **Dockerfile**:
   - Base image: \`centos:6\` → \`rockylinux:9\`
   - Compiler flags: \`-mavx2\` → \`-march=armv8-a+simd\`
   - Package manager: \`yum\` → \`dnf\`

2. **matrix_operations.cpp**:
   - Headers: \`<immintrin.h>\` → \`<arm_neon.h>\`
   - All AVX2 intrinsics → NEON equivalents
   - Loop adjustments for 128-bit vector width
   - Horizontal reduction logic rewritten

## Learn More

- [Docker MCP Toolkit Documentation](https://www.docker.com/products/mcp-catalog-and-toolkit/)
- [Arm MCP Server GitHub](https://github.com/arm/mcp)
- [AWS Graviton Performance Guide](https://aws.amazon.com/ec2/graviton/)
- [ARM NEON Intrinsics Reference](https://developer.arm.com/architectures/instruction-sets/intrinsics/)

## License

MIT License - Feel free to use this code for learning and testing ARM migration workflows.
