/*
 * gvdigraph.h
 */

#ifndef CDG_GRAPHVIZ_H
#define CDG_GRAPHVIZ_H

#include <map>
#include <set>
#include <string>
#include <unordered_map>

#include "../utility.h"
// #include "./gvnode.h"
// #include "./gvedge.h"
#include "./gvsubgraph.h"


namespace cdg {

class Node;
class EdgeBase;
class GvSubGraph;
class GvDiGraph;


class GvDiGraph {
public:
  GvDiGraph(std::string name);
  virtual ~GvDiGraph();

  GvNode* add(Node* node);
  GvEdge* add(EdgeBase* edge);

  GvNode* get(Node* node);
  GvEdge* get(EdgeBase* edge);

  GvSubGraph& addSubgraph(std::string subgraphName);
  GvSubGraph& addSubgraph(std::string subgraphName, NodeSet subgraph);
  GvSubGraph& getSubgraph(std::string subgraphName);
  void addAttributes(std::map<std::string, std::string> attributes);
  void setAttribute(std::string name, std::string value);
  std::string getAttribute(std::string key);

  std::string to_string();

private:
  const std::string mName;
  std::map<std::string, std::string> mAttributes;
  std::map<std::string, GvSubGraph> mSubgraphs;
  GvNodeSet mNodes;
  GvEdgeSet mEdges;
  std::unordered_map<Node*, GvNode*> mNodeProxyLookupMap;
  std::unordered_map<EdgeBase*, GvEdge*> mEdgeProxyLookupMap;

};


} // namespace cdg


std::ostream& operator<<(std::ostream& os, cdg::GvDiGraph& gvdg);
std::ostream& operator<<(std::ostream& os, cdg::GvDiGraph gvdg);


#endif
