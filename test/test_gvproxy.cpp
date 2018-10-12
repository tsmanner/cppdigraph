/*
 * Unit Tests for cdg::GvProxy
 */

#include "graphviz/gvproxy.h"
#include "gtest/gtest.h"
#include "gmock/gmock.h"

using namespace cdg;
using namespace testing;


class ProxyObject {
public:
  ProxyObject(std::string name): mName(name) {}
  std::map<std::string, std::string> graphviz_attributes() { return mAttributes; }
  std::string graphviz_name() { return mName; }
  std::string _graphviz_name() { return "\"" + graphviz_name() + "\""; }
  GvTable graphviz_table() { return mTable; };

  std::map<std::string, std::string> mAttributes;
  std::string mName;
  GvTable mTable;
};


typedef GvProxy<ProxyObject> TestProxy;

// Use an anonymous namespace to isolate the tests.
namespace {


TEST(TestGvProxy, to_string_no_table_no_attributes) {
  ProxyObject* proxyobject = new ProxyObject("ProxyObject");
  TestProxy proxy = TestProxy(proxyobject);
  std::string expected = "\"ProxyObject\"";
  EXPECT_EQ(expected, proxy.to_string());
  delete proxyobject;
}


TEST(TestGvProxy, to_string_with_table_no_attributes) {
  ProxyObject* proxyobject = new ProxyObject("ProxyObject");
  GvTableRow row = GvTableRow();
  GvTableCell cell = GvTableCell();
  cell.setContent("test");
  row.addCell(cell);
  proxyobject->mTable.addRow(row);
  TestProxy proxy = TestProxy(proxyobject);
  std::string expected = "\"ProxyObject\" [ label=<<TABLE><TR><TD>test</TD></TR></TABLE>> margin=\"0\" shape=\"none\" ]";
  EXPECT_EQ(expected, proxy.to_string());
  delete proxyobject;
}


TEST(TestGvProxy, to_string_no_table_with_attributes) {
  ProxyObject* proxyobject = new ProxyObject("ProxyObject");
  proxyobject->mAttributes["attr"] = "test";
  TestProxy proxy = TestProxy(proxyobject);
  std::string expected = "\"ProxyObject\" [ attr=\"test\" ]";
  EXPECT_EQ(expected, proxy.to_string());
  delete proxyobject;
}


TEST(TestGvProxy, to_string_with_table_with_attributes) {
  ProxyObject* proxyobject = new ProxyObject("ProxyObject");
  GvTableRow row = GvTableRow();
  GvTableCell cell = GvTableCell();
  row.addCell(cell);
  proxyobject->mTable.addRow(row);
  proxyobject->mAttributes["attr"] = "test";
  TestProxy proxy = TestProxy(proxyobject);
  std::string expected = "\"ProxyObject\" [ attr=\"test\" label=<<TABLE><TR><TD></TD></TR></TABLE>> margin=\"0\" shape=\"none\" ]";
  EXPECT_EQ(expected, proxy.to_string());
  delete proxyobject;
}


 }
