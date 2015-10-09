# *HPPTest*
A C++ testing ~~framework~~ header modeled on [Catch](https://github.com/philsquared/Catch).

## Structure
*Roughly behavior driven.*
```C++
REGARDING("thing you're testing") {
  auto vec = new std::vector<int>();
  WHEN("doing this first"){
    vec->push_back(1);
    THEN("it should look like this after") {
      REQUIRE(vec->size() == 1);
    }
  }
  WHEN("doing this thing second"){
    THEN("it should look like this after") {
      REQUIRE(vec->size() == 0);
      REQUIRE(vec != 0); //multiple requires OK
    }
  }
}
```

## Features
- **REGARDING** is a for loop, running each WHEN separately
- **printf** is used to print errors to cstdio
- ***Antifeature*** make sure you use braces after each MACRO KEYWORD

## Example
See [example.cpp](example.cpp)

## Requirements
Requires C++11 feature like `auto` found in GCC 4.7+ or Apple's Clang. On `OSX` with XCode, I think you can use `g++ -std=c++11 -g example.cpp`. I compile my programs with `g++-5.2.0 -std=c++14 -g example.cpp`. These features are not necessary– pull requests welcome!

## Test todo
- Modify MACRO ifs to force curleys. [Possible](https://isocpp.org/wiki/faq/misc-technical-issues#macros-with-if)?
- remove C++11 dependency
- Capture LHS & RHS in Condition and print when fail:: OR give variadic ending to require such that on failure, all variadics are printed
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
