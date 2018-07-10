# cppdigraph  [![Build Status](https://travis-ci.org/tsmanner/cppdigraph.svg?branch=master)](https://travis-ci.org/tsmanner/cppdigraph)
Implementation of a directed graph container in C++

## Building

### As a User
To build a single `.so` library file for `cppdigraph`:

    mkdir build
    cd build
    cmake ../src
    make

### As a Developer
To build the library and test environment for `cppdigraph`:

    mkdir build
    cd build
    cmake ..
    make

Once the test environment is compiled, you can run them with `ctest`.  Tests are registered in `test/CMakeLists.txt` using the `add_test` directive.  To see the stdout of the tests as they run, use `ctest -V`.
