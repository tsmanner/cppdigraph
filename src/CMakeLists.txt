cmake_minimum_required(VERSION 3.0)

project (CPPDIGRAPH CXX)

set (CMAKE_CXX_STANDARD 11)

set (CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set (EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")

set (CDG_GRAPHVIZ_HEADERS)

set (CDG_HEADERS
  digraph.h
  edge.h
  node.h
  relationship.h
  utility.h
)

add_subdirectory (graphviz)

add_library (DiGraph_o OBJECT
  digraph.cpp
)

add_library (DiGraph SHARED
  "$<TARGET_OBJECTS:DiGraph_o>"
  "$<TARGET_OBJECTS:Graphviz_o>"
)

# Install for this target has to happen once per directory required in `include/` for PUBLIC_HEADER.

# Install first with the src/ headers
set_target_properties (DiGraph PROPERTIES PUBLIC_HEADER "${CDG_HEADERS}")
INSTALL (
  TARGETS DiGraph
  LIBRARY       DESTINATION ${CMAKE_BINARY_DIR}/lib
  PUBLIC_HEADER DESTINATION ${CMAKE_BINARY_DIR}/include/cdg
)

# Install second with the src/graphviz/ headers
set_target_properties (DiGraph PROPERTIES PUBLIC_HEADER "${CDG_GRAPHVIZ_HEADERS}")
INSTALL (
  TARGETS DiGraph
  LIBRARY       DESTINATION ${CMAKE_BINARY_DIR}/lib
  PUBLIC_HEADER DESTINATION ${CMAKE_BINARY_DIR}/include/cdg/graphviz
)

# Set the linker language to C++ for the DiGraph target
SET_TARGET_PROPERTIES (DiGraph PROPERTIES LINKER_LANGUAGE CXX)
