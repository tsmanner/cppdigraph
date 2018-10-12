/*
 * gvproxy.h
 */
#ifndef CDG_GRAPHVIZ_PROXY_H
#define CDG_GRAPHVIZ_PROXY_H

#include <iostream>

#include <map>
#include <sstream>
#include <string>

#include "./gvtable.h"
#include "../utility.h"

namespace cdg {


template <typename T>
class GvProxy {
public:
  GvProxy(T* object): mObject(object) { reset(); }

  ~GvProxy() {}

  T* getObject() {
    return mObject;
  }

  void setAttribute(std::string name, std::string value) {
    mObjectAttributes[name] = value;
    render();
  }

  std::string getAttribute(std::string key) {
    return mObjectAttributes[key];
  }

  void setObjectName(std::string name) {
    mObjectName = name;
  }

  std::string getObjectName() {
    return mObjectName;
  }

  void setTableCell(int row, int col, std::string value) {
    mObjectTable.setCell(row, col, value);
    render();
  }

  void setTableCell(int row, int col, GvTableCell value) {
    mObjectTable.setCell(row, col, value);
    render();
  }

  GvTableCell& getTableCell(int row, int col) {
    return mObjectTable[row][col];
  }

  GvTable& getTable() {
    return mObjectTable;
  }

  void reset() {
    if (getObject()) {
      mObjectAttributes = getObject()->graphviz_attributes();
      mObjectName = getObject()->_graphviz_name();
      mObjectTable = getObject()->graphviz_table();
    }
  }

  void render() {
    if (getObject()) {
      if (mObjectTable.size()) {
        mObjectAttributes["shape"] = "none";
        mObjectAttributes["margin"] = "0";
        mObjectAttributes["label"] = mObjectTable.to_string();
      }
    }
  }

  std::string to_string() {
    render();
    std::stringstream ss;
    if (getObject()) {
      ss << graphviz_sanitize(getObjectName());
      if (mObjectAttributes.size()) {
        ss << " [ ";
        for (auto p : mObjectAttributes) {
          // Quotes around <<TABLE></TABLE>> renders it as a literal string...
          if (mObjectTable.size() and p.first == "label") {
            ss << graphviz_sanitize(p.first) << "="
               << graphviz_sanitize(p.second) << " ";
          }
          else {
            ss << graphviz_sanitize(p.first) << "=\""
               << graphviz_sanitize(p.second) << "\" ";
          }
        }
        ss << "]";
      }
    }
    return ss.str();
  }

  int getCdgId() {
    if (getObject()) {
      return getObject()->getCdgId();
    }
    return 0;
  }

private:
  T* mObject;
  std::map<std::string, std::string> mObjectAttributes;
  std::string mObjectName;
  GvTable mObjectTable;


};


class Node;
typedef GvProxy<Node> GvNode;

class EdgeBase;
typedef GvProxy<EdgeBase> GvEdge;


} // namespace cdg


#endif
