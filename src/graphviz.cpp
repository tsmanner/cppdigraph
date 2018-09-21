#include "graphviz.h"
#include "edge.h"
#include "node.h"


namespace cdg {


GvSubGraph::GvSubGraph(std::string name
                     , std::set<Node*> nodes
                    ): mName(name)
                     , mNodes(nodes)
{
  setAttribute("label", mName);
}


std::string GvSubGraph::to_string() {
  std::ostringstream graphStream;
  graphStream << "  subgraph cluster_" << mName << " {" << std::endl;
  for (auto p : mAttributes) {
    graphStream << "    \"" << p.first << "\" = \"" << p.second << "\";" << std::endl;
  }
  for (auto node : mNodes) {
    graphStream << "    " << node->to_graphviz() << ";" << std::endl;
  }
  graphStream << "  }" << std::endl;
  return graphStream.str();
}


GvDiGraph::GvDiGraph(std::string name): mName(name) {}


void GvDiGraph::add(Node* node) {
  mNodes.insert(node);
}


void GvDiGraph::add(EdgeBase* edge) {
  mEdges.insert(edge);
}


GvSubGraph& GvDiGraph::addSubgraph(std::string subgraphName, std::set<Node*> subgraph) {
  mSubgraphs.insert(std::make_pair(subgraphName, GvSubGraph(subgraphName, subgraph)));
  return getSubgraph(subgraphName);
}


GvSubGraph& GvDiGraph::getSubgraph(std::string subgraphName) {
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


std::string GvDiGraph::to_string() {
  std::ostringstream graphStream;
  graphStream << "digraph " << mName << " {" << std::endl;
  for (auto p : mAttributes) {
    graphStream << "  \"" << p.first << "\" = \"" << p.second << "\";" << std::endl;
  }
  for (auto node : mNodes) {
    std::string node_string = node->to_graphviz();
    graphStream << "  " << node_string << ";" << std::endl;
  }
  for (auto edge : mEdges) {
    std::string edge_string = edge->to_graphviz();
    if (edge_string != "") {
      graphStream << "  " << edge_string << ";" << std::endl;
    }
  }
  for (auto p : mSubgraphs) {
    graphStream << p.second.to_string();
  }
  graphStream << "}" << std::endl;
  return graphStream.str();
}


} // namespace cdg


std::ostream& operator<<(std::ostream& os, cdg::GvDiGraph gvd) {
  os << gvd.to_string();
  return os;
}
