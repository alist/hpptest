#include <vector>
#include "HPPTest.hpp"

template <typename T> void testVec (void){
  REGARDING("vectors") {
    WHEN("instantiating a new vector"){
      auto exVec = new std::vector<T>();
      THEN("it should not be null") {
        REQUIRE(exVec != 0);
      }
      THEN("it should have size 0") {
        REQUIRE(exVec->size() == 0);
      }
    }
  }
}

int main(void) {
  testVec<char>();
  return 0;
}
