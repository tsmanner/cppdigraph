/*
 * digraph.h
 * 
 * Types:
 *   Node
 */

#ifndef CDG_DIGRAPH_H
#define CDG_DIGRAPH_H

#include <iostream>
#include <list>
#include <map>
#include <set>
#include <sstream>
#include <string>

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

  class GraphViz;
  GraphViz to_graphviz();
  GraphViz to_graphviz(std::string graphname);

  class GraphViz {
  public:
    GraphViz(std::string name);

    void insertNode(std::string nodeString);
    void insertEdge(std::string edgeString);

    void addSubgraph(std::string subgraphName, std::set<Node*> subgraph);
    void addAttributes(std::map<std::string, std::string> attributes);
    void setAttribute(std::string name, std::string value);
    std::map<std::string, std::string> getAttributes() { return mAttributes; }

    std::string to_string();

  private:
    const std::string mName;
    std::map<std::string, std::string> mAttributes;
    std::map<std::string, std::set<std::string>> mSubgraphs;
    std::set<std::string> mNodes;
    std::set<std::string> mEdges;
  };

private:
  const std::string mName;
  std::set<Node*> mNodes;
  std::set<EdgeBase*> mEdges;

};


} // namespace cdg


std::ostream& operator<<(std::ostream& os, cdg::DiGraph digraph);
std::ostream& operator<<(std::ostream& os, cdg::DiGraph::GraphViz graphviz);


#endif
