#include <string>
#include <vector>

#include "gtest/gtest.h"

#include "inverted_index.hpp"

namespace {
  class InvertedIndexTest : public ::testing::Test {
   protected:
    virtual void SetUp() {
      index.index("d5", "baz");  // To test ordering
      index.index("d0", "");
      index.index("d1", "foo");
      index.index("d2", "foo bar");
      index.index("d3", "foo bar baz");
      index.index("d4", "foo  bar\nbaz");
    }

    InvertedIndex index;
  };

  TEST_F(InvertedIndexTest, Empty) {
    ASSERT_EQ((vector<string> {}), index.query(""));
  }

  TEST_F(InvertedIndexTest, OneWord) {
    ASSERT_EQ((vector<string> {"d1", "d2", "d3", "d4"}), index.query("foo"));
  }

  TEST_F(InvertedIndexTest, TwoConsecutiveWords) {
    ASSERT_EQ((vector<string> {"d2", "d3", "d4"}), index.query("foo bar"));
  }

  TEST_F(InvertedIndexTest, TwoNonConsecutiveWords) {
    ASSERT_EQ((vector<string> {}), index.query("foo baz"));
  }

  TEST_F(InvertedIndexTest, LineBreak) {
    ASSERT_EQ((vector<string> {"d3"}), index.query("bar baz"));
  }

  TEST_F(InvertedIndexTest, TwoConsecutiveWordsWrongOrder) {
    ASSERT_EQ((vector<string> {}), index.query("bar foo"));
  }

  TEST_F(InvertedIndexTest, ThreeConsecutiveWords) {
    ASSERT_EQ((vector<string> {"d3"}), index.query("foo bar baz"));
  }

  TEST_F(InvertedIndexTest, ResultOrder) {
    ASSERT_EQ((vector<string> {"d3", "d4", "d5"}), index.query("baz"));
  }
}  // namespace
