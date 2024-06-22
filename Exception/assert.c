#include "Assert.h"

const Except_T Assert_Failed = {"Assertion Failed"};

void (Assert)(int e){
	Assert(e);
}
