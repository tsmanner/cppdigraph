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

// Use an namespace to isolate the tests.
namespace test_relationship {


class TestNodeB;


class TestNodeA: public Node
               , public Relationship<TestNodeA, TestNodeA>
               , public Relationship<TestNodeA, TestNodeB> {
public:
  TestNodeA(std::string name
         ): Node(name)
          , Relationship<TestNodeA, TestNodeA>()
          , Relationship<TestNodeA, TestNodeB>()
  {
  }

private:

};


class TestNodeB: public Node
               , public Relationship<TestNodeA, TestNodeB>
               , public Relationship<TestNodeB, TestNodeB>
{
public:
  TestNodeB(std::string name
         ): Node(name)
          , Relationship<TestNodeA, TestNodeB>()
          , Relationship<TestNodeB, TestNodeB>()
  {
  }

private:

};


TEST(TestRelationship, connector) {
  TestNodeA* na = nullptr;
  TestNodeA* a = new TestNodeA("ra");
  TestNodeB* nb = nullptr;
  TestNodeB* b = new TestNodeB("wr");
  Relationship<TestNodeA, TestNodeA>::connector<Edge>()(na, a);
  Relationship<TestNodeA, TestNodeB>::connector<Edge>()(a, b);
  Relationship<TestNodeB, TestNodeB>::connector<Edge>()(b, nb);
  auto a_aa_prev = a->Relationship<TestNodeA, TestNodeA>::getPrev();
  auto a_aa_next = a->Relationship<TestNodeA, TestNodeA>::getNext();
  auto a_ab_prev = a->Relationship<TestNodeA, TestNodeB>::getPrev();
  auto a_ab_next = a->Relationship<TestNodeA, TestNodeB>::getNext();
  auto b_ab_prev = b->Relationship<TestNodeA, TestNodeB>::getPrev();
  auto b_ab_next = b->Relationship<TestNodeA, TestNodeB>::getNext();
  auto b_bb_prev = b->Relationship<TestNodeB, TestNodeB>::getPrev();
  auto b_bb_next = b->Relationship<TestNodeB, TestNodeB>::getNext();
  EXPECT_EQ(a_aa_prev, nullptr);
  EXPECT_EQ(a_aa_next, nullptr);
  EXPECT_EQ(a_ab_prev, nullptr);
  EXPECT_EQ(a_ab_next, b);
  EXPECT_EQ(b_ab_prev, a);
  EXPECT_EQ(b_ab_next, nullptr);
  EXPECT_EQ(b_bb_prev, nullptr);
  EXPECT_EQ(b_bb_next, nullptr);
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
