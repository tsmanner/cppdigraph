#include "digraph.h"

#include "edge.h"
#include "node.h"


namespace cdg {


DiGraph::DiGraph(std::string name): mName(name) {
}


DiGraph::~DiGraph() {
  clear();
}


void DiGraph::clear() {
  while (mNodes.size()) delete *mNodes.begin();
  while (mEdges.size()) delete *mEdges.begin();
}


int DiGraph::size() {
  return mNodes.size();
}


const std::string DiGraph::getName() const {
  return mName;
}


std::ostream& operator<<(std::ostream& os, cdg::DiGraph digraph) {
  return os << digraph.getName();
}


/* 
 * GraphViz
 */


GvDiGraph DiGraph::to_graphviz() {
  return to_graphviz(getName());
}


GvDiGraph DiGraph::to_graphviz(std::string graphname) {
  GvDiGraph graphViz = GvDiGraph(graphname);
  for (auto node : mNodes) {
    if (node) {
      graphViz.add(node);
    }
  }
  for (auto edge : mEdges) {
    graphViz.add(edge);
  }
  graphViz.setAttribute("bgcolor", "transparent");
  return graphViz;
}


} // namespace cdg
