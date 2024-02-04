#!/bin/bash
# Navigate to the script's directory
cd "$(dirname "$0")"/out

# Run tests
ctest

echo "Testing completed."
