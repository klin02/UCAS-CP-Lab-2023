#!/bin/bash

cd ../deps/antlr4-runtime
rm -rf build
mkdir build
cd build
cmake ..
make -j8
cd ../../../
