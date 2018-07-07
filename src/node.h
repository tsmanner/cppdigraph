/*
 * node.h
 * 
 * Types:
 *   Node
 */

#ifndef CDG_NODE_H
#define CDG_NODE_H

#include <iostream>
#include <string>
#include <unordered_set>

#include "digraph.h"
#include "edge.h"

namespace cdg {


/*
 * Node
 *   Common base class for graph nodes.
 */
class Node {
public:
  Node(DiGraph* digraph, std::string name): mDiGraph(digraph), mName(name) {
    if (mDiGraph) mDiGraph->add(this);
  }

  virtual ~Node() {
    for (auto edge : mEdges) {
      edge->disconnect(this);
    }
    if (mDiGraph) mDiGraph->remove(this);
  }

  const std::string getName() const {
    return mName;
  }

  virtual void addEdge(EdgeBase* edge) {
    mEdges.insert(edge);
  }

  virtual void removeEdge(EdgeBase* edge) {
    mEdges.erase(edge);
  }

  virtual GraphVizStatements graphviz_statements() {
    GraphVizStatements gvs;
    gvs.nodes.insert(getName());
    return gvs;
  }

  std::string to_string() {
    return "[" + getName() + "]";
  }

  std::ostream& operator<<(std::ostream& os) {
    return os << to_string();
  }

private:
  DiGraph* mDiGraph;
  const std::string mName;
  std::unordered_set<EdgeBase*> mEdges;

};


} // namespace cdg

#endif
