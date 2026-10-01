#include "testing.h"

#define MAKE_VAR_INFO(variable) VarInfo{ #variable, variable }

VarInfo runTesting() {
	int a = 0;
	return MAKE_VAR_INFO(a);
}