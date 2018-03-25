/*
 * edeg.h
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


template <typename tail_t, typename head_t> class Edge;

/*
 * Tail
 *   Handle for the tail of an edge used to implement a type
 *   aware `traverse` method.
 */
template <typename tail_t, typename head_t>
class Tail {
public:
  Tail(Edge<tail_t, head_t>* edge): mEdge(edge) {}

  head_t& traverse() { return mEdge->getHead(); }
  Edge<tail_t, head_t>* getEdge() { return mEdge; }

private:
  Edge<tail_t, head_t>* mEdge;

};


/*
 * Head
 *   Handle for the head of an edge used to implement a type
 *   aware `traverse` method.
 */
template <typename tail_t, typename head_t>
class Head {
public:
  Head(Edge<tail_t, head_t>* edge): mEdge(edge) {}

  tail_t& traverse() { return mEdge->getTail(); }
  Edge<tail_t, head_t>* getEdge() { return mEdge; }

private:
  Edge<tail_t, head_t>* mEdge;

};


/*
 * Edge
 *   Templated with the endpoint types so that the head and
 *   tail are fully resolved when the edge is traversed.
 */
template <typename tail_t, typename head_t>
class Edge {
public:
  Edge(tail_t& tail
     , head_t& head
    ): mName(tail.getName() + "->" + head.getName())
     , mTail(&tail)
     , mHead(&head)
     , mTailHandle(this)
     , mHeadHandle(this)
  {
    mTail->connectTail(&mTailHandle);
    mHead->connectHead(&mHeadHandle);
  }

  ~Edge() {
    mTail->destructTail(&mTailHandle);
    mHead->destructHead(&mHeadHandle);
  }

  const std::string getName() const { return mName; }
  tail_t& getTail() { return *mTail; }
  head_t& getHead() { return *mHead; }

private:
  const std::string mName;
  tail_t* mTail;
  head_t* mHead;

  Tail<tail_t, head_t> mTailHandle;
  Head<tail_t, head_t> mHeadHandle;

};


} // namespace cdg

#endif
