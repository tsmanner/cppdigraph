find_package(GTest REQUIRED)
include_directories (
    ${CPPDIGRAPH_SOURCE_DIR}/src
)
# add_definitions (-DBOOST_TEST_DYN_LINK)
add_executable (test.out test.cpp)
target_link_libraries (
    test.out
#    DiGraph
    GTest::GTest
    GTest::Main
)
