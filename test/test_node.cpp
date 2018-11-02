/*
 * 
 */

#include "node.h"
#include "digraph.h"
#include "gtest/gtest.h"
#include "gmock/gmock.h"

using namespace cdg;

// Use an namespace to isolate the tests.
namespace test_node {


class MockDiGraph: public DiGraph {
public:
  MockDiGraph(std::string name): DiGraph(name) {}
  MOCK_METHOD1(add, void(Node*));
};


TEST(TestNode, constructor) {
  MockDiGraph* mdg = new MockDiGraph("graph");
  EXPECT_EQ("rawr", Node(mdg, "rawr").getName());
  delete mdg;
}

} // namespace
