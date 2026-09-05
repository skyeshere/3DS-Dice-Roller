#!/usr/bin/env bash

set -e

if [ -z "$DEVKITPRO" ]; then
  echo "DEVKITPRO not set"
  exit 1
fi

BUILD_DIR=build

mkdir -p $BUILD_DIR
cd $BUILD_DIR

cmake .. \
  -DCMAKE_TOOLCHAIN_FILE=$DEVKITPRO/cmake/3DS.cmake

make -j$(nproc)