/*
 * Edge
 *   Base class for edges.  Templated with the endpoint types
 *   so that the head and tail are fully resolved when the edge
 *   is traversed.
 */
 
#ifndef CDG_EDGE_H
#define CDG_EDGE_H


namespace cdg {


//                 tail ----------> head
template <typename tail_t, typename head_t>
class Edge {
public:
  Edge(tail_t& tail, head_t& head): mTail(&tail), mHead(&head) {
    tail.connectTail(this);
    head.connectHead(this);
  }

  ~Edge() {
    mTail->destructTail(this);
    mHead->destructHead(this);
  }

  tail_t& getTail() { return *mTail; }
  head_t& getHead() { return *mHead; }

private:
  tail_t* mTail;
  head_t* mHead;

};

} // namespace cdg

#endif
