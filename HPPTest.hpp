#include <cstdio>
#include <memory>

struct ATestScope { //REGARDINGSCOPE
  const char * testName;
  int whenCount;
  int loopNumber; //loop 0, get whenCount, then loop# becomes when#
  int rolling; //keeps track of which WHEN to execute
  int lastErrdWhen; //to stop over sharing
  void nextLoop() {
      loopNumber++;
      rolling = whenCount + loopNumber;
  }
  ~ATestScope(){
    printf("COMPLETED %s: %i WHENs\n", testName, whenCount);
  }
};

//Major feature is variables/setup in REGARDING are repeated for each WHEN
#define REGARDING( Name ) \
    for (std::unique_ptr<ATestScope> _ATestScope(new ATestScope({ Name })) ; _ATestScope->loopNumber <= _ATestScope->whenCount ; _ATestScope->nextLoop())

#define WHEN( Name ) \
    if (_ATestScope->loopNumber == 0) { _ATestScope->whenCount++; } \
    _ATestScope->rolling--; \
    /* following is an if then statement, expressed as !if else then… since can't scope condition and var assignment together in C */ \
    if (!(_ATestScope->rolling == _ATestScope->whenCount)) {} else if ( const char* _ATestWHEN = Name )

#define THEN( Name ) \
    if (const char* _ATestTHEN = Name )

#define REQUIRE_LINE_TOO( Condition , Line ) \
    const char* _ATestREQUIRE##Line = #Condition; \
    if (! ( Condition ) ) { \
      if ( _ATestScope->lastErrdWhen != _ATestScope->loopNumber ){ \
        printf("REGARDING %s: Failed when #%i \nWHEN %s: \n", _ATestScope->testName ,_ATestScope->loopNumber, _ATestWHEN); \
        _ATestScope->lastErrdWhen = _ATestScope->loopNumber; \
      } \
      printf("THEN %s… FAILS line %s: %s\n", _ATestTHEN, #Line, _ATestREQUIRE##Line ); \
    }
#define REQUIRE_LINE( Condition , Line ) REQUIRE_LINE_TOO( Condition, Line )
#define REQUIRE( Condition ) REQUIRE_LINE( Condition, __LINE__ )
