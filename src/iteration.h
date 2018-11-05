/*
 * iteration.h
 */

#ifndef CDG_ITERATION_H
#define CDG_ITERATION_H


#include <list>


namespace cdg {

enum eIterationDirection { cForward, cReverse };



template <typename NodeType>
class Chain {
public:
  /*
   * Iterator
   */
  class iterator {
  public:
    iterator(Chain* chain, NodeType* node): mChain(chain), mNode(node) {}

    NodeType* operator*() {
      return mNode;
    }

    // Pre-increment
    iterator operator++() {
      mNode = mChain->getNext(mNode);
      return *this;
    }

    // Post-increment
    iterator operator++(int) {
      iterator newIterator = iterator(mChain, mNode);
      mNode = mChain->getNext(mNode);
      return newIterator;
    }

    bool operator==(iterator other) {
      return (**this) == (*other);
    }

    bool operator!=(iterator other) {
      return ! ((*this) == other);
    }

  protected:
    Chain* mChain;
    NodeType* mNode;

  };

  /*
   * Chain Definition
   */
  Chain(NodeType* front
     ): mFront(front)
      , mBegin(iterator(this, front))
      , mEnd(iterator(this, nullptr))
  {
  }

  virtual NodeType* getNext(NodeType* node) = 0;
  iterator begin() { return mBegin; }
  iterator end() { return mEnd; }

private:
  NodeType* mFront;
  const iterator mBegin;
  const iterator mEnd;

};


template <typename NodeType>
class BidirectionalChain: public Chain<NodeType> {
public:
  /*
   * Iterator
   */
  class iterator: public Chain<NodeType>::iterator {
  public:
    iterator(BidirectionalChain* chain, NodeType* node): Chain<NodeType>::iterator(chain, node), mBidirectionalChain(chain) {}


    // Pre-increment
    iterator operator++() {
      if (mBidirectionalChain->getDirection() == cForward) {
        this->mNode = mBidirectionalChain->getNext(this->mNode);
        return *this;
      } else {
        this->mNode = mBidirectionalChain->getPrev(this->mNode);
        return *this;
      }

    }

    // Post-increment
    iterator operator++(int) {
      if (mBidirectionalChain->getDirection() == cForward) {
        iterator newIterator = iterator(mBidirectionalChain, this->mNode);
        this->mNode = mBidirectionalChain->getNext(this->mNode);
        return newIterator;
      } else {
        iterator newIterator = iterator(mBidirectionalChain, this->mNode);
        this->mNode = mBidirectionalChain->getPrev(this->mNode);
        return newIterator;
      }
    }

    // Pre-decrement
    iterator operator--() {
      if (mBidirectionalChain->getDirection() == cReverse) {
        this->mNode = mBidirectionalChain->getNext(this->mNode);
        return *this;
      } else {
        this->mNode = mBidirectionalChain->getPrev(this->mNode);
        return *this;
      }
    }

    // Post-decrement
    iterator operator--(int) {
      if (mBidirectionalChain->getDirection() == cReverse) {
        iterator newIterator = iterator(mBidirectionalChain, this->mNode);
        this->mNode = mBidirectionalChain->getNext(this->mNode);
        return newIterator;
      } else {
        iterator newIterator = iterator(mBidirectionalChain, this->mNode);
        this->mNode = mBidirectionalChain->getPrev(this->mNode);
        return newIterator;
      }
    }

    bool operator==(iterator other) {
      return (**this) == (*other);
    }

    bool operator!=(iterator other) {
      return ! ((*this) == other);
    }

  protected:
    BidirectionalChain* mBidirectionalChain;
  };

  /*
   * BidirectionalChain Definition
   */
  BidirectionalChain(NodeType* front
                    , eIterationDirection direction = cForward 
                   ): Chain<NodeType>(front)
                    , mBegin(iterator(this, front))
                    , mEnd(iterator(this, nullptr))
                    , mDirection(direction)
  {
  }

  virtual NodeType* getPrev(NodeType* node) = 0;
  iterator begin() { return mBegin; }
  iterator end() { return mEnd; }
  eIterationDirection getDirection() { return mDirection; }

private:
  const iterator mBegin;
  const iterator mEnd;
  const eIterationDirection mDirection;


};

}


#endif
