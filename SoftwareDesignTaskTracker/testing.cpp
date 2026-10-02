#include "testing.h"
#include <typeinfo>
#include <tuple>

#define MAKE_VAR_INFO(variable) Info{ #variable, variable, &variable, 0, nullptr, InfoType::Variable }
#define MAKE_ARR_INFO(arr) Info{#arr, arr[0], arr, sizeof(arr)/sizeof(arr[0]), arr, InfoType::Array}

template <typename T>
struct FunctionTraits;

template <typename R, typename... Args>
struct FunctionTraits<R(*)(Args...)> {
    static constexpr int arity = sizeof...(Args);

    static std::vector<std::string> arg_types() {
        return std::vector<std::string>{ typeid(Args).name()... };
    }

    static std::string return_type_name() {
        return typeid(R).name();
    }
};

template <typename R, typename... Args>
Info MakeFunctionInfo(const char* name, R(*func)(Args...)) {
    using Traits = FunctionTraits<R(*)(Args...)>;

    return Info{
        name,
        0,
        reinterpret_cast<void*>(func),
        0,
        nullptr,
        InfoType::Function,
        Traits::arity,
        Traits::arg_types(),
        Traits::return_type_name()
    };
}

#define MAKE_FUNC_INFO(func) MakeFunctionInfo(#func, func)

int square(int a) {
    return a * a;
}

Info Testing() {
    int result = square(2);

    return MAKE_FUNC_INFO(square);
}