/*
 * 
 */

#include <string>

#include "edge.h"
#include "node.h"
#include "gtest/gtest.h"
#include "gmock/gmock.h"


// Use an anonymous namespace to isolate the tests.
namespace {
  using namespace cdg;
  using namespace testing;

class MockNode: public Node {
public:
  MockNode(std::string name): Node(name) {}
  // MockNode(MockNode& mn) {}
  MOCK_METHOD1(addEdge, void(EdgeBase*));
};

TEST(TestEdge, constructor) {
  MockNode* n0 = new MockNode("n0");
  MockNode* n1 = new MockNode("n1");
  EXPECT_CALL(*n0, addEdge(_));
  EXPECT_CALL(*n1, addEdge(_));
  new Edge<MockNode, MockNode>(n0, n1);
  delete n0;
  delete n1;
}

} // namespace
