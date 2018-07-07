/*
 * Node
 *   Generic base class for nodes.  Only here to give users
 *   a common place to derive from while allowing ownership
 *   of Node instances to exist in a single entity.
 *
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
 *   Common base class for Node.  Super simple, mostly just exists
 *   to support DiGraph collections that can own a single master set
 *   of Nodes by giving users a base to inherit from.
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

  std::ostream& operator<<(std::ostream& os) {
    return os << "[" << getName() << "]";
  }

private:
  std::unordered_set<EdgeBase*> mEdges;
  const std::string mName;

};


} // namespace cdg

#endif
