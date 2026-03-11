#/usr/bin/env bash

rm -rf ./build/
mkdir -p build
cmake -B build -S . -DCMAKE_TOOLCHAIN_FILE=$VCPKG_ROOT/scripts/buildsystems/vcpkg.cmake
cmake --build build
mv build/audiotr .
