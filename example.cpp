#include <vector>
#include "HPPTest.hpp"

void runTest (void){
  REGARDING("thing you're testing") {
    auto vec = new std::vector<int>();
    WHEN("doing this on first"){
      vec->push_back(1);
      THEN("it should look like this after") {
        ASSERT(vec->size() == 1);
        ASSERT(vec != 0); //multiple requires OK
      }
    }
    WHEN("doing nothing second"){
      THEN("it should look like this") {
        ASSERT(vec->size() == 0); //Each WHEN run seperately within REGARDING loop
      }
    }
    WHEN("doing this thing third (that intentionally fails)"){
      vec->pop_back();
      THEN("it should look like this after") {
        ASSERT(vec->size() == 0, (long int) vec->size()); //variadic endings printed
      }
    }
  }
}

int main(void) {
  runTest();
  return 0;
}
