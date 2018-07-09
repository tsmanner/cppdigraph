cmake_minimum_required(VERSION 3.0)
enable_testing()

project (CPPDIGRAPH CXX)

set (CMAKE_CXX_STANDARD 11)
set (CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -std=c++11" )
set (CMAKE_BUILD_TYPE Debug)

add_subdirectory (src)
add_subdirectory (test)


add_test (NAME UnitTest COMMAND test/unittest.out --gtest_color=yes)
add_test (NAME IntegrationTest COMMAND test/integrationtest.out 5)
