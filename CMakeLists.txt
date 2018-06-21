cmake_minimum_required(VERSION 3.0)

set (CMAKE_CXX_STANDARD 11)
set (CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -std=c++11" )

add_subdirectory (src)
include_directories ("${PROJECT_SOURCE_DIR}/src")

enable_testing()
find_package(GTest REQUIRED)

# add the executable
add_executable(test src/test.cpp)

target_link_libraries(test GTest::GTest GTest::Main)

add_test(AllTests test)

# Create ctags file for simple code indexing.
add_custom_command (TARGET test.out PRE_BUILD COMMAND ctags -f cppdigraph.ctags -R .)
