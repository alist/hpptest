# *HPPTest*
C++ behavior testing ~~framework~~ header modeled on [Catch](https://github.com/philsquared/Catch).

## Structure
```C++
REGARDING("thing you're testing") {
  auto vec = new std::vector<int>();
  WHEN("doing this first"){
    vec->push_back(1);
    THEN("it should look like this after") {
      REQUIRE(vec->size() == 1);
    }
  }
  WHEN("doing this thing second (that intentionally fails)"){
    vec->pop_back();
    THEN("it should look like this after") {
      REQUIRE(vec->size() == 0);
      REQUIRE(vec != 0); //multiple requires OK
    }
  }
}
//next REGARDING goes here
```
*prints…*
```
REGARDING thing you're testing: Failed when #2
WHEN doing this thing second (that intentionally fails):
THEN it should look like this after… FAILS line 17: vec->size() == 0
COMPLETED thing you're testing: 2 WHENs
```


## Features
- **REGARDING** is a for loop, running each WHEN separately
- **Printf**s failed conditions and their line numbers
- **Printf**s WHEN count after each REGARDING's completion, so you know tests ran
- ***Antifeature*** make sure you use braces after REGARDING, WHEN and THEN

## Example
See [example.cpp](example.cpp)

## Requirements
Requires C++11 feature like `auto` and `unique_ptr` found in GCC 4.7+ or Apple's Clang. On `OSX` with XCode, I think you can use `g++ -std=c++11 -g example.cpp`. I compile my programs with `g++-5.2.0 -std=c++14 -g example.cpp`.

## Test todo
*Pull requests welcome!*
- Write `REQUIRE_EXCEPTION` for tests that ensure exceptions happen
- Print pass/fail count of THENs on REQUIRE completion. A `passedRequire` function could help tabulate.
- Give variadic ending to `REQUIRE(condition, ...)` such that on failure, all variadics are printed via `failedRequire`'s `values`
- Wrap REGARDING/WHEN in try statement, to catch exceptions that occur in test setup.
- Modify MACRO ifs to force curleys. [Possible](https://isocpp.org/wiki/faq/misc-technical-issues#macros-with-if)?
- remove C++11 dependency
- Engineer a test ~~framework~~ header for this test header
- ~~Wrap each REQUIRE expression in try statement to prevent test case failure from breaking run~~
- ~~Print when tests completed, #tests #ofsuccesses, perhaps in ~ATestScope. smart pointers to ensure we get released~~
- ~~If failing multiple REQUIRES in THEN, print only FAILS line~~
- ~~Store WHEN count and current index in GIVEN~~
- ~~made REGARDING for loop, run each WHEN separately!~~
- ~~Run REGARDING scope for each WHEN~~
- ~~Use REGARDING, WHEN, THEN, REQUIRE BDD style~~
- ~~Print out relevant data when REQUIRE fails~~
- ~~Allow multiple REQUIRES in THEN scope~~

## License?
I'm flattered! MIT License.
