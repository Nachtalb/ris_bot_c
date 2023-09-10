#!/usr/bin/sh

set -xe

mkdir build && cd build
cmake ..
make
