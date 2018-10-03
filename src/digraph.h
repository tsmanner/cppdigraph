/*
 * digraph.h
 */

#ifndef CDG_DIGRAPH_H
#define CDG_DIGRAPH_H

#include <iostream>
#include <list>
#include <map>
#include <set>
#include <sstream>
#include <string>

#include "./graphviz.h"
#include "./utility.h"

namespace cdg {


class Node;
class EdgeBase;


class DiGraph {
public:
  DiGraph(std::string name);
  virtual ~DiGraph();

  void clear();
  int size();
  void add(Node* node) { mNodes.insert(node); }
  void remove(Node* node) { mNodes.erase(node); }
  void add(EdgeBase* edge) { mEdges.insert(edge); }
  void remove(EdgeBase* edge) { mEdges.erase(edge); }

  const std::string getName() const;

  ////// GraphViz

  GvDiGraph to_graphviz();
  GvDiGraph to_graphviz(std::string graphname);


private:
  const std::string mName;
  std::set<Node*, NameCompare<Node>> mNodes;
  std::set<EdgeBase*, NameCompare<EdgeBase>> mEdges;

};


} // namespace cdg


std::ostream& operator<<(std::ostream& os, cdg::DiGraph digraph);


#endif
