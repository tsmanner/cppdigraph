add_library (DiGraph digraph.cpp)

# Set the linker language to C++ for the DiGraph target
SET_TARGET_PROPERTIES(DiGraph PROPERTIES LINKER_LANGUAGE CXX)
