/*
 * Unit Tests for cdg::Chain
 */

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include <list>

#include "iteration.h"

using namespace cdg;


namespace test_chain {

class MockNode {
public:
  void setNext(MockNode* next) { mNext = next; }
  MockNode* getNext() { return mNext; }

private:
  MockNode* mNext;
};


class ChainTraversal: public Chain<MockNode> {
public:
  ChainTraversal(MockNode* node): Chain<MockNode>(node) {}

  MockNode* getNext(MockNode* node) {
    return node->getNext();
  }

private:

};


TEST(TestChain, PreIncrement) {
  MockNode* a = new MockNode();
  MockNode* b = new MockNode();
  a->setNext(b);
  ChainTraversal t = ChainTraversal(a);
  ChainTraversal::iterator it = t.begin();
  EXPECT_EQ(*it, a);
  EXPECT_EQ(*(++it), b);
  delete a;
  delete b;
}


TEST(TestChain, PostIncrement) {
  MockNode* a = new MockNode();
  MockNode* b = new MockNode();
  a->setNext(b);
  ChainTraversal t = ChainTraversal(a);
  ChainTraversal::iterator it = t.begin();
  EXPECT_EQ(*(it++), a);
  EXPECT_EQ(*it, b);
  delete a;
  delete b;
}


TEST(TestChain, ForTwo) {
  MockNode* a = new MockNode();
  MockNode* b = new MockNode();
  a->setNext(b);
  std::list<MockNode*> traversal;
  ChainTraversal t = ChainTraversal(a);
  for (ChainTraversal::iterator it = t.begin(); it != t.end(); ++it) {
    traversal.push_back(*it);
  }
  EXPECT_EQ(2, traversal.size());
  EXPECT_EQ(a, traversal.front());
  EXPECT_EQ(b, traversal.back());
  delete a;
  delete b;
}


TEST(TestChain, ForOne) {
  MockNode* a = new MockNode();
  std::list<MockNode*> traversal;
  ChainTraversal t = ChainTraversal(a);
  for (ChainTraversal::iterator it = t.begin(); it != t.end(); ++it) {
    traversal.push_back(*it);
  }
  EXPECT_EQ(1, traversal.size());
  EXPECT_EQ(a, traversal.front());
  EXPECT_EQ(a, traversal.back());
  delete a;
}


TEST(TestChain, ForNone) {
  std::list<MockNode*> traversal;
  ChainTraversal t = ChainTraversal(nullptr);
  for (ChainTraversal::iterator it = t.begin(); it != t.end(); ++it) {
    traversal.push_back(*it);
  }
  EXPECT_EQ(0, traversal.size());
}


TEST(TestChain, RangeTwo) {
  MockNode* a = new MockNode();
  MockNode* b = new MockNode();
  a->setNext(b);
  std::list<MockNode*> traversal;
  for (auto node : ChainTraversal(a)) {
    traversal.push_back(node);
  }
  EXPECT_EQ(2, traversal.size());
  EXPECT_EQ(a, traversal.front());
  EXPECT_EQ(b, traversal.back());
  delete a;
  delete b;
}


TEST(TestChain, RangeOne) {
  MockNode* a = new MockNode();
  std::list<MockNode*> traversal;
  for (auto node : ChainTraversal(a)) {
    traversal.push_back(node);
  }
  EXPECT_EQ(1, traversal.size());
  EXPECT_EQ(a, traversal.front());
  EXPECT_EQ(a, traversal.back());
  delete a;
}


TEST(TestChain, RangeNone) {
  std::list<MockNode*> traversal;
  for (auto node : ChainTraversal(nullptr)) {
    traversal.push_back(node);
  }
  EXPECT_EQ(0, traversal.size());
}


}
