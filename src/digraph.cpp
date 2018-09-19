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


int DiGraph::size() {
  return mNodes.size();
}


std::string DiGraph::to_graphviz() {
  std::map<std::string, std::set<Node*>> subgraphs = {};
  return to_graphviz(subgraphs);
}


std::string DiGraph::to_graphviz(std::map<std::string, std::set<Node*>> subgraphs) {
  return to_graphviz(getName(), subgraphs);
}


std::string DiGraph::to_graphviz(std::string graphname) {
  std::map<std::string, std::set<Node*>> subgraphs = {};
  return to_graphviz(graphname, subgraphs);
}


std::string DiGraph::to_graphviz(std::string graphname, std::map<std::string, std::set<Node*>> subgraphs) {
  // Iterate over all the nodes and edges, compiling the graphviz strings
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
  for (auto p : subgraphs) {
    auto subgraphLabel = p.first;
    auto subgraphNodes = p.second;
    s += "  subgraph cluster_" + subgraphLabel + " {\n";
    s += "    label = \"" + subgraphLabel + "\";\n";
    for (auto node : subgraphNodes) {
      if (node) {
        s += "    " + node->graphviz_name() + ";\n";
      }
    }
    s += "  }\n";
  }
  s += "}\n";
  return s;
}


const std::string DiGraph::getName() const {
  return mName;
}


std::ostream& DiGraph::operator<<(std::ostream& os) {
  return os << getName();
}
