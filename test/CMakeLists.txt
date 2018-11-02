cmake_minimum_required(VERSION 3.0)

project (CPPDIGRAPH_TEST CXX)

set (CMAKE_CXX_STANDARD 11)
set (CMAKE_BUILD_TYPE Debug)

set (CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set (EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})

include_directories (
    ${CPPDIGRAPH_SOURCE_DIR}
)

find_package(GTest REQUIRED)

add_test (NAME UnitTest COMMAND unittest.out --gtest_color=yes)

add_executable (
    unittest.out
    do_unit_tests.cpp
    test_relationship.cpp
    test_node.cpp
    test_edge.cpp
    test_digraph.cpp
    test_gvdigraph.cpp
    test_gvproxy.cpp
    test_gvtablecell.cpp
    test_gvtablerow.cpp
    test_gvtable.cpp
    test_gvfilter.cpp
    test_chain.cpp
    test_bidirectionalchain.cpp
)

target_link_libraries (
    unittest.out
    DiGraph
    gmock_main
    GTest::GTest
    GTest::Main
)

add_test (NAME IntegrationTest COMMAND integrationtest.out 5)

add_executable (
    integrationtest.out
    integration.cpp
)

target_link_libraries (
    integrationtest.out
    DiGraph
)
