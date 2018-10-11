/*
 * Unit Tests for cdg::GvDiGraph
 *   Graphviz Directed Graph
 */

#include "digraph.h"
#include "node.h"
#include "gtest/gtest.h"
#include "gmock/gmock.h"

using namespace cdg;


namespace {


TEST(TestGvDiGraph, to_graphviz_empty) {
  DiGraph dg = DiGraph("test_digraph");
  std::string expected = "\
digraph \"test_digraph\" {\n\
  bgcolor = \"transparent\"\n\
}\n\
";
  EXPECT_EQ(expected, dg.to_graphviz().to_string());
}


TEST(TestGvDiGraph, to_graphviz) {
  DiGraph dg = DiGraph("test_digraph");
  Node* n0 = new Node(&dg, "n0");
  Node* n1 = new Node(&dg, "n1");
  std::string expected = "\
digraph \"test_digraph\" {\n\
  bgcolor = \"transparent\"\n\
  \"n0\"\n\
  \"n1\"\n\
}\n\
";
  EXPECT_EQ(expected, dg.to_graphviz().to_string());
  delete n0;
  delete n1;
}


TEST(TestGvDiGraph, to_graphviz_with_subgraph) {
  DiGraph dg = DiGraph("test_digraph");
  Node* n0 = new Node(&dg, "n0");
  Node* n1 = new Node(&dg, "n1");
  std::map<std::string, cdg::NodeSet> subgraphs = {
    {"test_subgraph", { n0 } }
  };
  std::string expected = "\
digraph \"test_digraph\" {\n\
  bgcolor = \"transparent\"\n\
  \"n0\"\n\
  \"n1\"\n\
  subgraph \"cluster_test_subgraph\" {\n\
    label = \"test_subgraph\"\n\
    rawr = \"rawr\"\n\
    \"n0\"\n\
  }\n\
}\n\
";
  auto graphviz = dg.to_graphviz();
  for (auto p : subgraphs) {
    graphviz.addSubgraph(p.first, p.second);
  }
  graphviz.getSubgraph("test_subgraph").setAttribute("rawr", "rawr");
  EXPECT_EQ(expected, graphviz.to_string());
  delete n0;
  delete n1;
}


TEST(TestGvDiGraph, to_graphviz_with_subgraph_nullptr) {
  DiGraph dg = DiGraph("test_digraph");
  Node* n0 = new Node(&dg, "n0");
  Node* n1 = new Node(&dg, "n1");
  std::map<std::string, cdg::NodeSet> subgraphs = {
    {"test_subgraph", { n0, nullptr } }
  };
  std::string expected = "\
digraph \"test_digraph\" {\n\
  bgcolor = \"transparent\"\n\
  \"n0\"\n\
  \"n1\"\n\
  subgraph \"cluster_test_subgraph\" {\n\
    label = \"test_subgraph\"\n\
    \"n0\"\n\
  }\n\
}\n\
";
  auto graphviz = dg.to_graphviz();
  for (auto p : subgraphs) {
    graphviz.addSubgraph(p.first, p.second);
  }
  EXPECT_EQ(expected, graphviz.to_string());
  delete n0;
  delete n1;
}


}
