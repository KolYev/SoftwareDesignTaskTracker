#pragma once
#include <string>
#include <vector>

struct VarInfo {
	std::string name;
	int value;
	void* address;
	size_t size;
	int* arrayPtr;
};

VarInfo Testing();