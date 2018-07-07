# cppdigraph  [![Build Status](https://travis-ci.org/tsmanner/cppdigraph.svg?branch=master)](https://travis-ci.org/tsmanner/cppdigraph)
Implementation of a directed graph container in C++

## Building

### With Make
    cmake . && make

### With Ninja
    cmake . -DCMAKE_MAKE_PROGRAM=$(which ninja) && ninja

### Produce Dependency Graph (With PNG Image)
    cmake . --graphviz=dependencygraph.gv
    dot -Tpng dependencygraph.gv -o dependencygraph.png
