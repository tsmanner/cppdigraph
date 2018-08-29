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
  return to_graphviz(getName());
}


std::string DiGraph::to_graphviz(std::string graphname) {
  std::set<std::string> nodes;
  std::set<std::string> edges;
  std::string s = "digraph " + graphname + " {\n";
  for (auto node : mNodes) {
    nodes.insert(node->to_graphviz());
  }
  for (auto edge : mEdges) {
    edges.insert(edge->to_graphviz());
  }
  for (auto node_string : nodes) {
    s += "  " + node_string + ";\n";
  }
  for (auto edge_string : edges) {
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
