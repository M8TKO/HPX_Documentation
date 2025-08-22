#!/usr/bin/env bash
set -euo pipefail

# Absolute path to HPX installed by Spack
HPX_DIR="/home/petricic1/spack/opt/spack/linux-skylake/hpx-1.11.0-uuk46vfdso4eqdyhqdipmssmpb45trka/lib/cmake/HPX"

# Usage:
#   ./rebuild.sh              -> just rebuild
#   ./rebuild.sh --run        -> rebuild and run ./build/my_hpx_program
#   ./rebuild.sh --run args…  -> rebuild and run with arguments

TARGET="three_vectors_program"

if [[ "${1:-}" == "--run" ]]; then
    shift
    echo "Running $TARGET $*"
    ./build/$TARGET "$@"
    exit 0
fi
# Reconfigure & build
rm -rf build
cmake -S . -B build -DHPX_DIR="$HPX_DIR" -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
cmake --build build -j

# Run if requested
if [[ "${1:-}" == "--buildrun" ]]; then
    shift
    echo "Running $TARGET $*"
    ./build/$TARGET "$@"
fi
