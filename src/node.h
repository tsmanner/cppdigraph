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

#include "./digraph.h"
#include "./edge.h"
#include "./graphviz/gvtable.h"


namespace cdg {


class NodeCopyException: public std::exception {
  virtual const char* what() const throw()
  {
    return "Attempt to make copy of Node";
  }
};


/*
 * Node
 *   Common base class for graph nodes.
 */
class Node {
public:
  Node(DiGraph* digraph
     , std::string name
    ): mDiGraph(digraph)
     , mName(name)
     , mCdgId(getNextCdgId())
  {
    if (getDiGraph()) getDiGraph()->add(this);
  }

  Node(std::string name): Node(nullptr, name) {
  }

  virtual ~Node() {
    while (mEdges.size()) {
      delete *mEdges.begin();
    }
    if (getDiGraph()) getDiGraph()->remove(this);
  }

  const std::string getName() const {
    return mName;
  }

  int getCdgId() {
    return mCdgId;
  }

  DiGraph* getDiGraph() {
    return mDiGraph;
  }

  virtual void addEdge(EdgeBase* edge) {
    mEdges.insert(edge);
  }

  virtual void removeEdge(EdgeBase* edge) {
    mEdges.erase(edge);
  }

  /*
   * GraphViz
   */

  virtual std::map<std::string, std::string> graphviz_attributes() { return std::map<std::string, std::string>(); }
  virtual std::string graphviz_name() { return getName(); }
  std::string _graphviz_name() { return "\"" + graphviz_name() + "\""; }

  virtual GvTable graphviz_table() { return GvTable(); }

  virtual void applyFilter(GvFilter* filter, GvNode* gvNode) {}

  /*
   * String
   */

  virtual std::string to_string() {
    return "[" + getName() + "]";
  }

private:
  DiGraph* mDiGraph;
  const std::string mName;
  int mCdgId;
  std::unordered_set<EdgeBase*> mEdges;

  // Make the copy constructor private so that no one can make copies.
  //   Copying a Node instance will result in corruption of the edge
  //   pointers because the destructor calls delete on them.
  Node(const Node& other) {
    throw NodeCopyException();
  }

};


} // namespace cdg


#endif
