#include <cstdio>
#include <iostream>
#include <cstring>
#include <memory>

struct HPPTestScope {
  const char * testName;
  int whenCount{0};
  int loopNumber{0}; //loop 0, get whenCount, then loop# becomes when#
  int rolling{0}; ///keeps track of which WHEN to execute
  int lastErrdWhen{0}; //to stop over sharing
  int thenCount{0};
  int thenPassCount{0};
  void nextLoop() {
      loopNumber++;
      rolling = whenCount + loopNumber;
  }
  void failedRequire(const char* whenName, const char* thenName, const char * line, const char * condition) {
    failedRequire(whenName, thenName, line, condition, 0);
  }
  template <typename ... Values> void failedRequire(const char* whenName, const char* thenName, const char * line, const char * condition, const char *valueNames, const Values & ... values) {
    if ( lastErrdWhen != loopNumber ){
      printf("REGARDING %s: Failed when #%i \nWHEN %s: \n", testName , loopNumber, whenName);
      lastErrdWhen = loopNumber;
    }
    if (valueNames != 0 && valueNames[0] != 0){
      printf("THEN %s… FAILS line %s: %s. values: ", thenName, line, condition);
      printVars(valueNames, values...);
    } else {
      printf("THEN %s… FAILS line %s: %s\n", thenName, line, condition );
    }
  }
  void printVars(const char * names) const{
    std::cout << "\n";
  }
  template <typename T, typename ... More> void printVars (const char* names, const T& print, const More & ... more) const {
    const char * nextNames = strchr(names, ',');
    for (const char * printChar = names; printChar != nextNames && *printChar != 0 ; printChar++){
      if (*printChar == ' ') continue;
      std::cout << *printChar;
    }
    std::cout << " = " << print;
    if (nextNames != 0){
      std::cout << ", ";
      nextNames++;
    }
    printVars(nextNames, more...);
  }
  ~HPPTestScope(){
    printf("COMPLETED %s: %i WHENs. Passing %i of %i THENs. \n", testName, whenCount, thenPassCount, thenCount);
  }
};

struct HPPTestThenHelper {
  std::shared_ptr<HPPTestScope> testScope{nullptr};
  const char * thenName{NULL};
  bool failed{false};
  operator bool() const { return true; }
  ~HPPTestThenHelper(){
    if (testScope && !failed){
      testScope->thenPassCount++;
    }
  }
};

//Major feature is variables/setup in REGARDING are repeated for each WHEN
#define REGARDING( Name ) \
    for (std::shared_ptr<HPPTestScope> _HPPTestScope(new HPPTestScope({ Name })) ; _HPPTestScope->loopNumber <= _HPPTestScope->whenCount ; _HPPTestScope->nextLoop())

#define WHEN( Name ) \
    if (_HPPTestScope->loopNumber == 0) { _HPPTestScope->whenCount++; } \
    _HPPTestScope->rolling--; \
    /* following is an if then statement, expressed as !if else then… since can't scope condition and var assignment together in C */ \
    if (!(_HPPTestScope->rolling == _HPPTestScope->whenCount)) {} else if ( const char* _ATestWHEN = Name )

#define THEN( Name ) \
    _HPPTestScope->thenCount++; \
    if ( HPPTestThenHelper _HPPTestThenHelper{_HPPTestScope, Name } )

#define REQUIRE_LINE_TOO( Condition , Line, vars... ) \
    const char* _ATestREQUIRE##Line = #Condition; \
    try { if (! ( Condition ) ) { \
      _HPPTestThenHelper.failed = true; \
      _HPPTestScope->failedRequire(_ATestWHEN, _HPPTestThenHelper.thenName, #Line, _ATestREQUIRE##Line, #vars, ##vars ); \
    }} catch (...) { \
      _HPPTestThenHelper.failed = true; \
      _HPPTestScope->failedRequire(_ATestWHEN, _HPPTestThenHelper.thenName, #Line, _ATestREQUIRE##Line, "EXCEPTION", "TRUE" ); \
    }
#define REQUIRE_LINE( Condition , Line, vars... ) REQUIRE_LINE_TOO( Condition, Line , ##vars )
#define REQUIRE(Condition, vars... ) REQUIRE_LINE( Condition, __LINE__ , ##vars )
