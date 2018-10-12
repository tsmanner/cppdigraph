/*
 * Unit Tests for cdg::GvTableCell
 */

#include "graphviz/gvtablecell.h"
#include "gtest/gtest.h"

using namespace cdg;


// Use an anonymous namespace to isolate the tests.
namespace {


TEST(TestGvTableCell, to_string_no_attribute) {
  GvTableCell cell = GvTableCell();
  cell.setContent("rawr");
  std::string expected = "<TD>rawr</TD>";
  EXPECT_EQ(expected, cell.to_string());
}


TEST(TestGvTableCell, to_string_with_attribute) {
  GvTableCell cell = GvTableCell();
  cell.setContent("rawr");
  cell.setAttribute("attr", "test");
  std::string expected = "<TD attr=\"test\">rawr</TD>";
  EXPECT_EQ(expected, cell.to_string());
}


}
