/*
 * Unit Tests for cdg::GvTable
 */

#include "graphviz/gvtable.h"
#include "gtest/gtest.h"

using namespace cdg;


// Use an anonymous namespace to isolate the tests.
namespace {


TEST(TestGvTable, setCell_0_0) {
  GvTable table = GvTable();
  std::string expected = "rawr";
  table.setCell(0, 0, expected);
  EXPECT_EQ(expected, table.getCell(0, 0).getContent());
}


TEST(TestGvTable, setCell_1_1) {
  GvTable table = GvTable();
  std::string expected = "rawr";
  table.setCell(1, 1, expected);
  EXPECT_EQ("", table.getCell(1, 0).getContent());
  EXPECT_EQ(expected, table.getCell(1, 1).getContent());
}


TEST(TestGvTable, to_string_no_rows_no_attributes) {
  GvTable table = GvTable();
  std::string expected = "<<TABLE></TABLE>>";
  EXPECT_EQ(expected, table.to_string());
}


TEST(TestGvTable, to_string_with_rows_no_attributes) {
  GvTable table = GvTable();
  GvTableRow row = GvTableRow();
  table.addRow(row);
  std::string expected = "<<TABLE><TR></TR></TABLE>>";
  EXPECT_EQ(expected, table.to_string());
}


TEST(TestGvTable, to_string_no_rows_with_attributes) {
  GvTable table = GvTable();
  table.setAttribute("attr", "test");
  std::string expected = "<<TABLE attr=\"test\"></TABLE>>";
  EXPECT_EQ(expected, table.to_string());
}


TEST(TestGvTable, to_string_with_rows_with_attributes) {
  GvTable table = GvTable();
  GvTableRow row = GvTableRow();
  table.addRow(row);
  table.setAttribute("attr", "test");
  std::string expected = "<<TABLE attr=\"test\"><TR></TR></TABLE>>";
  EXPECT_EQ(expected, table.to_string());
}


TEST(TestGvTable, size) {
  GvTable table = GvTable();
  GvTableCell cell = GvTableCell();
  GvTableRow row = GvTableRow();
  cell.setContent("rawr");
  row.addCell(cell);
  table.addRow(row);
  int expected = 1;
  EXPECT_EQ(expected, table.size());
}


TEST(TestGvTable, size_empty) {
  GvTable table = GvTable();
  int expected = 0;
  EXPECT_EQ(expected, table.size());
}


TEST(TestGvTable, size_empty_row) {
  GvTable table = GvTable();
  GvTableRow row = GvTableRow();
  table.addRow(row);
  int expected = 0;
  EXPECT_EQ(expected, table.size());
}


TEST(TestGvTable, cols) {
  GvTable table = GvTable();
  GvTableCell cell = GvTableCell();
  GvTableRow row = GvTableRow();
  cell.setContent("rawr");
  row.addCell(cell);
  table.addRow(row);
  int expected = 1;
  EXPECT_EQ(expected, table.cols());
}


TEST(TestGvTable, cols_empty) {
  GvTable table = GvTable();
  int expected = 0;
  EXPECT_EQ(expected, table.cols());
}


TEST(TestGvTable, cols_empty_row) {
  GvTable table = GvTable();
  GvTableRow row = GvTableRow();
  table.addRow(row);
  int expected = 0;
  EXPECT_EQ(expected, table.cols());
}


TEST(TestGvTable, cols_mismatched_row_length) {
  GvTable table = GvTable();
  GvTableCell cell = GvTableCell();
  GvTableRow row0 = GvTableRow();
  GvTableRow row1 = GvTableRow();
  cell.setContent("rawr");
  row0.addCell(cell);
  row1.addCell(cell);
  row1.addCell(cell);
  table.addRow(row0);
  table.addRow(row1);
  int expected = 2;
  EXPECT_EQ(expected, table.cols());
}


TEST(TestGvTable, expandCells_colspan0) {
  GvTable table = GvTable();
  GvTableCell cell = GvTableCell();
  GvTableRow row0 = GvTableRow();
  cell.setContent("rawr");
  row0.addCell(cell);
  table.addRow(row0);
  table[0][0].setAttribute("colspan", "0");
  table.expandCells();
  std::string expected = "1";
  EXPECT_EQ(expected, table[0][0].getAttribute("colspan"));
}


TEST(TestGvTable, expandCells_mismatched_row_length_colspan0) {
  GvTable table = GvTable();
  GvTableCell cell = GvTableCell();
  GvTableRow row0 = GvTableRow();
  GvTableRow row1 = GvTableRow();
  cell.setContent("rawr");
  row0.addCell(cell);
  row1.addCell(cell);
  row1.addCell(cell);
  table.addRow(row0);
  table.addRow(row1);
  table[0][0].setAttribute("colspan", "0");
  table.expandCells();
  std::string expected = "2";
  EXPECT_EQ(expected, table[0][0].getAttribute("colspan"));
}


}
