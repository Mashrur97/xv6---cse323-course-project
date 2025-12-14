#!/bin/bash

# Go to xv6 folder (optional if already there)
cd "$(dirname "$0")"

# Clean old build (optional)
make clean

# Build xv6
make

# Run xv6 in QEMU
make qemu
