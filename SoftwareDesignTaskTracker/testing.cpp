#include "testing.h"
#include <sstream>
#include <typeinfo>

template <typename T>
Info MakeVarInfo(const char* name, T& var) {
    Info info;
    info.name = name;
    info.typeName = typeid(T).name();
    info.address = &var;
    info.type = InfoType::Variable;

    info.getValue = [&var] {
        std::ostringstream os;
        os << var;
        return os.str();
        };

    info.setValue = [&var](const std::string& s) {
        if constexpr (std::is_same_v<T, std::string>) {
            var = s;
        }
        else {
            std::istringstream is(s);
            T tmp{};
            if (is >> tmp) var = tmp;
        }
        };
    return info;
}

template <typename T, size_t N>
Info MakeArrInfo(const char* name, T(&arr)[N]) {
    Info info;
    info.name = name;
    info.typeName = typeid(T).name();
    info.address = arr;
    info.type = InfoType::Array;
    info.size = N;
    if constexpr (std::is_same_v<T, int>)
        info.arrayPtr = arr;
    return info;
}

#define MAKE_VAR_INFO(v) MakeVarInfo(#v, v)
#define MAKE_ARR_INFO(a) MakeArrInfo(#a, a)

Info Testing() {
    static int a = 4;        
    return MAKE_VAR_INFO(a);
}