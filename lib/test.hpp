#pragma once

#include <functional>
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
  std::vector<std::function<void()>> *testFuncs;

protected:
  void register_test_func(std::function<void()> func) {
    this->testFuncs->push_back(func);
  }

public:
  AbstractTestHarness() {
    this->testFuncs = new std::vector<std::function<void()>>();
  }
  ~AbstractTestHarness() { delete this->testFuncs; }

  void execute() {
    for (auto f : (*testFuncs)) {
      f();
    }
  }
};

class TestManager {
private:
  std::vector<AbstractTestHarness> *tests;

protected:
  void add_test(AbstractTestHarness &&test) {
    this->tests->push_back(std::move(test));
  }

public:
  TestManager() { this->tests = new std::vector<AbstractTestHarness>(); }
  ~TestManager() { delete this->tests; }
  void execute() {
    for (AbstractTestHarness t : (*tests)) {
      t.execute();
    }
    if (failed) {
      std::cout << "tests failed" << std::endl;
      exit(1);
    }
  }
};
