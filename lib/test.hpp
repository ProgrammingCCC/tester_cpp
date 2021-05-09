#pragma once

#include <iostream>
#include <string>
#include <vector>

static bool failed = false;

template <class T>
constexpr void assert_equal(const T &expected, const T &testVal) {
  if (expected != testVal) {
    std::cout << "Result\tError\tExpected: " << expected << " actual "
              << testVal << std::endl;
    failed = true;
  }
  std::cout << "Result\tOK";
}

class AbstractTestHarness {
private:
  std::vector<void (*)()> testFuncs;

protected:
  AbstractTestHarness *register_test_func(void (*func)()) {
    this->testFuncs.push_back(func);
    return this;
  }

public:
  AbstractTestHarness() { this->testFuncs = std::vector<void (*)()>(); }

  void execute() {
    for (auto f : testFuncs) {
      f();
    }
  }
};

class TestManager {
private:
  std::vector<AbstractTestHarness> *tests;

public:
  TestManager() { this->tests = new std::vector<AbstractTestHarness>(); }
  ~TestManager() { delete this->tests; }
  TestManager *add_test(AbstractTestHarness &&test) {
    this->tests->push_back(std::move(test));
    return this;
  }

  void execute() {
    for (auto t : (*tests)) {
      t.execute();
    }
    if (failed) {
      std::cout << "tests failed" << std::endl;
      exit(1);
    }
  }
};
