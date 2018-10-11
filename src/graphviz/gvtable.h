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

  void addRow(GvTableRow row) {
    mRows.push_back(row);
  }

  void setAttribute(std::string name, std::string value) {
    mAttributes[name] = value;
  }

  std::string getAttribute(std::string key) {
    return mAttributes[key];
  }

  std::string to_string() {
    std::stringstream ss;
    ss << "<<TABLE";
    for (auto p : mAttributes) {
      std::string key = p.first;
      std::string value = p.second;
      ss << " " << key << "=\"" << value << "\"";
    }
    ss << ">";
    for (auto row : mRows) {
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

private:
  std::map<std::string, std::string> mAttributes;
  std::vector<GvTableRow> mRows;

};


} // namespace cdg


#endif
