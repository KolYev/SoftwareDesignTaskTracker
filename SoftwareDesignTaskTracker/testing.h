#pragma once
#include <string>
#include <vector>

enum class InfoType {
	Variable,
	Array,
	Function
};

struct Info {
	std::string name;
	int value;
	void* address;
	size_t size;
	int* arrayPtr;
	InfoType type;
};


Info Testing();