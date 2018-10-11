add_library(Graphviz_o OBJECT
  gvsubgraph.cpp
  gvdigraph.cpp
)

list(APPEND CDG_HEADERS
  gvproxy.h
  gvsubgraph.h
  gvdigraph.h
  gvtable.h
  gvtablerow.h
  gvtablecell.h
)
