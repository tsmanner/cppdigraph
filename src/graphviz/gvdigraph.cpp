/*
 * graphviz.cpp
 */

#include "./gvdigraph.h"
#include "./gvproxy.h"
#include "../edge.h"
#include "../node.h"


namespace cdg {


////// Graphviz DiGraph


GvDiGraph::GvDiGraph(std::string name): mName(name) {
}


GvDiGraph::~GvDiGraph() {
  for (auto node : mNodes) {
    delete node;
  }
  mNodes.clear();
  for (auto edge : mEdges) {
    delete edge;
  }
  mEdges.clear();
}


GvNode* GvDiGraph::add(Node* node) {
  if (node) {
    GvNode* gvNode = new GvNode(node);
    mNodes.insert(gvNode);
    return gvNode;
  }
  return nullptr;
}


GvEdge* GvDiGraph::add(EdgeBase* edge) {
  if (edge) {
    GvEdge* gvEdge = new GvEdge(edge);
    mEdges.insert(gvEdge);
    return gvEdge;
  }
  return nullptr;
}


GvSubGraph& GvDiGraph::addSubgraph(std::string subgraphName) {
  return getSubgraph(subgraphName);
}


GvSubGraph& GvDiGraph::addSubgraph(std::string subgraphName, NodeSet subgraph) {
  mSubgraphs[subgraphName] = GvSubGraph(this, subgraphName, subgraph);
  return getSubgraph(subgraphName);
}


GvSubGraph& GvDiGraph::getSubgraph(std::string subgraphName) {
  if (mSubgraphs.find(subgraphName) == mSubgraphs.end()) {
    mSubgraphs[subgraphName] = GvSubGraph(this, subgraphName);
  }
  return mSubgraphs[subgraphName];
}


void GvDiGraph::addAttributes(std::map<std::string, std::string> attributes) {
  for (auto p : attributes) {
    setAttribute(p.first, p.second);
  }
}


void GvDiGraph::setAttribute(std::string name, std::string value) {
  mAttributes[name] = value;
}


std::string GvDiGraph::getAttribute(std::string key) {
  return mAttributes[key];
}


std::string GvDiGraph::to_string() {
  std::stringstream graphStream;
  graphStream << "digraph \"" << mName << "\" {" << std::endl;
  for (auto p : mAttributes) {
    graphStream << "  " << p.first << " = \"" << p.second << "\"" << std::endl;
  }
  for (auto node : mNodes) {
    graphStream << "  " << node->to_string() << std::endl;
  }
  for (auto edge : mEdges) {
    std::string edge_string = edge->to_string();
    if (edge_string != "") {
      graphStream << "  " << edge_string << std::endl;
    }
  }
  for (auto p : mSubgraphs) {
    graphStream << p.second.to_string();
  }
  graphStream << "}" << std::endl;
  // Go backslash escape anything that graphviz interprets as a special character
  std::string str = graphStream.str();
  for (auto specialCharacter : cGraphvizSpecialCharacters) {
    int count = 0;
    for (int pos = str.find(specialCharacter); pos != std::string::npos; pos = str.find(specialCharacter, pos+2)) {
      str.replace(pos, 1, "\\" + specialCharacter);
    }
  }
  return str;
}


} // namespace cdg


std::ostream& operator<<(std::ostream& os, cdg::GvSubGraph gvsg) {
  os << gvsg.to_string();
  return os;
}


std::ostream& operator<<(std::ostream& os, cdg::GvDiGraph gvdg) {
  os << gvdg.to_string();
  return os;
}
