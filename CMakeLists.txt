cmake_minimum_required(VERSION 3.0)
set (CMAKE_CXX_STANDARD 11)
set (CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -std=c++11" )

#find_package(PkgConfig)
#pkg_check_modules(GTEST REQUIRED gtest>=1.7.0)
#pkg_check_modules(GMOCK REQUIRED gmock>=1.7.0)

#include_directories(
#    ${GTEST_INCLUDE_DIRS}
#    ${GMOCK_INCLUDE_DIRS}
#)



add_subdirectory (src)
include_directories ("${PROJECT_SOURCE_DIR}/src")
 
# add the executable
add_executable (main src/main.C)
# target_link_libraries (Tutorial MathFunctions)
