/*
 * gvsubgraph.h
 */

#ifndef CDG_GVSUBGRAPH_H
#define CDG_GVSUBGRAPH_H

#include <set>
#include <string>

#include "./gvproxy.h"
#include "../utility.h"


namespace cdg {


class GvDiGraph;


class GvSubGraph {
public:
  GvSubGraph() {}
  GvSubGraph(GvDiGraph* parentGraph, std::string name);
  GvSubGraph(GvDiGraph* parentGraph, std::string name, NodeSet nodes);
  virtual ~GvSubGraph();

  GvNode* add(Node* node);
  void setAttribute(std::string name, std::string value);
  std::string getAttribute(std::string key);

  std::string to_string();

private:
  GvDiGraph* mParentGraph;
  std::string mName;
  std::map<std::string, std::string> mAttributes;
  GvNodeSet mNodes;

};


} // namespace cdg


std::ostream& operator<<(std::ostream& os, cdg::GvSubGraph& gvsg);
std::ostream& operator<<(std::ostream& os, cdg::GvSubGraph gvsg);


#endif
