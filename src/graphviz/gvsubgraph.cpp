/*
 * gvsubgraph.cpp
 */

#ifndef CDG_GVSUBGRAPH_C
#define CDG_GVSUBGRAPH_C

#include <sstream>

#include "./gvsubgraph.h"
#include "./gvdigraph.h"
#include "../node.h"


namespace cdg {


GvSubGraph::GvSubGraph(GvDiGraph* parentGraph
                     , std::string name
                    ): mParentGraph(parentGraph)
                     , mName(name)
                     , mNodes()
{
  setAttribute("label", mName);
}


GvSubGraph::GvSubGraph(GvDiGraph* parentGraph
                     , std::string name
                     , NodeSet nodes
                    ): mParentGraph(parentGraph)
                     , mName(name)
                     , mNodes()
{
  for (auto node : nodes) {
    add(node);
  }
  setAttribute("label", mName);
}


GvSubGraph::~GvSubGraph() {
}

GvNode* GvSubGraph::add(Node* node) {
  GvNode* gvNode = mParentGraph->add(node);
  if (gvNode) {
    mNodes.insert(gvNode); 
  }
  return gvNode;
}


void GvSubGraph::setAttribute(std::string name, std::string value) {
  mAttributes[name] = value;
}


std::string GvSubGraph::getAttribute(std::string key) {
  return mAttributes[key];
}


std::string GvSubGraph::to_string() {
  std::stringstream graphStream;
  graphStream << "  subgraph \"cluster_" << graphviz_sanitize(mName) << "\" {" << std::endl;
  for (auto p : mAttributes) {
    graphStream << "    " << graphviz_sanitize(p.first)
                << " = \"" << graphviz_sanitize(p.second) << "\""
                << std::endl;
  }
  for (auto node : mNodes) {
    graphStream << "    " << graphviz_sanitize(node->getObject()->_graphviz_name()) << std::endl;
  }
  graphStream << "  }" << std::endl;
  return graphStream.str();
}


} // namespace cdg


std::ostream& operator<<(std::ostream& os, cdg::GvSubGraph& gvsg) {
  os << gvsg.to_string();
  return os;
}


std::ostream& operator<<(std::ostream& os, cdg::GvSubGraph gvsg) {
  os << gvsg.to_string();
  return os;
}


#endif
