/*
 * relationship.h
 * 
 * Types:
 *   Relationship
 *   Relationship::connector
 *   Relationship::disconnector
 */

#ifndef CDG_RELATIONSHIP_H
#define CDG_RELATIONSHIP_H

#include <iostream>

#include "./edge.h"
#include "./node.h"


namespace cdg {


/*
 * Relationship
 *   Templated mixin class that adds an edge from `tail_t* this` to a `head_t*`
 */
template <typename tail_t, typename head_t, typename node_t = Node>
class Relationship {
public:
  Relationship(node_t* node
            ): mNode(node)
             , mOutgoingEdge(nullptr)
             , mIncomingEdge(nullptr)
  {
  }

  virtual ~Relationship() {
    preDestruct();
  }

  void preDestruct() {
    if (mOutgoingEdge) {
      head_t* next = getNext();
      if (next) {
        next->Relationship<tail_t, head_t>::disconnect(mOutgoingEdge);
      }
      // Make sure we delete each edge exactly once
      if (mNode->hasEdge(mOutgoingEdge)) {
        delete mOutgoingEdge;
      }
      mOutgoingEdge = nullptr;
    }
    if (mIncomingEdge) {
      tail_t* prev = getPrev();
      if (prev) {
        prev->Relationship<tail_t, head_t>::disconnect(mIncomingEdge);
      }
      // Make sure we delete each edge exactly once
      if (mNode->hasEdge(mIncomingEdge)) {
        delete mIncomingEdge;
      }
      mIncomingEdge = nullptr;
    }
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
      if (tail and head) {
        if (!digraph) digraph = tail->getDiGraph();
        auto edge = new edge_t<tail_t, head_t>(digraph, tail, head);
        tail->Relationship<tail_t, head_t>::connect(edge);
        head->Relationship<tail_t, head_t>::connect(edge);
        return edge;
      }
      return nullptr;
    }
  };

  /*
   * Disconnector
   */
  struct disconnector {
    void operator()(tail_t* tail, head_t* head) {
      (*this)(nullptr, tail, head);
    }

    void operator()(DiGraph* digraph, tail_t* tail, head_t* head) {
      if (tail and head) {
        Edge<tail_t, head_t>* edge = tail->Relationship<tail_t, head_t>::getOutgoingEdge();
        if (edge and edge->getHead() == head) {
          tail->Relationship<tail_t, head_t>::disconnect(edge);
          head->Relationship<tail_t, head_t>::disconnect(edge);
          delete edge;
        }
      }
    }
  };

private:
  node_t* mNode;
  Edge<tail_t, head_t>* mOutgoingEdge;
  Edge<tail_t, head_t>* mIncomingEdge;
};


} // namespace cdg


#endif
