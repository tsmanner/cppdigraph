cmake_minimum_required(VERSION 3.0)

project (CPPDIGRAPH CXX)

set (CMAKE_CXX_STANDARD 11)

set (CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set (EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})

add_library (DiGraph SHARED digraph.cpp graphviz.cpp)
set_target_properties(DiGraph PROPERTIES PUBLIC_HEADER "digraph.h;edge.h;node.h;relationship.h")
INSTALL(
  TARGETS DiGraph
  LIBRARY       DESTINATION ${CMAKE_BINARY_DIR}/lib
  PUBLIC_HEADER DESTINATION ${CMAKE_BINARY_DIR}/include/cdg
)

# Set the linker language to C++ for the DiGraph target
SET_TARGET_PROPERTIES(DiGraph PROPERTIES LINKER_LANGUAGE CXX)
