/*
 * gvtable.h
 */

#ifndef CDG_GVTABLE_H
#define CDG_GVTABLE_H

#include <algorithm>
#include <map>
#include <sstream>
#include <string>
#include <vector>

#include "./gvtablerow.h"

namespace cdg {


class GvTable {
public:

  void setCell(int row, int col, std::string content) {
    while (mRows.size() <= row) {
      addRow(GvTableRow());
    }
    getRow(row).setCell(col, content);
  }

  void setCell(int row, int col, GvTableCell cell) {
    while (mRows.size() <= row) {
      addRow(GvTableRow());
    }
    getRow(row).setCell(col, cell);
  }

  GvTableCell& getCell(int row, int col) {
    return getRow(row).getCell(col);
  }

  void addRow(GvTableRow row) {
    mRows.push_back(row);
  }

  GvTableRow& getRow(int row) {
    return mRows.at(row);
  }

  GvTableRow& operator[](int row) {
    return getRow(row);
  }

  void setAttribute(std::string name, std::string value) {
    mAttributes[name] = value;
  }

  std::string getAttribute(std::string key) {
    return mAttributes[key];
  }

  std::string to_string() {
    expandCells();
    std::stringstream ss;
    ss << "<<TABLE";
    for (auto p : mAttributes) {
      std::string key = p.first;
      std::string value = p.second;
      if (value != "") {
        ss << " " << key << "=\"" << value << "\"";
      }
    }
    ss << ">";
    for (auto& row : mRows) {
      ss << row.to_string();
    }
    ss << "</TABLE>>";
    return ss.str();
  }

  int size() {
    int size = 0;
    for (auto& row : mRows) {
      size += row.size();
    }
    return size;
  }

  int rows() {
    return mRows.size();
  }

  int cols() {
    int cols = 0;
    for (auto& row : mRows) {
      cols = std::max(cols, row.size());
    }
    return cols;
  }

  void expandCells() {
    for (auto& row : mRows) {
      auto& cells = row.getCells();
      for (auto cell_it = cells.begin(); cell_it != cells.end();) {
        auto& cell = *cell_it;
        ++cell_it;  // Increment early so we can tell if the one we captured is the last one
        if (cell.getAttribute("colspan") == "0") {
          if (cell_it == cells.end()) {
            cell.setAttribute("colspan", std::to_string(cols() - row.size() + 1));
          }
          else {
            cell.setAttribute("colspan", "1");
          }
        }
      }
    }
  }

private:
  std::map<std::string, std::string> mAttributes;
  std::vector<GvTableRow> mRows;

};


} // namespace cdg


#endif
