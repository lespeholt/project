#include <iostream>

#include "class.hpp"

using namespace std;

int main(int argc, const char* argv[]) {
  Foo food("Hello, World!\n");

  cout << food.toString();
  return 0;
}
