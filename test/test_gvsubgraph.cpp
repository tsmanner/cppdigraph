/*
 * Unit Tests for cdg::GvSubGraph
 */

#include "graphviz/gvtablerow.h"
#include "gtest/gtest.h"

using namespace cdg;


// Use an namespace to isolate the tests.
namespace test_gvsubgraph {


TEST(TestGvTableRow, to_string_no_cell_no_attribute) {
  GvTableRow row = GvTableRow();
  std::string expected = "<TR></TR>";
  EXPECT_EQ(expected, row.to_string());
}


TEST(TestGvTableRow, to_string_with_cell_no_attribute) {
  GvTableRow row = GvTableRow();
  GvTableCell cell = GvTableCell();
  cell.setContent("rawr");
  row.addCell(cell);
  std::string expected = "<TR><TD>\"rawr\"</TD></TR>";
  EXPECT_EQ(expected, row.to_string());
}


TEST(TestGvTableRow, to_string_no_cell_with_attribute) {
  GvTableRow row = GvTableRow();
  row.setAttribute("attr", "test");
  std::string expected = "<TR attr=\"test\"></TR>";
  EXPECT_EQ(expected, row.to_string());
}


TEST(TestGvTableRow, to_string_with_cell_with_attribute) {
  GvTableRow row = GvTableRow();
  row.setAttribute("attr", "test");
  GvTableCell cell = GvTableCell();
  cell.setContent("rawr");
  row.addCell(cell);
  std::string expected = "<TR attr=\"test\"><TD>\"rawr\"</TD></TR>";
  EXPECT_EQ(expected, row.to_string());
}


TEST(TestGvTableRow, size) {
  GvTableRow row = GvTableRow();
  GvTableCell cell = GvTableCell();
  cell.setContent("rawr");
  row.addCell(cell);
  int expected = 1;
  EXPECT_EQ(expected, row.size());
}


}
