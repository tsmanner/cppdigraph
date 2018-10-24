/*
 * iteration.h
 */

#ifndef CDG_ITERATION_H
#define CDG_ITERATION_H


#include <list>


namespace cdg {


template <typename NodeType>
class Chain {
public:
  /*
   * Iterator
   */
  class chain_iterator {
  public:
    chain_iterator(Chain* chain, NodeType* node): mChain(chain), mNode(node) {}

    NodeType* operator*() {
      return mNode;
    }

    // Pre-increment
    chain_iterator operator++() {
      mNode = mChain->getNext(mNode);
      return *this;
    }

    // Post-increment
    chain_iterator operator++(int) {
      chain_iterator newIterator = chain_iterator(mChain, mNode);
      mNode = mChain->getNext(mNode);
      return newIterator;
    }

    bool operator==(chain_iterator other) {
      return (**this) == (*other);
    }

    bool operator!=(chain_iterator other) {
      return ! ((*this) == other);
    }

  private:
    Chain* mChain;
    NodeType* mNode;

  };

  /*
   * Chain Definition
   */
  Chain(NodeType* front
     ): mFront(front)
      , mBegin(chain_iterator(this, front))
      , mEnd(chain_iterator(this, nullptr))
  {
  }

  virtual NodeType* getNext(NodeType* node) = 0;
  chain_iterator begin() { return mBegin; }
  chain_iterator end() { return mEnd; }

private:
  NodeType* mFront;
  const chain_iterator mBegin;
  const chain_iterator mEnd;

};


}


#endif
