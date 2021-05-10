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
  } else {
    std::cout << "Result\tOK" << std::endl;
  }
}

class AbstractTestHarness {
private:
  std::vector<std::function<void()>> testFuncs;

protected:
  void register_test_func(std::function<void()> &&func) {
    this->testFuncs.push_back(std::move(func));
  }

public:
  AbstractTestHarness() {
    this->testFuncs = std::vector<std::function<void()>>();
  }
  void execute() {
    std::cout << "Found " << testFuncs.size() << " Tests" << std::endl;
    for (auto f : testFuncs) {
      f();
    }
  }
};

class TestManager {
private:
  std::vector<AbstractTestHarness> tests;

protected:
  void add_test(AbstractTestHarness &&test) {
    this->tests.push_back(std::move(test));
  }

public:
  TestManager() { this->tests = std::vector<AbstractTestHarness>(); }
  void execute() {
    std::cout << "Found " << tests.size() << " Test Harnesses" << std::endl;
    for (AbstractTestHarness t : tests) {
      t.execute();
    }
    if (failed) {
      std::cout << "tests failed" << std::endl;
      exit(1);
    }
  }
};
