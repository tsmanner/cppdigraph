/*
 * Unit Tests for cdg::GvTableRow
 */

#include "graphviz/gvtablerow.h"
#include "gtest/gtest.h"

using namespace cdg;


// Use an anonymous namespace to isolate the tests.
namespace {


TEST(TestGvTableRow, setCell_string) {
  GvTableRow row = GvTableRow();
  std::string expected = "rawr";
  row.setCell(1, expected);
  EXPECT_EQ(expected, row.getCell(1).getContent());
  EXPECT_EQ("", row.getCell(0).getContent());
}


TEST(TestGvTableRow, setCell_GvTableCell) {
  GvTableRow row = GvTableRow();
  std::string expected = "rawr";
  GvTableCell cell = GvTableCell();
  cell.setContent(expected);
  row.setCell(1, cell);
  EXPECT_EQ(expected, row.getCell(1).getContent());
  EXPECT_EQ("", row.getCell(0).getContent());
}


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
