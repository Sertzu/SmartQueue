#!/bin/bash
# Navigate to the script's directory
cd "$(dirname "$0")"

# Create and navigate to the build directory
mkdir -p out
cd out

# Configure and build the project
cmake ..
make

echo "Build completed."
