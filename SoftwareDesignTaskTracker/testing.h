#pragma once
#include <string>

struct VarInfo {
	std::string name;
	int value;
	int* address;
};

VarInfo runTesting();