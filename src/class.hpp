#include <string>

using namespace std;

class Foo {
 public:
  explicit Foo(const string& s) : s_(s) {}

  string toString() {
    return s_;
  }

 private:
  string s_;
};
