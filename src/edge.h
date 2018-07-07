/*
 * edge.h
 *
 * Types:
 *   Tail - Handle to tail of an edge.
 *   Head - Handle to head of an edge.
 *   Edge - The edge itself.
 */
 
#ifndef CDG_EDGE_H
#define CDG_EDGE_H

#include <iostream>
#include <string>


namespace cdg {

class Node;

class EdgeBase {
public:
  EdgeBase() {}
  virtual void disconnect(Node* node) = 0;

};


template <typename tail_t, typename head_t>
class Edge: public EdgeBase {
public:
  Edge(tail_t* tail, head_t* head): EdgeBase(), mTail(tail), mHead(head) {
    getTail()->addEdge(this);
    getHead()->addEdge(this);
  }

  virtual ~Edge() {
    if (getTail()) getTail()->removeEdge(this);
    if (getHead()) getHead()->removeEdge(this);
  }

  tail_t* getTail() {
    return mTail;
  }

  head_t* getHead() {
    return mHead;
  }

  virtual void disconnect(Node* node) {
    if (node == mTail) mTail = nullptr;
    if (node == mHead) mHead = nullptr;
    if (mTail == nullptr && mHead == nullptr) {
      delete this;
    }
  }

  std::ostream& operator<<(std::ostream& os) {
    if (getTail()) os << *getTail();
    else os << "[nullptr]";
    os << "->";
    if (getHead()) os << *getHead();
    else os << "[nullptr]";
    return os;
  }

private:
  tail_t* mTail;
  head_t* mHead;

};


// Connector Template
//   This object is templated with a type that itself expects two templates
//   Example:
//     Node* n0 = new Node();
//     Node* n1 = new Node();
//     Edge<Node, Node>* edge = connector<Edge>()(n0, n1);
template <template<typename, typename> class edge_t>
struct connector {
  template <typename tail_t, typename head_t>
  edge_t<tail_t, head_t>* operator()(tail_t* tail, head_t* head) {
    return new edge_t<tail_t, head_t>(tail, head);
  }
};


static connector<Edge> connect = connector<Edge>();


} // namespace cdg

#endif
