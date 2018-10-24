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

private:
  MockNode* mNext;
};


class Traversal: public Chain<MockNode> {
public:
  Traversal(MockNode* node): Chain<MockNode>(node) {}

  MockNode* getNext(MockNode* node) {
    return node->getNext();
  }

private:

};


TEST(TestIteration, PreIncrement) {
  MockNode* a = new MockNode();
  MockNode* b = new MockNode();
  a->setNext(b);
  Traversal t = Traversal(a);
  Traversal::chain_iterator it = t.begin();
  EXPECT_EQ(*it, a);
  EXPECT_EQ(*(++it), b);
  delete a;
  delete b;
}


TEST(TestIteration, PostIncrement) {
  MockNode* a = new MockNode();
  MockNode* b = new MockNode();
  a->setNext(b);
  Traversal t = Traversal(a);
  Traversal::chain_iterator it = t.begin();
  EXPECT_EQ(*(it++), a);
  EXPECT_EQ(*it, b);
  delete a;
  delete b;
}


TEST(TestIteration, ForTwo) {
  MockNode* a = new MockNode();
  MockNode* b = new MockNode();
  a->setNext(b);
  std::list<MockNode*> traversal;
  Traversal t = Traversal(a);
  for (Traversal::chain_iterator it = t.begin(); it != t.end(); ++it) {
    traversal.push_back(*it);
  }
  EXPECT_EQ(2, traversal.size());
  EXPECT_EQ(a, traversal.front());
  EXPECT_EQ(b, traversal.back());
  delete a;
  delete b;
}


TEST(TestIteration, ForOne) {
  MockNode* a = new MockNode();
  std::list<MockNode*> traversal;
  Traversal t = Traversal(a);
  for (Traversal::chain_iterator it = t.begin(); it != t.end(); ++it) {
    traversal.push_back(*it);
  }
  EXPECT_EQ(1, traversal.size());
  EXPECT_EQ(a, traversal.front());
  EXPECT_EQ(a, traversal.back());
  delete a;
}


TEST(TestIteration, ForNone) {
  std::list<MockNode*> traversal;
  Traversal t = Traversal(nullptr);
  for (Traversal::chain_iterator it = t.begin(); it != t.end(); ++it) {
    traversal.push_back(*it);
  }
  EXPECT_EQ(0, traversal.size());
}


TEST(TestIteration, RangeTwo) {
  MockNode* a = new MockNode();
  MockNode* b = new MockNode();
  a->setNext(b);
  std::list<MockNode*> traversal;
  for (auto node : Traversal(a)) {
    traversal.push_back(node);
  }
  EXPECT_EQ(2, traversal.size());
  EXPECT_EQ(a, traversal.front());
  EXPECT_EQ(b, traversal.back());
  delete a;
  delete b;
}


TEST(TestIteration, RangeOne) {
  MockNode* a = new MockNode();
  std::list<MockNode*> traversal;
  for (auto node : Traversal(a)) {
    traversal.push_back(node);
  }
  EXPECT_EQ(1, traversal.size());
  EXPECT_EQ(a, traversal.front());
  EXPECT_EQ(a, traversal.back());
  delete a;
}


TEST(TestIteration, RangeNone) {
  std::list<MockNode*> traversal;
  for (auto node : Traversal(nullptr)) {
    traversal.push_back(node);
  }
  EXPECT_EQ(0, traversal.size());
}


}
