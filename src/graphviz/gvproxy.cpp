/*
 * gvproxy.cpp
 */
#ifndef CDG_GRAPHVIZ_PROXY_C
#define CDG_GRAPHVIZ_PROXY_C

#include "./gvproxy.h"


namespace cdg {


template <typename T>
GvProxy<T>::GvProxy(T* object): mObject(object) {
}


template <typename T>
GvProxy<T>::~GvProxy() {
}


template <typename T>
T* GvProxy<T>::getObject() {
  return mObject;
}


template <typename T>
void GvProxy<T>::setAttribute(std::string name, std::string value) {
  mAttributes[name] = value;
}


template <typename T>
std::string GvProxy<T>::getAttribute(std::string key) {
  return mAttributes[key];
}


template <typename T>
std::string GvProxy<T>::to_string() {
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


template <typename T>
int GvProxy<T>::getCdgId() {
  if (getObject()) {
    return getObject()->getCdgId();
  }
  return 0;
}


} // namespace cdg


#endif
