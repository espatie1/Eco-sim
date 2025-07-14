#!/usr/bin/env bash
# build_debug.sh — configure, build and run eco‑sim in Debug mode
set -e

ROOT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
BUILD_DIR="$ROOT_DIR/build"

echo ">>> Configuring Debug build..."
cmake -S "$ROOT_DIR" -B "$BUILD_DIR" -DCMAKE_BUILD_TYPE=Debug

echo ">>> Building..."
cmake --build "$BUILD_DIR" --config Debug

echo ">>> Running eco‑sim..."
"$BUILD_DIR/eco-sim"
