#include "digraph.h"

#include "edge.h"
#include "node.h"


namespace cdg {


DiGraph::DiGraph(std::string name): mName(name) {
  mNextCdgId = std::hash<std::string>()(name) + 1;
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


void DiGraph::add(Node* node) {
  mNodes.insert(node);
}


void DiGraph::remove(Node* node) {
  mNodes.erase(node);
}


void DiGraph::add(EdgeBase* edge) {
  mEdges.insert(edge);
}


void DiGraph::remove(EdgeBase* edge) {
  mEdges.erase(edge);
}


const std::string DiGraph::getName() const {
  return mName;
}


int DiGraph::getNextCdgId() {
  return mNextCdgId++;
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
  return graphViz;
}


} // namespace cdg
