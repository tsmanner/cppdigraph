/*
 * Unit Tests for cdg::GvFilter
 *   Graphviz Filter
 */

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "graphviz/gvfilter.h"
#include "digraph.h"
#include "edge.h"
#include "node.h"

using namespace cdg;
using namespace testing;


namespace test_gvfilter {


class MockNode: public Node {
public:
  MockNode(DiGraph* graph, std::string name): Node(graph, name) {}
  MOCK_METHOD2(applyFilter, void(GvFilter*, GvNode*));
};


class MockEdge: public Edge<MockNode, MockNode> {
public:
  MockEdge(DiGraph* graph, MockNode* tail, MockNode* head): Edge<MockNode, MockNode>(graph, tail, head) {}
  MOCK_METHOD2(applyFilter, void(GvFilter*, GvEdge*));
};


TEST(TestGvFilter, applyFilter) {
  DiGraph digraph = DiGraph("graph");
  MockNode* a = new MockNode(&digraph, "a");
  MockNode* b = new MockNode(&digraph, "b");
  MockEdge* e = new MockEdge(&digraph, a, b);

  EXPECT_CALL(*a, applyFilter(_, _));
  EXPECT_CALL(*b, applyFilter(_, _));
  EXPECT_CALL(*e, applyFilter(_, _));

  GvDiGraph gvdg = digraph.to_graphviz();
  GvFilter filter = GvFilter();
  gvdg.filter(filter);

  delete a;
  delete b;
  // delete e;
}


} // namespace cdg
