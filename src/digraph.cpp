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


const std::string DiGraph::getName() const {
  return mName;
}


std::ostream& operator<<(std::ostream& os, cdg::DiGraph digraph) {
  return os << digraph.getName();
}


/* 
 * GraphViz
 */


DiGraph::GraphViz DiGraph::to_graphviz() {
  return to_graphviz(getName());
}


DiGraph::GraphViz DiGraph::to_graphviz(std::string graphname) {
  GraphViz graphViz = GraphViz(graphname);
  for (auto node : mNodes) {
    if (node) {
      graphViz.insertNode(node->to_graphviz());
    }
  }
  for (auto edge : mEdges) {
    graphViz.insertEdge(edge->to_graphviz());
  }
  graphViz.setAttribute("bgcolor", "transparent");
  return graphViz;
}


DiGraph::GraphViz::GraphViz(std::string name): mName(name) {}


void DiGraph::GraphViz::insertNode(std::string nodeString) {
  mNodes.insert(nodeString);
}


void DiGraph::GraphViz::insertEdge(std::string edgeString) {
  mEdges.insert(edgeString);
}


void DiGraph::GraphViz::addSubgraph(std::string subgraphName, std::set<Node*> subgraph) {
  std::set<std::string> subgraphStrings;
  for (auto node : subgraph) {
    if (node) {
      subgraphStrings.insert(node->graphviz_name());
    }
  }
  mSubgraphs[subgraphName] = subgraphStrings;
}


void DiGraph::GraphViz::addAttributes(std::map<std::string, std::string> attributes) {
  for (auto p : attributes) {
    setAttribute(p.first, p.second);
  }
}


void DiGraph::GraphViz::setAttribute(std::string name, std::string value) {
  mAttributes[name] = value;
}


std::string DiGraph::GraphViz::to_string() {
  std::ostringstream graphStream;
  graphStream << "digraph " << mName << " {" << std::endl;
  for (auto p : mAttributes) {
    graphStream << "  \"" << p.first << "\" = \"" << p.second << "\";" << std::endl;
  }
  for (auto node_string : mNodes) {
    graphStream << "  " << node_string << ";" << std::endl;
  }
  for (auto edge_string : mEdges) {
    if (edge_string != "") {
      graphStream << "  " << edge_string << ";" << std::endl;
    }
  }
  for (auto p : mSubgraphs) {
    auto subgraphLabel = p.first;
    auto subgraphNodes = p.second;
    graphStream << "  subgraph cluster_" << subgraphLabel << " {" << std::endl;
    graphStream << "    label = \"" << subgraphLabel << "\";" << std::endl;
    for (auto node : subgraphNodes) {
      graphStream << "    " << node << ";" << std::endl;
    }
    graphStream << "  }" << std::endl;
  }
  graphStream << "}" << std::endl;
  return graphStream.str();
}


std::ostream& operator<<(std::ostream& os, cdg::DiGraph::GraphViz graphviz) {
  os << graphviz.to_string();
  return os;
}
