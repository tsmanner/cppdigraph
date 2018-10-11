/*
 * gvtablerow.h
 */

#ifndef CDG_GVTABLEROW_H
#define CDG_GVTABLEROW_H

#include <map>
#include <sstream>
#include <string>
#include <vector>

#include "./gvtablecell.h"


namespace cdg {


class GvTableRow {
public:

  void addCell(GvTableCell cell) {
    mCells.push_back(cell);
  }

  std::vector<GvTableCell> getCells() {
    return mCells;
  }

  void setAttribute(std::string name, std::string value) {
    mAttributes[name] = value;
  }

  std::string getAttribute(std::string key) {
    return mAttributes[key];
  }

  std::string to_string() {
    std::stringstream ss;
    ss << "<TR";
    for (auto p : mAttributes) {
      std::string key = p.first;
      std::string value = p.second;
      ss << " " << key << "=\"" << value << "\"";
    }
    ss << ">";
    for (auto& cell : mCells) {
      ss << cell.to_string();
    }
    ss << "</TR>";
    return ss.str();
  }

  int size() {
    return mCells.size();
  }

private:
  std::map<std::string, std::string> mAttributes;
  std::vector<GvTableCell> mCells;

};


} // namespace cdg


#endif
