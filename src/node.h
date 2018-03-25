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
// void connectTail(Edge<A, B>* edge) { mABTails.insert(edge); }
// void connectHead(Edge<B, A>* edge) { mBAHeads.insert(edge); }
// void destructTail(Edge<A, B>* edge) { mABTails.erase(edge); }
// void destructHead(Edge<B, A>* edge) { mBAHeads.erase(edge); }
// set<Edge<A, B>*> A::mABTails
// set<Edge<B, A>*> A::mBAHeads
#define CDG_NODE_CREATE_RELATIONSHIP(__this, __that, __tails_name, __heads_name) \
public: \
  void connectTail(cdg::Edge<__this, __that>* edge) { __tails_name.insert(edge); } \
  void connectHead(cdg::Edge<__that, __this>* edge) { __heads_name.insert(edge); } \
  void destructTail(cdg::Edge<__this, __that>* edge) { __tails_name.erase(edge); } \
  void destructHead(cdg::Edge<__that, __this>* edge) { __heads_name.erase(edge); } \
 \
private: \
  std::set<cdg::Edge<__this, __that>*> __tails_name; \
  std::set<cdg::Edge<__that, __this>*> __heads_name;


// Optional automatic edge deletion for a named collection.
//   This macro should be placed in the User Node class destructor.
#define CDG_NODE_DESTRUCT_RELATIONSHIP(__edge_collection) \
for (auto& edge : __edge_collection) delete edge; \
__edge_collection.clear();


/*
 * Node
 *   Common base class for Node.  Super simple, mostly just exists
 *   to support DiGraph collections that can own a single master set
 *   of Nodes by giving users a base to inherit from.
 */
class Node {
public:
  Node(std::string name): mName(name) {}

  const std::string getName() const { return mName; }

private:
  const std::string mName;

};

} // namespace cdg

#endif
