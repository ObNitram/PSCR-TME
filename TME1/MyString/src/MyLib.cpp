//
// Created by obnitram on 20/09/24.
//

#include "MyLib.hpp"

#include <cstring>

namespace pr
{
size_t strlen(const char *str)
{
    for (const char *itr = str; ; ++itr)
    {
        if (*itr == '\0')
        {
            return reinterpret_cast<size_t>(itr) - reinterpret_cast<size_t>(
                       str);
        }
    }
}

char *newCopy(const char *str)
{
    const size_t len = strlen(str) + 1;
    const auto copy = new char[len];
    memcpy(copy, str, len);
    return copy;
}
} // pr