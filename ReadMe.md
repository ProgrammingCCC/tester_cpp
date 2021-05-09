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

This takes in any function that takes in no arguments and returns void. I used lambda functions explicitly capturing the `this` scope so we have access to our Logic class local instance.

```
class FibbonacciTestHarness : public AbstractTestHarness {
private:
  Logic l = Logic();

public:
  void TestFib() {

    register_test_func([this]() -> void { assert_equal(55, l.fib(5)); });
    // this will fail
    register_test_func([this]() -> void { assert_equal(10, l.fib(10)); });
  }
};

```

Once we have at least one test harness defined we can register it with a test manager
this is a collection of test harnesses that need to be Runnymede

```
class GlobalTestManager : public TestManager {
public:
  GlobalTestManager() { add_test(FibbonacciTestHarness()); }
};
```

once we have this defined we can then just run all of our tests in a main function

```
int main(int argc, char ** argv) {
  GlobalTestManager tr = GlobalTestManager();
  tr.execute();
}
```


## Include In Your Project ##

The easiest way is to copy the `test.hpp` header into a directory called `includes/` in the root of your cmake project and have a `include_directories()` entry that includes the correct directory. then you can use `#include "../includes/test.hpp"`
at the top of your test file

## Known Issues ##
This is a simple, bare bones approach that still has some quality of life (QOL) enhancements to make writing tests simple and straightforward. This only runs on c++ 11 and later.

If you run into issues please open a github issue and i will address

