/*
 * Node
 *   Generic base class for nodes.  Only here to give users
 *   a common place to derive from while allowing ownership
 *   of Node instances to exist in a single entity.
 *
 *   TODO: Implement DiGraph class as a container for Node*
+ *         instances.
 */

#ifndef CDG_NODE_H
#define CDG_NODE_H

#include <string>
#include <set>

#include "edge.h"

namespace cdg {

// Consider the following
// __this = A
// __that = B
// A relationship between A and B, in A, looks like
// A -> B  -- A has Tails of Edge<A, B>
// A <- B  -- A has Heads of Edge<B, A>
//
// void connectTail(Edge<A, B> edge) { mABTails.insert(edge); }
// void connectHead(Edge<B, A> edge) { mBAHeads.insert(edge); }
// void destructTail(Edge<A, B> edge) { mABTails.erase(edge); }
// void destructHead(Edge<B, A> edge) { mBAHeads.erase(edge); }
// set<Edge<A, B>> A::mABTails
// set<Edge<B, A>> A::mBAHeads
//
// void connectTail(Edge<__this, __that> edge) { m__this__thatTails.insert(edge); }
// void connectHead(Edge<__that, __this> edge) { m__that__thisHeads.insert(edge); }
// void destructTail(Edge<__this, __that> edge) { m__this__thatTails.erase(edge); }
// void destructHead(Edge<__that, __this> edge) { m__that__thisHeads.erase(edge); }
// set<Edge<__this, __that>> __this::m__this__thatTails
// set<Edge<__that, __this>> __this::m__that__thisHeads

#define CDG_NODE_RELATIONSHIP(__this, __that, __tails_name, __heads_name) \
public: \
  void connectTail(cdg::Edge<__this, __that>* edge) { __tails_name.insert(edge); } \
  void connectHead(cdg::Edge<__that, __this>* edge) { __heads_name.insert(edge); } \
  void destructTail(cdg::Edge<__this, __that>* edge) { __tails_name.erase(edge); } \
  void destructHead(cdg::Edge<__that, __this>* edge) { __heads_name.erase(edge); } \
private: \
  std::set<cdg::Edge<__this, __that>*> __tails_name; \
  std::set<cdg::Edge<__that, __this>*> __heads_name;


class Node {
public:
  Node() {}

private:

};

} // namespace cdg

#endif
