/*
 * utility.h
 */

#ifndef CDG_UTILITY_H
#define CDG_UTILITY_H

#include <set>
#include <string>
#include <vector>


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


/*
 * DiGraph Common Definitions
 */
class Node;
class EdgeBase;
typedef std::set<Node*, CdgIdCompare<Node>> NodeSet;
typedef std::set<EdgeBase*, CdgIdCompare<EdgeBase>> EdgeSet;


/*
 * Graphviz DiGraph Common Definitions
 */
template <typename T> class GvProxy;
typedef GvProxy<Node> GvNode;
typedef GvProxy<EdgeBase> GvEdge;
typedef std::set<GvNode*, CdgIdCompare<GvNode>> GvNodeSet;
typedef std::set<GvEdge*, CdgIdCompare<GvEdge>> GvEdgeSet;

static const std::vector<std::string> cGraphvizSpecialCharacters = {
  // ".",
  // "-",
  // "=",
  // "\""
};

static std::string graphviz_sanitize(std::string str) {
  for (auto specialCharacter : cGraphvizSpecialCharacters) {
    for (int pos = str.find(specialCharacter); pos != std::string::npos; pos = str.find(specialCharacter, pos+2)) {
      str.replace(pos, 1, "\\" + specialCharacter);
    }
  }
  return str;
}


} // namespace cdg


#endif
