/*
 * 
 */

#include <limits.h>
#include "node.h"
#include "gtest/gtest.h"

using namespace cdg;

// Use an anonymous namespace to isolate the tests.
namespace {

TEST(TestNode, construction) {
  EXPECT_EQ("rawr", Node("rawr").getName());
}

} // namespace


// Do the unit tests
int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
