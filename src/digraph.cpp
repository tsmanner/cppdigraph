#include "digraph.h"

#include "edge.h"
#include "node.h"


using namespace cdg;


DiGraph::DiGraph(std::string name): mName(name) {
}


DiGraph::~DiGraph() {
  for (auto n : mNodes) {
    delete n;
  }
}


void DiGraph::clear() {
  while (mNodes.size()) delete *mNodes.begin();
}


std::string DiGraph::to_graphviz() {
  GraphVizStatements gvs;
  std::string s = "digraph " + getName() + " {\n";
  for (auto node : mNodes) {
    gvs.merge(node->graphviz_statements());
  }
  for (auto node_string : gvs.nodes) {
    s += "  " + node_string + ";\n";
  }
  for (auto edge_string : gvs.edges) {
    if (edge_string != "") {
      s += "  " + edge_string + ";\n";
    }
  }
  s += "}";
  return s;
}


const std::string DiGraph::getName() const {
  return mName;
}


std::ostream& DiGraph::operator<<(std::ostream& os) {
  return os << getName();
}
