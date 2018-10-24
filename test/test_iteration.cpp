/*
 * Unit Tests for cdg::traverse
 */

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include <list>

#include "iteration.h"

using namespace cdg;


namespace {

class MockNode {
public:
  void setNext(MockNode* next) { mNext = next; }
  MockNode* getNext() { return mNext; }

  static MockNode* iterationFunction(MockNode* node) { return node->getNext(); }

private:
  MockNode* mNext;
};


TEST(TestIteration, two_nodes) {
  MockNode* a = new MockNode();
  MockNode* b = new MockNode();
  a->setNext(b);
  std::list<MockNode*> traversal = traverse<MockNode>(MockNode::iterationFunction, a);
  EXPECT_EQ(2, traversal.size());
  EXPECT_EQ(a, traversal.front());
  EXPECT_EQ(b, traversal.back());
}


TEST(TestIteration, one_node) {
  MockNode* a = new MockNode();
  std::list<MockNode*> traversal = traverse<MockNode>(MockNode::iterationFunction, a);
  EXPECT_EQ(1, traversal.size());
  EXPECT_EQ(a, traversal.front());
  EXPECT_EQ(a, traversal.back());
}


TEST(TestIteration, no_nodes) {
  std::list<MockNode*> traversal = traverse<MockNode>(MockNode::iterationFunction, nullptr);
  EXPECT_EQ(0, traversal.size());
}


}
