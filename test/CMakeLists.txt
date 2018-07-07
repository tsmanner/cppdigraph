find_package(GTest REQUIRED)
include_directories (
    ${CPPDIGRAPH_SOURCE_DIR}/src
)

add_executable (
    test.out
    do_tests.cpp
    test_node.cpp
    test_edge.cpp
)

target_link_libraries (
    test.out
    #DiGraph
    gmock_main
    GTest::GTest
    GTest::Main
)
