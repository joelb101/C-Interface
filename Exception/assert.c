#include "assert.h"

const Except_T Assert_Failed = {"Assertion Failed"};

void (assert)(int e){
	assert(e);
}
