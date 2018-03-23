/*
 *
 */
 
#ifndef CDG_EDGE_H
#define CDG_EDGE_H

#include "node.h"


#define EDGE(__name, __head_type, __tail_type) \
class __name: public CdgEdge { \
public: \
  __name(__head_type* head, __tail_type* tail): mName(#__name), mHead(head), mTail(tail) {} \
 \
  __head_type* getHead() { return mHead; } \
  __tail_type* getTail() { return mTail; } \
 \
private: \
  const string mName; \
};


template <typename head_t, typename tail_t>
class CdgEdge {
public:
  CdgEdge(head_t& head, tail_t& tail): mHead(head), mTail(tail) {}

  head_t& getHead() { return mHead; }
  tail_t& getTail() { return mTail; }

private:
  head_t& mHead;
  tail_t& mTail;

};

#endif
