# *HPPTest*
C++ behavior testing ~~framework~~ header modeled on [Catch](https://github.com/philsquared/Catch).

## Structure
```C++
GIVEN("thing you're testing") {
  auto vec = new std::vector<int>();
  WHEN("doing this on first"){
    vec->push_back(1);
    THEN("it should look like this after") {
      ASSERT(vec->size() == 1);
      ASSERT(vec != 0); //multiple requires OK
    }
  }
  WHEN("doing this thing second (that intentionally fails)"){
    vec->pop_back();
    THEN("it should look like this after") {
      ASSERT(vec->size() == 0, (long int) vec->size()); //variadic endings printed
    }
  }
}
//next GIVEN goes here
```
*prints…*
```
GIVEN thing you're testing: Failed when #2
WHEN doing this thing second (that intentionally fails):
THEN it should look like this after… FAILS line 26: vec->size() == 0. values: (longint)vec->size() = -1
COMPLETED thing you're testing: 2 WHENs. Passing 1 of 2 THENs.
```


## Features
- **GIVEN** is a for loop, running each WHEN separately
- **Prints** failed conditions and their line numbers
- **ASSERT(condition, values...)** has a variadic ending, to print values for failed conditions
- **Prints** WHEN count and THEN pass count after each GIVEN's completion, so you know how you're doing

## Example
See [example.cpp](example.cpp)

## Limitations
- Requires C++11 features like `auto` and `unique_ptr` found in GCC 4.7+ or Apple's Clang, with the `-std=c++11` option.
- *HPPTest* **only** catches exceptions in ASSERT. Exceptions that occur in test setup are not caught.
- You must use braces `{}` after GIVEN, WHEN and THEN.
- If your ASSERTS have potential for `nullptr`, know HPPTest doesn't avoid segfaults. Instead use the `ASSERT(TPtr(pointer) && pointer->member)` pattern with the following snippet

```C++
bool ThrowFalse(bool c){ if (!c) {throw "ThrowFalse"; } return c; }
#define TPtr( a ) ThrowFalse(a != 0)
```

## Test todo
*Pull requests welcome!*
- Write `ASSERT_EXCEPTION` for tests that ensure exceptions happen.
- ~~Print pass/fail count of THENs on GIVEN completion~~

## License?
I'm flattered! MIT License.
