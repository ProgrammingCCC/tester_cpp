#include "lib/test.hpp"
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

class FibbonacciTestHarness : public AbstractTestHarness {
private:
  Logic l = Logic();

public:
  FibbonacciTestHarness() {
    register_test_func("Fibbonacci 5",
                       [this]() -> void { assert_equal(5, l.fib(5)); });
    register_test_func("Fibbonacci 10",
                       [this]() -> void { assert_equal(10, l.fib(10)); });
  }
};

class GlobalTestManager : public TestManager {
public:
  GlobalTestManager() { add_test("Fibbonacci Tests", FibbonacciTestHarness()); }
};

int main(int argc, char **argv) {
  GlobalTestManager tr = GlobalTestManager();
  tr.execute();
}
