/*
 * gvproxy.h
 */
#ifndef CDG_GRAPHVIZ_PROXY_H
#define CDG_GRAPHVIZ_PROXY_H

#include <map>
#include <sstream>
#include <string>

#include "./gvtable.h"


namespace cdg {


template <typename T>
class GvProxy {
public:
  GvProxy(T* object): mObject(object) {}

  ~GvProxy() {}

  T* getObject() {
    return mObject;
  }

  void setAttribute(std::string name, std::string value) {
    mAttributes[name] = value;
  }

  std::string getAttribute(std::string key) {
    return mAttributes[key];
  }

  std::string to_string() {
    std::stringstream ss;
    if (getObject()) {
      ss << "\"" << getObject()->graphviz_name() << "\"";
      std::map<std::string, std::string> attributes = getObject()->graphviz_attributes();
      GvTable gvtable = getObject()->graphviz_table();
      if (gvtable.size()) {
        attributes["shape"] = "none";
        attributes["margin"] = "0";
        attributes["label"] = gvtable.to_string();
      }
      if (attributes.size()) {
        ss << " [ ";
        for (auto p : attributes) {
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
  std::map<std::string, std::string> mAttributes;

  T* mObject;

};


class Node;
typedef GvProxy<Node> GvNode;

class EdgeBase;
typedef GvProxy<EdgeBase> GvEdge;


} // namespace cdg


#endif
