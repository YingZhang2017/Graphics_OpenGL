#!/bin/bash
# clean and rebuild

bash clear.sh

echo "Compile..."
make -f Makefile

echo "Open demo..."
./tessellation_demo
