#include "testing.h"

#define MAKE_VAR_INFO(variable) VarInfo{ #variable, variable, &variable }
#define MAKE_ARR_INFO(arr) VarInfo{#arr, arr[0], arr, sizeof(arr)/sizeof(arr[0]), arr};

VarInfo Testing() {
	static int arr[] = { 1,2,3,4,5 };

	return MAKE_ARR_INFO(arr);
}
