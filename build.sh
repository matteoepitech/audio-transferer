#!/usr/bin/env bash

set -euo pipefail
: "${VCPKG_ROOT:?VCPKG_ROOT must be set to your vcpkg checkout path}"

# To change depending on your configuration.
export CC=/usr/bin/clang
export CXX=/usr/bin/clang++

rm -rf ./build/
mkdir -p build
cmake -B build -S . -DCMAKE_TOOLCHAIN_FILE="$VCPKG_ROOT/scripts/buildsystems/vcpkg.cmake"
cmake --build build
mv build/audiotr .
