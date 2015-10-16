# *HPPTest*
C++ behavior testing ~~framework~~ header modeled on [Catch](https://github.com/philsquared/Catch).

## Structure
```C++
REGARDING("thing you're testing") {
  auto vec = new std::vector<int>();
  WHEN("doing this on first"){
    vec->push_back(1);
    THEN("it should look like this after") {
      REQUIRE(vec->size() == 1);
      REQUIRE(vec != 0); //multiple requires OK
    }
  }
  WHEN("doing this thing second (that intentionally fails)"){
    vec->pop_back();
    THEN("it should look like this after") {
      REQUIRE(vec->size() == 0, (long int) vec->size()); //variadic endings printed
    }
  }
}
//next REGARDING goes here
```
*prints…*
```
REGARDING thing you're testing: Failed when #2
WHEN doing this thing third (that intentionally fails):
THEN it should look like this after… FAILS line 22: vec->size() == 0. values: (longint)vec->size() = -1
COMPLETED thing you're testing: 2 WHENs
```


## Features
- **REGARDING** is a for loop, running each WHEN separately
- **Prints** failed conditions and their line numbers
- **REGARDING(condition, values...)** has a variadic ending, to print values for failed conditions
- **Prints** WHEN count after each REGARDING's completion, so you know tests ran

## Example
See [example.cpp](example.cpp)

## Limitations
- Requires C++11 features like `auto` and `unique_ptr` found in GCC 4.7+ or Apple's Clang, with the `-std=c++11` option.
- *HPPTest* **only** catches exceptions in REQUIRE. Exceptions that occur in test setup are not caught.
- You must use braces `{}` after REGARDING, WHEN and THEN.

## Test todo
*Pull requests welcome!*
- Write `REQUIRE_EXCEPTION` for tests that ensure exceptions happen.
- Print pass/fail count of THENs on REQUIRE completion.

## License?
I'm flattered! MIT License.
