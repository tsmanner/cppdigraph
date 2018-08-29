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
 *   Templated mixin class that adds an edge from `tail_t* this` to a `head_t*`
 */
template <typename tail_t, typename head_t>
class Relationship {
public:
  Relationship(
            ): mOutgoingEdge(nullptr)
             , mIncomingEdge(nullptr)
  {
  }

  virtual ~Relationship() {
    disconnect(mOutgoingEdge);
    disconnect(mIncomingEdge);
  }

  void connect(Edge<tail_t, head_t>* edge) {
    if (edge->getTail() == this) {
      mOutgoingEdge = edge;
    }
    if (edge->getHead() == this) {
      mIncomingEdge = edge;
    }
  }

  void disconnect(Edge<tail_t, head_t>* edge) {
    if (edge == mOutgoingEdge) {
      mOutgoingEdge = nullptr;
    }
    if (edge == mIncomingEdge) {
      mIncomingEdge = nullptr;
    }
  }

  head_t* getNext() { if (mOutgoingEdge) return mOutgoingEdge->getHead(); return nullptr; }

  /*
   * Connector overload for defined relationship
   */
  template <template<typename, typename> class edge_t>
  struct connector {
    edge_t<tail_t, head_t>* operator()(tail_t* tail, head_t* head) {
      auto edge = new edge_t<tail_t, head_t>(tail, head);
      tail->Relationship<tail_t, head_t>::connect(edge);
      head->Relationship<tail_t, head_t>::connect(edge);
      return edge;
    }

    edge_t<tail_t, head_t>* operator()(DiGraph* digraph, tail_t* tail, head_t* head) {
      auto edge = new edge_t<tail_t, head_t>(digraph, tail, head);
      tail->Relationship<tail_t, head_t>::connect(edge);
      head->Relationship<tail_t, head_t>::connect(edge);
      return edge;
    }
  };



private:
  Edge<tail_t, head_t>* mOutgoingEdge;
  // This should only be used when it's a relationship to the same type
  //   i.e. Relationship<NodeA, NodeA>
  Edge<tail_t, head_t>* mIncomingEdge;

};


} // namespace cdg


#endif
