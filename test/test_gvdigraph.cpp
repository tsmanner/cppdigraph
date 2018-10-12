/*
 * Unit Tests for cdg::GvDiGraph
 *   Graphviz Directed Graph
 */

#include "digraph.h"
#include "node.h"
#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include <cstdlib>
#include <fstream>

using namespace cdg;


namespace {


TEST(TestGvDiGraph, to_string_empty) {
  DiGraph dg = DiGraph("test_digraph");
  std::string expected = "\
digraph \"test_digraph\" {\n\
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
  \"n0\"\n\
  \"n1\"\n\
}\n\
";
  EXPECT_EQ(expected, dg.to_graphviz().to_string());
  delete n0;
  delete n1;
}


TEST(TestGvDiGraph, to_string_with_subgraph) {
  DiGraph dg = DiGraph("test_digraph");
  Node* n0 = new Node(&dg, "n0");
  Node* n1 = new Node(&dg, "n1");
  std::map<std::string, cdg::NodeSet> subgraphs = {
    {"test_subgraph", { n0 } }
  };
  std::string expected = "\
digraph \"test_digraph\" {\n\
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


TEST(TestGvDiGraph, to_string_with_subgraph_nullptr) {
  DiGraph dg = DiGraph("test_digraph");
  Node* n0 = new Node(&dg, "n0");
  Node* n1 = new Node(&dg, "n1");
  std::map<std::string, cdg::NodeSet> subgraphs = {
    {"test_subgraph", { n0, nullptr } }
  };
  std::string expected = "\
digraph \"test_digraph\" {\n\
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


TEST(TestGvDiGraph, to_string_special_characters) {
  DiGraph dg = DiGraph("test.digraph");
  std::string expected = "\
digraph \"test.digraph\" {\n\
}\n\
";
  EXPECT_EQ(expected, dg.to_graphviz().to_string());
}


TEST(TestGvDiGraph, graphviz_dot) {
  DiGraph dg = DiGraph("test.digraph");
  Node* n0 = new Node(&dg, "n=1.2-3");
  Node* n1 = new Node(&dg, "n1");
  connect(n0, n1);
  GvDiGraph gvdg = dg.to_graphviz();
  GvNode* gvn0 = gvdg.get(n0);
  gvn0->setTableCell(0, 0, n0->getName());
  gvn0->setTableCell(1, 0, "id=1.2-3");

  std::ofstream gvStream;
  gvStream.open("integration.dot");
  gvStream << gvdg;
  gvStream.close();

  int rc = std::system("dot -Tpng -O integration.dot");
  EXPECT_EQ(0, rc);

  delete n0;
}


}
