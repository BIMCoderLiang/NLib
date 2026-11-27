#!/usr/bin/env sh
# SPDX-FileCopyrightText: Copyright (c) 2026 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
# SPDX-License-Identifier: Apache-2.0
#
# Build NLib on Linux / macOS.
#
# Usage:
#   chmod +x build.sh      (first time only)
#   ./build.sh [Release|Debug|RelWithDebInfo|MinSizeRel]
#
# Default build type is Release.

set -eu

cd "$(dirname "$0")"

echo "=========================================================="
echo "  NLib - CMake build (Linux / macOS)"
echo "=========================================================="
echo

if ! command -v cmake >/dev/null 2>&1; then
    echo "[ERROR] 'cmake' was not found. Install CMake and retry." >&2
    exit 1
fi

BUILD_TYPE="${1:-Release}"

echo "[1/2] Configuring ($BUILD_TYPE)..."
cmake -S . -B build -DCMAKE_BUILD_TYPE="$BUILD_TYPE"

echo
echo "[2/2] Building..."
cmake --build build --parallel

echo
echo "=========================================================="
echo "  Build succeeded: build/lib/libNLib.a"
echo "=========================================================="
