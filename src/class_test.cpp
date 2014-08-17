#include "gtest/gtest.h"

#include "class.hpp"

namespace {
  class FooTest : public ::testing::Test {
   protected:
    FooTest() : foo("foo") {}

    virtual void SetUp() {

    }

    Foo foo;
  };

  TEST_F(FooTest, toString) {
    ASSERT_EQ("foo", foo.toString());
  }
}
