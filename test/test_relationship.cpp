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
  EXPECT_EQ(b, a->getNext());
  delete a;
  delete b;
}

} // namespace
