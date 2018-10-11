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

#include "./graphviz/gvdigraph.h"
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
  void add(Node* node);
  void remove(Node* node);
  void add(EdgeBase* edge);
  void remove(EdgeBase* edge);

  const std::string getName() const;
  int getNextCdgId();

  ////// GraphViz

  GvDiGraph to_graphviz();
  GvDiGraph to_graphviz(std::string graphname);


private:
  const std::string mName;
  int mNextCdgId;
  NodeSet mNodes;
  EdgeSet mEdges;

};


} // namespace cdg


std::ostream& operator<<(std::ostream& os, cdg::DiGraph digraph);


#endif
