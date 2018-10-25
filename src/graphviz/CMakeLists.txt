add_library(Graphviz_o OBJECT
  gvsubgraph.cpp
  gvdigraph.cpp
  gvfilter.cpp
)

set (CDG_GRAPHVIZ_HEADERS
  "${CMAKE_CURRENT_SOURCE_DIR}/gvproxy.h"
  "${CMAKE_CURRENT_SOURCE_DIR}/gvsubgraph.h"
  "${CMAKE_CURRENT_SOURCE_DIR}/gvdigraph.h"
  "${CMAKE_CURRENT_SOURCE_DIR}/gvtable.h"
  "${CMAKE_CURRENT_SOURCE_DIR}/gvtablerow.h"
  "${CMAKE_CURRENT_SOURCE_DIR}/gvtablecell.h"
  "${CMAKE_CURRENT_SOURCE_DIR}/gvfilter.h"
  PARENT_SCOPE
)
