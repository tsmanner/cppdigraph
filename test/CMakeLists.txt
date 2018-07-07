find_package(GTest REQUIRED)
include_directories (
    ${CPPDIGRAPH_SOURCE_DIR}/src
)

add_executable (
    unittest.out
    do_unit_tests.cpp
    test_node.cpp
    test_edge.cpp
)

add_executable (
    integrationtest.out
    integration.cpp
)

target_link_libraries (
    unittest.out
    gmock_main
    GTest::GTest
    GTest::Main
)
