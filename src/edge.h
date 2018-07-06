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

#include <string>


namespace cdg {

class Node;

class EdgeBase {
public:
  EdgeBase() {} //Node* tail, Node* head): mTail(tail), mHead(head) {}
  virtual void disconnect(Node* node) = 0;

};


template <typename tail_t, typename head_t>
class Edge: public EdgeBase {
public:
  Edge(tail_t* tail, head_t* head): EdgeBase(), mTail(tail), mHead(head) {
    getTail()->addEdge(this);
    getHead()->addEdge(this);
  }
  virtual ~Edge() { } // if (getTail()) getTail()->removeEdge(this); if (getHead()) getHead()->removeEdge(this); }
  tail_t* getTail() { return mTail; }
  head_t* getHead() { return mHead; }

  virtual void disconnect(Node* node) {
    if (node == mTail) mTail = nullptr;
    if (node == mHead) mHead = nullptr;
  }

private:
  tail_t* mTail;
  head_t* mHead;

};


template <typename tail_t, typename head_t>
Edge<tail_t, head_t>* connect(tail_t* tail, head_t* head) {
  return new Edge<tail_t, head_t>(tail, head);
}


} // namespace cdg

#endif
