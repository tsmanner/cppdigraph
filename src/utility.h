/*
 * utility.h
 */

#ifndef CDG_UTILITY_H
#define CDG_UTILITY_H


namespace cdg {


class Node;
class EdgeBase;


template<typename T>
struct NameCompare {
  bool operator()(T* lhs, T* rhs) {
    return lhs->getCdgId() < rhs->getCdgId();
  }
};


typedef std::set<Node*, NameCompare<Node>> NodeSet;
typedef std::set<EdgeBase*, NameCompare<EdgeBase>> EdgeSet;


} // namespace cdg


#endif
