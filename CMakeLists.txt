cmake_minimum_required(VERSION 3.0)

project (CPPDIGRAPH CXX)

set (CMAKE_CXX_STANDARD 11)
set (CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -std=c++11" )
set (CMAKE_BUILD_TYPE Debug)

add_subdirectory (src)
add_subdirectory (test)

enable_testing()

# Create ctags file for simple code indexing.
# add_custom_command (TARGET do_tests.out PRE_BUILD COMMAND ctags -f cppdigraph.ctags -R .)

enable_testing ()
add_test (NAME MyTest COMMAND Test)
