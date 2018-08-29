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
  tail_t* getPrev() { if (mIncomingEdge) return mIncomingEdge->getTail(); return nullptr; }
  Edge<tail_t, head_t>* getOutgoingEdge() { return mOutgoingEdge; }
  Edge<tail_t, head_t>* getIncomingEdge() { return mIncomingEdge; }

  /*
   * Connector overload for defined relationship
   */
  template <template<typename, typename> class edge_t = Edge>
  struct connector {
    edge_t<tail_t, head_t>* operator()(tail_t* tail, head_t* head) {
      return (*this)(nullptr, tail, head);
    }

    edge_t<tail_t, head_t>* operator()(DiGraph* digraph, tail_t* tail, head_t* head) {
      auto edge = new edge_t<tail_t, head_t>(digraph, tail, head);
      tail->Relationship<tail_t, head_t>::connect(edge);
      head->Relationship<tail_t, head_t>::connect(edge);
      return edge;
    }
  };

  struct disconnector {
    void operator()(tail_t* tail, head_t* head) {
      (*this)(nullptr, tail, head);
    }

    void operator()(DiGraph* digraph, tail_t* tail, head_t* head) {
      Edge<tail_t, head_t>* edge = tail->getOutgoingEdge();
      if (edge->getHead() == head) {
        tail->Relationship<tail_t, head_t>::disconnect(edge);
        tail->removeEdge(edge);
        head->Relationship<tail_t, head_t>::disconnect(edge);
        head->removeEdge(edge);
        edge->disconnect(tail);
        edge->disconnect(head);
      }
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
