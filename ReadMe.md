# CPP Unit Testing #

## GOAL ##
The goal of this project is to create a simple, header only unit test library for students to fullfill homework assignments requirement for unit testing without relying on proper 3rd party libraries that have compatibility issues on older distros.

## Example ##
Test should be logically grouped into test harnesses. This just keeps tests somewhat organized around what you are testing. 

first we need something to test. My default is the recursive implementation of the fibonacci sequence

``` 
class Logic {
public:
  int fib(const int n) {
    if (n == 0 || n == 1) {
      return n;
    }
    return fib(n - 1) + fib(n - 2);
  };
};
```


Then we need a test harness. This allows us to use the register test function

This takes in any function that takes in no arguments and returns void. I used lambda functions explicitly capturing the `this` scope so we have access to our Logic class local instance. Every test needs a name to make figuring out what failed at least easy

```
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

```

Once we have at least one test harness defined we can register it with a test manager
this is a collection of test harnesses that need to be run. We have a name to make organization clear when running

```
class GlobalTestManager : public TestManager {
public:
  GlobalTestManager() { add_test("Fibbonacci Tests", FibbonacciTestHarness()); }
};
```

once we have this defined we can then just run all of our tests in a main function

```
int main(int argc, char ** argv) {
  GlobalTestManager tr = GlobalTestManager();
  tr.execute();
}
```


the output of a test run marks clearly the failed tests and the program will fail with an error if there are any failures in the test run
```
Found 1 Test Harnesses
Executing Test Harness Fibbonacci Tests
Found 2 Tests
Executing Test Fibbonacci 10
Result  Error   Expected: 10 actual 55
Executing Test Fibbonacci 5
Result  OK
tests failed
```

## Include In Your Project ##

The easiest way is to copy the `test.hpp` header into a directory called `includes/` in the root of your cmake project and have a `include_directories()` entry that includes the correct directory. then you can use `#include "../includes/test.hpp"`
at the top of your test file

## Known Issues ##
This is a simple, bare bones approach that still has some quality of life (QOL) enhancements to make writing tests simple and straightforward. This only runs on c++ 11 and later.

This project aims for simplicity. Feel free to make Pull Requests adding different assertion functions etc

If you run into issues please open a github issue and i will address

