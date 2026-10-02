#pragma once
#include <string>
#include <vector>
#include <type_traits>

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

	int paramCount = 0;
	std::vector<std::string> paramTypes;
	std::string returnType;
};


Info Testing();