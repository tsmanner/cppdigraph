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

#include "edge.h"

namespace cdg {


/*
 * Node
 *   Common base class for graph nodes.
 */
class Node {
public:
  Node(std::string name): mName(name) {
  }

  virtual ~Node() {
    for (auto edge : mEdges) {
      edge->disconnect(this);
    }
  }

  virtual void addEdge(EdgeBase* edge) {
    mEdges.insert(edge);
  }

  virtual void removeEdge(EdgeBase* edge) {
    mEdges.erase(edge);
  }

  const std::string getName() const {
    return mName;
  }

  std::string to_string() {
    return "[" + getName() + "]";
  }

  std::ostream& operator<<(std::ostream& os) {
    return os << to_string();
  }

private:
  std::unordered_set<EdgeBase*> mEdges;
  const std::string mName;

};


} // namespace cdg

#endif
