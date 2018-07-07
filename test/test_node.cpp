/*
 * 
 */

#include "node.h"
#include "gtest/gtest.h"

using namespace cdg;

// Use an anonymous namespace to isolate the tests.
namespace {

TEST(TestNode, constructor) {
  EXPECT_EQ("rawr", Node("rawr").getName());
}

} // namespace
