/*
 * gvtablecell.h
 */

#ifndef CDG_GVTABLECELL_H
#define CDG_GVTABLECELL_H

#include <map>
#include <sstream>
#include <string>
#include <vector>


namespace cdg {


class GvTableCell {
public:

  void setContent(std::string content) {
    mContent = content;
  }

  std::string getContent() {
    return mContent;
  }

  void setAttribute(std::string name, std::string value) {
    mAttributes[name] = value;
  }

  std::string getAttribute(std::string key) {
    return mAttributes[key];
  }

  std::string to_string() {
    std::stringstream ss;
    ss << "<TD";
    for (auto p : mAttributes) {
      std::string key = p.first;
      std::string value = p.second;
      ss << " " << key << "=\"" << value << "\"";
    }
    ss << ">";
    if (mContent.size()) {
      ss << "\"" << mContent << "\"";
    }
    ss << "</TD>";
    return ss.str();
  }

private:
  std::map<std::string, std::string> mAttributes;
  std::string mContent;

};


} // namespace cdg


#endif
