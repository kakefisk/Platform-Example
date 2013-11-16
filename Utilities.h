#ifndef UTILITIES_H
#define UTILITIES_H

#include <string>
#include <vector>

namespace util
{
    int stoi(std::string str);
    template<typename T>
    bool contains(std::vector<T>& vec, T value);
}

#endif
