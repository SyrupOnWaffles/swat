#!/bin/bash
rm -r build
mkdir build
cd build
cmake ..
make
cd ..
./build/swat
rm -r build
