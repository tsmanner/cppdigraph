/*
 * 
 */

#include <iostream>
#include <iomanip>
#include <string>

#include "node.h"
#include "relationship.h"
#include "gtest/gtest.h"
#include "gmock/gmock.h"

using namespace cdg;

// Use an anonymous namespace to isolate the tests.
namespace {


class TestNodeB;


class TestNodeA: public Node, public Relationship<TestNodeA, TestNodeB> {
public:
  TestNodeA(std::string name): Node(name), Relationship<TestNodeA, TestNodeB>() {}

private:

};


class TestNodeB: public Node
               , public Relationship<TestNodeA, TestNodeB>
               , public Relationship<TestNodeB, TestNodeB>
{
public:
  TestNodeB(std::string name): Node(name), Relationship<TestNodeA, TestNodeB>() {}

private:

};


TEST(TestRelationship, connector) {
  TestNodeA* a = new TestNodeA("ra");
  TestNodeB* b = new TestNodeB("wr");
  Relationship<TestNodeA, TestNodeB>::connector<Edge>()(a, b);
  auto anext = a->Relationship<TestNodeA, TestNodeB>::getNext();
  auto aprev = a->Relationship<TestNodeA, TestNodeB>::getPrev();
  auto bnext = b->Relationship<TestNodeA, TestNodeB>::getNext();
  auto bprev = b->Relationship<TestNodeA, TestNodeB>::getPrev();
  EXPECT_EQ(b, anext);
  EXPECT_EQ(nullptr, aprev);
  EXPECT_EQ(nullptr, bnext);
  EXPECT_EQ(a, bprev);
  delete a;
  delete b;
}


TEST(TestRelationship, disconnector) {
  TestNodeA* a = new TestNodeA("ra");
  TestNodeB* b = new TestNodeB("wr");
  Relationship<TestNodeA, TestNodeB>::connector<Edge>()(a, b);
  Relationship<TestNodeA, TestNodeB>::disconnector()(a, b);
  auto anext = a->Relationship<TestNodeA, TestNodeB>::getNext();
  auto aprev = a->Relationship<TestNodeA, TestNodeB>::getPrev();
  auto bnext = b->Relationship<TestNodeA, TestNodeB>::getNext();
  auto bprev = b->Relationship<TestNodeA, TestNodeB>::getPrev();
  EXPECT_EQ(nullptr, anext);
  EXPECT_EQ(nullptr, aprev);
  EXPECT_EQ(nullptr, bnext);
  EXPECT_EQ(nullptr, bprev);
  delete a;
  delete b;
}

} // namespace
