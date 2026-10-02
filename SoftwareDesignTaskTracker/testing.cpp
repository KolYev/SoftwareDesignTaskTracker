#include "testing.h"

#define MAKE_VAR_INFO(variable) Info{ #variable, variable, &variable, 0, nullptr, InfoType::Variable }
#define MAKE_ARR_INFO(arr) Info{#arr, arr[0], arr, sizeof(arr)/sizeof(arr[0]), arr, InfoType::Array};
#define MAKE_FUNC_INFO(func) Info{ #func, 0, reinterpret_cast<void*>(func), 0, nullptr, InfoType::Function }

int square(int a) {
	return a * a;
}

Info Testing() {
	int result = square(2);

	return MAKE_FUNC_INFO(square);
}
