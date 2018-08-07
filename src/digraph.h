/*
 * node.h
 * 
 * Types:
 *   Node
 */

#ifndef CDG_DIGRAPH_H
#define CDG_DIGRAPH_H

#include <iostream>
#include <list>
#include <set>
#include <string>

namespace cdg {


class Node;
class EdgeBase;


struct GraphVizStatements {
  std::set<std::string> nodes;
  std::set<std::string> edges;

  void merge(GraphVizStatements other) {
    nodes.insert(other.nodes.begin(), other.nodes.end());
    edges.insert(other.edges.begin(), other.edges.end());
  }

};


class DiGraph {
public:
  DiGraph(std::string name);
  virtual ~DiGraph();

  void clear();
  void add(Node* node) { mNodes.insert(node); }
  void remove(Node* node) { mNodes.erase(node); }

  std::string to_graphviz();
  std::string to_graphviz(std::string graphname);

  const std::string getName() const;

  std::ostream& operator<<(std::ostream& os);

private:
  const std::string mName;
  std::set<Node*> mNodes;

};


} // namespace cdg

#endif
