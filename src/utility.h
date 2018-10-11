/*
 * utility.h
 */

#ifndef CDG_UTILITY_H
#define CDG_UTILITY_H


namespace cdg {


template<typename T>
struct CdgIdCompare {
  bool operator()(T* lhs, T* rhs) {
    if (lhs and rhs) {
      return lhs->getCdgId() < rhs->getCdgId();
    }
    else if (rhs) {
      return true;
    }
    return false;
  }
};


class Node;
class EdgeBase;
typedef std::set<Node*, CdgIdCompare<Node>> NodeSet;
typedef std::set<EdgeBase*, CdgIdCompare<EdgeBase>> EdgeSet;

template <typename T> class GvProxy;
typedef GvProxy<Node> GvNode;
typedef GvProxy<EdgeBase> GvEdge;
typedef std::set<GvNode*, CdgIdCompare<GvNode>> GvNodeSet;
typedef std::set<GvEdge*, CdgIdCompare<GvEdge>> GvEdgeSet;


} // namespace cdg


#endif
