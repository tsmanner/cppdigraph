/*
 * graphviz.h
 */

#ifndef CDG_GRAPHVIZ_H
#define CDG_GRAPHVIZ_H

#include <map>
#include <set>
#include <string>

#include "./utility.h"


namespace cdg {

class Node;
struct NodeSetCompare;
class EdgeBase;


class GvSubGraph {
public:
  GvSubGraph() {}
  GvSubGraph(std::string name, NodeSet nodes);
  virtual ~GvSubGraph();

  void add(Node* node);
  void setAttribute(std::string name, std::string value) { mAttributes[name] = value; }
  std::string getAttribute(std::string key) { return mAttributes[key]; }

  std::string to_string();

private:
  std::string mName;
  std::map<std::string, std::string> mAttributes;
  std::set<Node*> mNodes;
};


class GvDiGraph {
public:
  GvDiGraph(std::string name);
  virtual ~GvDiGraph();

  void add(Node* node);
  void add(EdgeBase* edge);

  GvSubGraph& addSubgraph(std::string subgraphName, NodeSet subgraph);
  GvSubGraph& getSubgraph(std::string subgraphName);
  void addAttributes(std::map<std::string, std::string> attributes);
  void setAttribute(std::string name, std::string value);
  std::string getAttribute(std::string key) { return mAttributes[key]; }

  std::string to_string();

private:
  const std::string mName;
  std::map<std::string, std::string> mAttributes;
  std::map<std::string, GvSubGraph> mSubgraphs;
  NodeSet mNodes;
  EdgeSet mEdges;
};


} // namespace cdg

std::ostream& operator<<(std::ostream& os, cdg::GvSubGraph gvsg);
std::ostream& operator<<(std::ostream& os, cdg::GvDiGraph gvdg);

#endif
