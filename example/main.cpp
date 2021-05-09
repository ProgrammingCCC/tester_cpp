#include "../lib/test.hpp"
#include <functional>

class Logic {
public:
  int fib(const int n) {
    if (n == 0 || n == 1) {
      return n;
    }
    return fib(n - 1) + fib(n - 2);
  };
};

class TestExample : public AbstractTestHarness {
private:
  Logic l = Logic();

public:
  void TestFib() {

    register_test_func([this]() -> void { assert_equal(55, l.fib(5)); });
    // this will fail
    register_test_func([this]() -> void { assert_equal(10, l.fib(10)); });
  }
};
