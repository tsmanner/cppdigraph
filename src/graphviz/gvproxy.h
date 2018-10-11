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


namespace cdg {


static const std::vector<std::string> cGraphvizSpecialCharacters = {
  ".",
  "-"
};


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
    mObjectTable[row][col].setContent(value);
    render();
  }

  std::string getTableCell(int row, int col) {
    return mObjectTable[row][col];
  }

  void reset() {
    if (getObject()) {
      mObjectAttributes = getObject()->graphviz_attributes();
      mObjectName = getObject()->graphviz_name();
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
      ss << "\"" << getObjectName() << "\"";
      if (mObjectAttributes.size()) {
        ss << " [ ";
        for (auto p : mObjectAttributes) {
          std::string key = p.first;
          std::string value = p.second;
          ss << key << "=\"" << value << "\" ";
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
