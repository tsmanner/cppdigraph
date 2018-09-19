/*
 * Unit Tests for cdg::DiGraph
 */

#include "digraph.h"
#include "node.h"
#include "gtest/gtest.h"
#include "gmock/gmock.h"

using namespace cdg;


// Use an anonymous namespace to isolate the tests.
namespace {


TEST(TestDiGraph, to_graphviz_empty) {
  DiGraph dg = DiGraph("test_digraph");
  std::string expected = "\
digraph test_digraph {\n\
}\
";
  EXPECT_EQ(expected, dg.to_graphviz());
}


TEST(TestDiGraph, to_graphviz) {
  DiGraph dg = DiGraph("test_digraph");
  Node n0 = Node(&dg, "n0");
  Node n1 = Node(&dg, "n1");
  std::string expected = "\
digraph test_digraph {\n\
  n0;\n\
  n1;\n\
}\
";
  EXPECT_EQ(expected, dg.to_graphviz());
}


TEST(TestDiGraph, to_graphviz_with_subgraph) {
  DiGraph dg = DiGraph("test_digraph");
  Node n0 = Node(&dg, "n0");
  Node n1 = Node(&dg, "n1");
  std::map<std::string, std::set<cdg::Node*>> subgraphs = {
    {"test_subgraph", { &n0 } }
  };
  std::string expected = "\
digraph test_digraph {\n\
  n0;\n\
  n1;\n\
  subgraph cluster_test_subgraph {\n\
    label = \"test_subgraph\";\n\
    n0;\n\
  }\n\
}\
";
  EXPECT_EQ(expected, dg.to_graphviz(subgraphs));
}


TEST(TestDiGraph, to_graphviz_with_subgraph_nullptr) {
  DiGraph dg = DiGraph("test_digraph");
  Node n0 = Node(&dg, "n0");
  Node n1 = Node(&dg, "n1");
  std::map<std::string, std::set<cdg::Node*>> subgraphs = {
    {"test_subgraph", { &n0, nullptr } }
  };
  std::string expected = "\
digraph test_digraph {\n\
  n0;\n\
  n1;\n\
  subgraph cluster_test_subgraph {\n\
    label = \"test_subgraph\";\n\
    n0;\n\
  }\n\
}\
";
  EXPECT_EQ(expected, dg.to_graphviz(subgraphs));
}


}
