/*
 * Unit Tests for cdg::Chain
 */

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include <list>

#include "iteration.h"

using namespace cdg;


namespace test_bidirectionalchain {

class MockNode {
public:
  void setNext(MockNode* next) { mNext = next; }
  MockNode* getNext() { return mNext; }

  void setPrev(MockNode* prev) { mPrev = prev; }
  MockNode* getPrev() { return mPrev; }

private:
  MockNode* mNext;
  MockNode* mPrev;
};


class BidirectionalChainTraversal: public BidirectionalChain<MockNode> {
public:
  BidirectionalChainTraversal(MockNode* node): BidirectionalChain<MockNode>(node) {}

  MockNode* getNext(MockNode* node) {
    return node->getNext();
  }

  MockNode* getPrev(MockNode* node) {
    return node->getPrev();
  }

private:

};


////// BidirectionalChain


TEST(TestBidirectionalChain, PreIncrement) {
  MockNode* a = new MockNode();
  MockNode* b = new MockNode();
  a->setNext(b);
  b->setPrev(a);
  BidirectionalChainTraversal t = BidirectionalChainTraversal(a);
  BidirectionalChainTraversal::iterator it = t.begin();
  EXPECT_EQ(*it, a);
  EXPECT_EQ(*(++it), b);
  delete a;
  delete b;
}


TEST(TestBidirectionalChain, PostIncrement) {
  MockNode* a = new MockNode();
  MockNode* b = new MockNode();
  a->setNext(b);
  b->setPrev(a);
  BidirectionalChainTraversal t = BidirectionalChainTraversal(a);
  BidirectionalChainTraversal::iterator it = t.begin();
  EXPECT_EQ(*(it++), a);
  EXPECT_EQ(*it, b);
  delete a;
  delete b;
}


TEST(TestBidirectionalChain, PreDecrement) {
  MockNode* a = new MockNode();
  MockNode* b = new MockNode();
  a->setNext(b);
  b->setPrev(a);
  BidirectionalChainTraversal t = BidirectionalChainTraversal(b);
  BidirectionalChainTraversal::iterator it = t.begin();
  EXPECT_EQ(*it, b);
  EXPECT_EQ(*(--it), a);
  delete a;
  delete b;
}


TEST(TestBidirectionalChain, PostDecrement) {
  MockNode* a = new MockNode();
  MockNode* b = new MockNode();
  a->setNext(b);
  b->setPrev(a);
  BidirectionalChainTraversal t = BidirectionalChainTraversal(b);
  BidirectionalChainTraversal::iterator it = t.begin();
  EXPECT_EQ(*(it--), b);
  EXPECT_EQ(*it, a);
  delete a;
  delete b;
}


TEST(TestBidirectionalChain, ForTwo) {
  MockNode* a = new MockNode();
  MockNode* b = new MockNode();
  a->setNext(b);
  b->setPrev(a);
  std::list<MockNode*> traversal;
  BidirectionalChainTraversal t = BidirectionalChainTraversal(a);
  for (BidirectionalChainTraversal::iterator it = t.begin(); it != t.end(); ++it) {
    traversal.push_back(*it);
  }
  EXPECT_EQ(2, traversal.size());
  EXPECT_EQ(a, traversal.front());
  EXPECT_EQ(b, traversal.back());
  delete a;
  delete b;
}


TEST(TestBidirectionalChain, ForOne) {
  MockNode* a = new MockNode();
  std::list<MockNode*> traversal;
  BidirectionalChainTraversal t = BidirectionalChainTraversal(a);
  for (BidirectionalChainTraversal::iterator it = t.begin(); it != t.end(); ++it) {
    traversal.push_back(*it);
  }
  EXPECT_EQ(1, traversal.size());
  EXPECT_EQ(a, traversal.front());
  EXPECT_EQ(a, traversal.back());
  delete a;
}


TEST(TestBidirectionalChain, ForNone) {
  std::list<MockNode*> traversal;
  BidirectionalChainTraversal t = BidirectionalChainTraversal(nullptr);
  for (BidirectionalChainTraversal::iterator it = t.begin(); it != t.end(); ++it) {
    traversal.push_back(*it);
  }
  EXPECT_EQ(0, traversal.size());
}


TEST(TestBidirectionalChain, ForTwoDecr) {
  MockNode* a = new MockNode();
  MockNode* b = new MockNode();
  a->setNext(b);
  b->setPrev(a);
  std::list<MockNode*> traversal;
  BidirectionalChainTraversal t = BidirectionalChainTraversal(b);
  for (BidirectionalChainTraversal::iterator it = t.begin(); it != t.end(); --it) {
    traversal.push_back(*it);
  }
  EXPECT_EQ(2, traversal.size());
  EXPECT_EQ(b, traversal.front());
  EXPECT_EQ(a, traversal.back());
  delete a;
  delete b;
}


TEST(TestBidirectionalChain, ForOneDecr) {
  MockNode* a = new MockNode();
  std::list<MockNode*> traversal;
  BidirectionalChainTraversal t = BidirectionalChainTraversal(a);
  for (BidirectionalChainTraversal::iterator it = t.begin(); it != t.end(); --it) {
    traversal.push_back(*it);
  }
  EXPECT_EQ(1, traversal.size());
  EXPECT_EQ(a, traversal.front());
  EXPECT_EQ(a, traversal.back());
  delete a;
}


TEST(TestBidirectionalChain, ForNoneDecr) {
  std::list<MockNode*> traversal;
  BidirectionalChainTraversal t = BidirectionalChainTraversal(nullptr);
  for (BidirectionalChainTraversal::iterator it = t.begin(); it != t.end(); --it) {
    traversal.push_back(*it);
  }
  EXPECT_EQ(0, traversal.size());
}


TEST(TestBidirectionalChain, RangeTwo) {
  MockNode* a = new MockNode();
  MockNode* b = new MockNode();
  a->setNext(b);
  b->setPrev(a);
  std::list<MockNode*> traversal;
  for (auto node : BidirectionalChainTraversal(a)) {
    traversal.push_back(node);
  }
  EXPECT_EQ(2, traversal.size());
  EXPECT_EQ(a, traversal.front());
  EXPECT_EQ(b, traversal.back());
  delete a;
  delete b;
}


TEST(TestBidirectionalChain, RangeOne) {
  MockNode* a = new MockNode();
  std::list<MockNode*> traversal;
  for (auto node : BidirectionalChainTraversal(a)) {
    traversal.push_back(node);
  }
  EXPECT_EQ(1, traversal.size());
  EXPECT_EQ(a, traversal.front());
  EXPECT_EQ(a, traversal.back());
  delete a;
}


TEST(TestBidirectionalChain, RangeNone) {
  std::list<MockNode*> traversal;
  for (auto node : BidirectionalChainTraversal(nullptr)) {
    traversal.push_back(node);
  }
  EXPECT_EQ(0, traversal.size());
}


}
