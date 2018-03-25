/*
 * Edge
 *   Base class for edges.  Templated with the endpoint types
 *   so that the head and tail are fully resolved when the edge
 *   is traversed.
 */
 
#ifndef CDG_EDGE_H
#define CDG_EDGE_H

#include <string>


namespace cdg {

/*
 * Edge
 *   Templated type for Edges.  Used in conjuction
 *   with macros from `node.h` to provide simple,
 *   fully resolved access to arbitrary connected
 *   Node types.
 */
template <typename tail_t, typename head_t>
class Edge {
public:
  Edge(tail_t& tail
     , head_t& head
    ): mName(tail.getName() + "->" + head.getName())
     , mTail(&tail)
     , mHead(&head)
  {
    tail.connectTail(this);
    head.connectHead(this);
  }

  ~Edge() {
    mTail->destructTail(this);
    mHead->destructHead(this);
  }

  const std::string getName() const { return mName; }
  tail_t& getTail() { return *mTail; }
  head_t& getHead() { return *mHead; }

private:
  const std::string mName;
  tail_t* mTail;
  head_t* mHead;

};

} // namespace cdg

#endif
