/*
 * graphviz.h
 */

#ifndef CDG_GRAPHVIZ_H
#define CDG_GRAPHVIZ_H

#include <map>
#include <set>
#include <string>


namespace cdg {

class Node;
class EdgeBase;


class GvSubGraph {
public:
  GvSubGraph() {}
  GvSubGraph(std::string name, std::set<Node*> nodes);

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

  void add(Node* node);
  void add(EdgeBase* edge);

  GvSubGraph& addSubgraph(std::string subgraphName, std::set<Node*> subgraph);
  GvSubGraph& getSubgraph(std::string subgraphName);
  void addAttributes(std::map<std::string, std::string> attributes);
  void setAttribute(std::string name, std::string value);
  std::string getAttribute(std::string key) { return mAttributes[key]; }

  std::string to_string();

private:
  const std::string mName;
  std::map<std::string, std::string> mAttributes;
  std::map<std::string, GvSubGraph> mSubgraphs;
  std::set<Node*> mNodes;
  std::set<EdgeBase*> mEdges;
};


} // namespace cdg

std::ostream& operator<<(std::ostream& os, cdg::GvDiGraph gvd);

#endif
