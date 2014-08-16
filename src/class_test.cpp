#include "gtest/gtest.h"

#include "class.hpp"

namespace {
  TEST(Foo, toString) {
    Foo foo("foo");

    ASSERT_EQ("foo", foo.toString());
  }
}
