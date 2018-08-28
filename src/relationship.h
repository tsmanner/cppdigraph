/*
 * node.h
 * 
 * Types:
 *   Node
 */

#ifndef CDG_RELATIONSHIP_H
#define CDG_RELATIONSHIP_H


#include "edge.h"


namespace cdg {


/*
 * Relationship
 *   Templated mixin class that adds an edge from `this` to `T`
 */
template <typename tail_t, typename head_t, typename edge_t = Edge>
class Relationship {
public:
  Relationship<tail_t, head_t>(tail_t* tail): mTail(tail) {
  }

  virtual ~Relationship<tail_t, head_t>() {
  }

  Edge<tail_t, head_t>* connect(head_t* head) {
    return connector<Edge>()(mTail, head);
  }

private:
  tail_t* mTail;
  Edge<tail_t, head_t>* mEdge;

};


} // namespace cdg


#endif
