#!/usr/bin/sh

set -xe

mkdir build -p
cd build
cmake ..
make
