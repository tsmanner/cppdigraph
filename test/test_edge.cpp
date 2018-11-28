/*
 * 
 */

#include <string>

#include "edge.h"
#include "node.h"
#include "gtest/gtest.h"
#include "gmock/gmock.h"


// Use an anonymous namespace to isolate the tests.
namespace test_edge {

using namespace cdg;
using namespace testing;


class MockNode: public Node {
public:
  MockNode(std::string name): Node(name) {}
  MOCK_METHOD1(addEdge, void(EdgeBase*));
  MOCK_METHOD1(removeEdge, void(EdgeBase*));
};


TEST(TestEdge, constructor) {
  // Setup
  MockNode* n0 = new MockNode("n0");
  MockNode* n1 = new MockNode("n1");
  // Expect
  EXPECT_CALL(*n0, addEdge(_));
  EXPECT_CALL(*n1, addEdge(_));
  EXPECT_CALL(*n0, removeEdge(_));
  EXPECT_CALL(*n1, removeEdge(_));
  // Execute
  auto edge = new Edge<MockNode, MockNode>(n0, n1);
  // Cleanup
  delete edge;
  delete n0;
  delete n1;
}


TEST(TestEdge, getTail) {
  // Setup
  MockNode* n0 = new NiceMock<MockNode>("n0");
  MockNode* n1 = new NiceMock<MockNode>("n1");
  auto edge = new Edge<MockNode, MockNode>(n0, n1);
  // Execute
  EXPECT_EQ(edge->getTail(), n0);
  // Cleanup
  delete edge;
  delete n0;
  delete n1;
}


TEST(TestEdge, getHead) {
  // Setup
  MockNode* n0 = new NiceMock<MockNode>("n0");
  MockNode* n1 = new NiceMock<MockNode>("n1");
  auto edge = new Edge<MockNode, MockNode>(n0, n1);
  // Execute
  EXPECT_EQ(edge->getHead(), n1);
  // Cleanup
  delete edge;
  delete n0;
  delete n1;
}


} // namespace
