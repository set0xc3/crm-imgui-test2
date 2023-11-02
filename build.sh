#!/bin/bash

export CC="ccache /usr/bin/clang"
export CXX="ccache /usr/bin/clang++"

cmake -B build && cmake --build build -j $(nproc) && cmake --build build --target run_crm
