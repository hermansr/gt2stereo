#!/bin/sh

# stop on error
set -e

# remove all temporary files from previous builds
rm -rf build build-win32 build-win64

if [[ $1 = clean ]] ; then
  exit 0
fi

# build using native compiler
cmake -S . -B build
cmake --build build
if [[ $1 = install ]] ; then
  cmake --install build
fi

if [[ $1 = cross ]] ; then
  # build using 32-bit MinGW-w64 GCC cross-compiler
  cmake -S . -B build-win32 --toolchain CMake/i686-w64-mingw32.cmake -D MyGen_DIR=build
  cmake --build build-win32

  # build using 64-bit MinGW-w64 GCC cross-compiler
  cmake -S . -B build-win64 --toolchain CMake/x86_64-w64-mingw32.cmake -D MyGen_DIR=build
  cmake --build build-win64
fi
