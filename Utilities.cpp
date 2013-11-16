#include "Utilities.h"
#include <sstream>

int util::stoi(std::string str)
{
    int result;
    std::stringstream(str) >> result;
    return result;
}

template <typename T>
bool util::contains(std::vector<T>& vec, T value)
{
    for (uint i = 0; i < vec.size(); i++)
    {
        if (vec.at(i) == value)
        {
            return true;
        }
    }
    return false;
}
