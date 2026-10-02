#pragma once
#include <string>
#include <vector>
#include <functional>
#include <type_traits>

enum class InfoType {
	Variable,
	Array,
	Function
};

struct Info {
	std::string name;									// имя
	std::string typeName;
	void* address = nullptr;							// адрес
	InfoType type = InfoType::Variable;					// тип данных
	int value = 0;

	std::function<std::string()> getValue;				// получить значение
	std::function<void(const std::string&)> setValue;	//поменять значение
	
	// для массива
	size_t size = 0;									// размер
	int* arrayPtr;										// указатель на массив
	
	// для функции
	int paramCount = 0;
	std::vector<std::string> paramTypes;
	std::string returnType;
};


Info Testing();